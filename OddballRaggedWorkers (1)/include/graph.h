#pragma once

#include "dataStructures.h"
#include "heap.h"
#include "stack.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class graph {
public:
  graph();
  graph(int vertices);
  ~graph();

  int readGraphFile(std::string &fileName, bool directed, int flag,
                    graph &myGraph);
  void buildAdjacencyLists(bool directed, int flag);
  void singlePair(int source, int destination, heap &minHeap, stack &newStack);
  void singleSource(int source, heap &minHeap, stack &newStack);
  void printPath(int source, int destination, stack &stack);
  void printPathSingle(int source, stack &stack);
  void printPathHelper(int source, stack &newStack);
  void printLength(int source, int destination);
  void printAdj(vertex **V, edge **ADJ, int numVertices);
  void addEdge(int index, int u, int v, float w);
  void printGraph(vertex **V, edge **ADJ, int numVertices);
  edge **getAdjacencyList() const;
  vertex **getVertList() const;
  int getVertices() const;
  void updateLastPath(int lastPathComp);
  int getLastPath();
  void setLastPath(int v);
  int getLastSource();
  void setLastSource(int v);
  void setLastDestination(int v);
  int getLastDestination();

private:
  int vertices;
  vertex **vertList;    // vertex list
  edge **adjacencyList; // adjacency list of pointers
  int lastPathComputation;
  int lastSource;
  int lastDestination;

  edge *createEdge(int index, int u, int v, float w);
  void setVertices(int num);
  void relax(vertex *u, vertex *v, float weight, heap &minHeap);
  void dijkstras(int source, int destination, heap &minHeap, stack &newStack);
  void initializeSingleSource(int source);
  void printPathHelper(int source, int destination);
};
