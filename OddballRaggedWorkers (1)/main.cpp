#include "include/graph.h"
#include "include/heap.h"
#include "include/stack.h"
#include <iostream>
#include <limits>
#include <string>

int main() {
  graph myGraph;             // Create an instance of the graph class
  heap *minHeap = nullptr;   // create minHeap
  stack *newStack = nullptr; // create stack
  int instruction;

  do {
    std::cout << "Homework 5 - CSE 310\n";
    std::cout << "1. Read the graph from the file\n";
    std::cout << "2. Print ADJ\n";
    std::cout << "3. Single Source, enter the starting node number\n";
    std::cout << "4. Single Pair, enter the starting node and the ending done "
                 "numbers\n";
    std::cout
        << "5. Print Path, enter the starting node and ending done numbers\n";
    std::cout
        << "6. Print Length, enter the starting node and ending done numbers\n";
    std::cout
        << "7. Print Path, enter the starting node and ending done numbers\n";
    std::cout << "8. Stop\n";
    std::cout << "\n\n Enter option 1-8: ";

    std::cin >> instruction;

    switch (instruction) {
    case 1: {
      myGraph.setLastPath(1);
      std::string fileName;
      bool directed;
      int flag;
      std::cin.ignore();
      // Get user input for file name, directed, and flag
      std::cout << "Enter file name: ";
      std::getline(std::cin, fileName);

      std::cout << "Is the graph directed? (1 for true, 0 for false): ";
      std::cin >> directed;

      std::cout << "Enter flag: ";
      std::cin >> flag;
      std::cout << "\n";

      // Call the readGraphFile function
      int numVertices =
          myGraph.readGraphFile(fileName, directed, flag, myGraph);
      minHeap = new heap(numVertices);
      newStack = new stack();
      break;
    }
    case 2: {

      myGraph.setLastPath(2);
      myGraph.printAdj(myGraph.getVertList(), myGraph.getAdjacencyList(),
                       myGraph.getVertices());
      break;
    }
    case 3: {

      myGraph.setLastPath(3);
      int source;
      std::cout << "Enter the starting node number: ";
      std::cin >> source;

      myGraph.setLastSource(source);

      // Call the singleSource function
      myGraph.singleSource(source, *minHeap, *newStack);
      break;
    }
    case 4: {

      myGraph.setLastPath(4);
      int s;
      int d;
      std::cout << "enter the starting vertex value: ";
      std::cin >> s;
      std::cout << "Enter the ending vertex value: ";
      std::cin >> d;

      myGraph.setLastSource(s);
      myGraph.setLastDestination(d);
      myGraph.singlePair(s, d, *minHeap, *newStack);
      break;
    }
    case 5: {

      int source, destination;
      std::cout << "Enter the starting node number: ";
      std::cin >> source;
      std::cout << "Enter the ending node number: ";
      std::cin >> destination;

      // Call the printPath function
      myGraph.printPath(source, destination, *newStack);
      break;
    }

    case 6: {
      int source, destination;
      std::cout << "Enter the starting node number: ";
      std::cin >> source;
      std::cout << "Enter the ending node number: ";
      std::cin >> destination;

      // Call the printLength function
      myGraph.printLength(source, destination);
      break;
    }
    case 7: {
      int source;
      std::cout << "Enter the starting node number: ";
      std::cin >> source;

      // Call the printPath function
      myGraph.printPathHelper(source, *newStack);
      break;
    }
    default: {
      std::cerr << "Invalid instruction." << std::endl;
      break;
    }
    }

    // Clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  } while (instruction != 8);

  return 0;
}
