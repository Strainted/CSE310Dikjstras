#pragma once

#include "dataStructures.h"
#include <vector>

class heap {
public:
  heap(int capacity);
  ~heap();

  void insert(vertex *v);
  vertex *extractMin();
  void decreaseKey(int index, int newKey);
  bool isEmpty() const;
  int getMin();

private:
  void heapify(int index);
  int parent(int i);
  int leftChild(int i);
  int rightChild(int i);
  void swap(vertex *&a, vertex *&b);

private:
  int capacity;
  int heapSize;
  std::vector<vertex *> heapArray;
};
