#include "include/graph.h"
#include "include/dataStructures.h"
#include "include/heap.h"
#include "include/stack.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

graph::graph() : vertices(0) {} //constructor allocates memory for vertices and edges in adj liist
graph::graph(int vertices) : vertices(vertices) {
  vertList = new vertex *[vertices + 1];
  adjacencyList = new edge *[vertices + 1];
}
graph::~graph() {//destructor 
  for (int i = 0; i < vertices; i++) {
    delete adjacencyList[i];
    delete vertList[i];
  }
  delete[] vertList;
  delete[] adjacencyList;
}

int graph::readGraphFile(std::string &fileName, bool directed, int flag, //read graph function
                         graph &myGraph) {
  ifstream inputFile(fileName);
  if (!inputFile) {
    std::cerr << "Error opening file." << endl;
    exit(EXIT_FAILURE);
  }

  int numVertices, numEdges;
  inputFile >> numVertices >> numEdges;

  heap *newHeap;
  newHeap = new heap(numVertices);
  stack *newStack;
  newStack = new stack();

  vertex **V = new vertex *[numVertices + 1];
  edge **ADJ = new edge *[numVertices + 1];

  for (int i = 1; i <= numVertices; i++) {
    V[i] = new vertex;
    V[i]->index = i;
    V[i]->pi = -1;
    V[i]->key = INT_MAX;
    V[i]->distance = INT_MAX;
    ADJ[i] = nullptr;
  }

  vertList = V;

  int edgeIndex;
  int u;
  int v;
  float weight; // New variable to store edge weight

  while (inputFile >> edgeIndex >> u >> v >> weight) {
    edge *newEdge = new edge;
    newEdge->index = edgeIndex;
    newEdge->u = u;
    newEdge->v = v;
    newEdge->w = weight; // Set the weight
    newEdge->next = nullptr;

    if (flag == 1 && directed) { //directed graph with flag 1
      newEdge->next = ADJ[u];
      ADJ[u] = newEdge;
    } else if (flag == 2 && directed) { //directed graph with flag 2
      edge **p = &ADJ[u];
      while (*p != nullptr) {
        p = &((*p)->next);
      }
      *p = newEdge;
    } else if (flag == 1 && !directed) { //undirected graph with flag 1
      newEdge->next = ADJ[u];
      ADJ[u] = newEdge;

      edge *r = new edge;
      r->u = v;
      r->v = u;
      r->w = weight; // Set the weight for the reversed edge
      r->next = ADJ[v];
      ADJ[v] = r;
    } else if (flag == 2 && !directed) { //undirected graph with flag 2
      edge **p = &ADJ[u];
      while (*p != nullptr) {
        p = &((*p)->next);
      }
      *p = newEdge;

      edge **r = &ADJ[v];
      while (*r != nullptr) {
        r = &((*r)->next);
      }

      edge *newEdgeReversed = new edge; //reversed edge
      newEdgeReversed->u = v;
      newEdgeReversed->v = u;
      newEdgeReversed->w = weight; // Set the weight for the reversed edge
      newEdgeReversed->index = edgeIndex;
      newEdgeReversed->next = nullptr;
      *r = newEdgeReversed;
    }
  }

  myGraph.adjacencyList = ADJ; //add to graph object members 
  myGraph.vertices = numVertices;
  myGraph.vertList = V;

  inputFile.close();

  return numVertices;
}

void graph::dijkstras(int source, int destination, heap &minHeap, //basic dijkstras algo 
                      stack &newStack) {
  initializeSingleSource(source);

  for (int i = 1; i <= vertices; ++i) {
    minHeap.insert(vertList[i]);
  }

  while (!minHeap.isEmpty()) {
    vertex *u = minHeap.extractMin();

    edge *currentEdge = adjacencyList[u->index];
    while (currentEdge != nullptr) {
      int vIndex = currentEdge->v;
      vertex *v = vertList[vIndex];
      float weight = currentEdge->w;

      // Call your relax function
      relax(u, v, weight, minHeap);

      currentEdge = currentEdge->next;
    }
  }
}

void graph::singlePair(int source, int destination, heap &minHeap, //single pair function 
                       stack &newStack) {
  initializeSingleSource(source);

  dijkstras(source, destination, minHeap, newStack);
}

void graph::singleSource(int source, heap &minHeap, stack &newStack) { //single source 
  initializeSingleSource(source);

  dijkstras(source, INT_MAX, minHeap,
            newStack); // destination = INT_MAX so it finds shortest path to all
                       // vertices
}

void graph::printPath(int source, int destination, stack &newStack) { //print path for single source 

  if (getLastPath() != 4) { //if last computation doesn't match exit
    std::cout << "Last path computation doesn't match!\n";
    return;
  }

  if (getLastSource() != source && getLastDestination() != destination) { //if source and destination don't match last source and destination exit 
    std::cout << "Source and destination do not match last compuation\n";
    return;
  }

  if (vertList[destination]->distance == INT_MAX) { //if path doesn't exsist 
    std::cout << "No path from " << source << " to " << destination << ".\n";
    return;
  }

  int curr = destination;

  while (curr != source) { //printing path algo 
    newStack.push(vertList[curr]);
    curr = vertList[curr]->pi;
  }
  newStack.push(vertList[source]);

  std::cout << "Shortest Path from " << source << " to " << destination << ": ";

  while (!newStack.isEmpty()) {
    std::cout << newStack.top()->index;
    newStack.pop();
    if (!newStack.isEmpty()) {
      std::cout << " -> ";
    }
  }

  std::cout << "\n";
}

void graph::printPathSingle(int source, stack &newStack) { //single source print function 

  if (getLastPath() != 3) {
    std::cout << "Last path computation doesn't match!\n";
    return;
  }

  if (getLastSource() != source) {
    std::cout << "Source does not match last compuation\n";
    return;
  }

  int currentVertex = vertList[source]->key;
  while (currentVertex != -1) {
    newStack.push(vertList[currentVertex]);
    currentVertex = vertList[currentVertex]->pi;
  }

  // Pop and print vertices from the stack
  while (!newStack.isEmpty()) {
    vertex *current = newStack.top();
    newStack.pop();
    std::cout << "[" << current->index << ": " << current->distance << "]";
    if (!newStack.isEmpty()) {
      std::cout << "-->";
    }
  }

  std::cout << "." << std::endl;
}

void graph::printPathHelper(int source, stack &newStack) {
  for (int i = 1; i <= vertices; ++i) {
    // Check if the vertex is the source
    if (i == source) {
      std::cout << "The shortest path from " << source << " to " << i
                << " is:" << std::endl;
      std::cout << "[" << i << ": 0.00]" << std::endl;
    } else {
      // Check if the vertex is reachable from the source
      if (vertList[i]->distance == INT_MAX) {
        std::cout << "The shortest path from " << source << " to " << i
                  << " is not reachable." << std::endl;
      } else {
        // Print the shortest path
        std::cout << "The shortest path from " << source << " to " << i
                  << " is:" << std::endl;
        printPathSingle(i, newStack);
      }
    }
  }
}

void graph::printLength(int source, int destination) { //print lenght of path
  if (getLastPath() != 3) {
    std::cout << "Last path compuation is not valid for this function\n";
    return;
  }

  if (source != getLastSource() && destination != getLastDestination()) {
    std::cout << "source and destination don't match last computation!\n";
  }

  if (vertList[destination]->distance == INT_MAX) {
    std::cout << "There is no path from " << source << " to " << destination
              << "\n";
  } else {
    std::cout << "The length of the shortest path from " << source << " to "
              << destination << " is " << vertList[destination]->distance
              << std::endl;
  }
}

void graph::printAdj(vertex **V, edge **ADJ, int numVertices) { //print adjacency list 
  std::cout << "\nAdjacency List:\n";
  for (int i = 1; i <= numVertices; i++) {
    std::cout << "ADJ[" << i << "]:-->";

    edge *currentEdge = ADJ[i];
    while (currentEdge != nullptr) {
      std::cout << "[" << currentEdge->u << " " << currentEdge->v << ": "
                << currentEdge->w << "]";

      if (currentEdge->next != nullptr) {
        std::cout << "-->";
      }

      currentEdge = currentEdge->next;
    }
    std::cout << std::endl;
  }
}

void graph::addEdge(int index, int u, int v, float w) { //not used
  edge *newEdge = new edge;
  newEdge->index = index; // You may set this to an appropriate value
  newEdge->u = u;
  newEdge->v = v;
  newEdge->w = w;
  newEdge->next = nullptr;

  // Add the new edge to the list
  adjacencyList[u] = newEdge;
}

edge *graph::createEdge(int index, int u, int v, float w) { return nullptr; } //not used 

void graph::relax(vertex *u, vertex *v, float weight, heap &minHeap) { //dijkstras relax function 
  if (v->distance > u->distance + weight) {
    v->distance = u->distance + weight;
    v->pi = u->index;

    minHeap.decreaseKey(v->index - 1, v->distance);
  }
}

void graph::setVertices(int num) { vertices = num; } //private member setter 

void graph::printGraph(vertex **V, edge **ADJ, int numVertices) { //not used 
  std::cout << "Vertex List:\n";
  for (int i = 1; i <= numVertices; i++) {
    std::cout << "Vertex " << V[i]->index << ": "
              << "pi=" << V[i]->pi << ", key=" << V[i]->key
              << ", distance=" << V[i]->distance << std::endl;
  }
}

edge **graph::getAdjacencyList() const { return adjacencyList; } //private member getter 

vertex **graph::getVertList() const { return vertList; } //private member getter 

int graph::getVertices() const { return vertices; }//private member getter 

void graph::initializeSingleSource(int source) { //single source initialize function 
  for (int i = 1; i <= vertices; i++) {
    vertList[i]->distance = (i == source) ? 0 : INT_MAX;
    vertList[i]->pi = -1;
  }
}

void graph::updateLastPath(int l) { lastPathComputation = l; } //private member setter function 

int graph::getLastPath() { return lastPathComputation; } //private member getter 

int graph::getLastSource() { return lastSource; } //private member getter 


void graph::setLastSource(int v) { lastSource = v; } //private member setter

void graph::setLastDestination(int v) { lastDestination = v; } //private member setter

int graph::getLastDestination() { return lastDestination; } //private member setter 

void graph::setLastPath(int v) { lastPathComputation = v; }//private member setter 
