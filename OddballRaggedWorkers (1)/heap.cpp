#include "include/heap.h"
#include "include/dataStructures.h"
#include <iostream>

using namespace std;

heap::heap(int capacity) : capacity(capacity), heapSize(0) { //constructor 
  heapArray.resize(capacity);
}

heap::~heap() {} //destructor 

void heap::insert(vertex *v) { //insertion method 
  if (heapSize == capacity) {
    std::cout << "\nOverflow: could not insert key\n";
    return;
  }

  int i = heapSize;
  heapArray[heapSize++] = v;

  while (i != 0 && heapArray[parent(i)]->key > heapArray[i]->key) {
    swap(heapArray[i], heapArray[parent(i)]);
    i = parent(i);
  }
}
bool heap::isEmpty() const { return heapSize == 0; }

vertex *heap::extractMin() { //extract min returns a vertex 
  if (heapSize <= 0) {
    return nullptr;
  }

  if (heapSize == 1) {
    heapSize--;
    return heapArray[0];
  } else {
    vertex *p = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    heapify(0);
    return p;
  }
}

void heap::decreaseKey(int index, int newKey) { //decrease key function
  heapArray[index]->key = newKey;
  while (index != 0 && heapArray[parent(index)]->key > heapArray[index]->key) {
    swap(heapArray[index], heapArray[parent(index)]);
    index = parent(index);
  }
}

int heap::getMin() { return heapArray[0]->key; } //returns the key value of the min not used though

void heap::heapify(int index) { //basic heapify function 
  int l = leftChild(index);
  int r = rightChild(index);

  int smallest = index;

  if (l < heapSize && heapArray[l]->key < heapArray[index]->key) {
    smallest = l;
  }
  if (r < heapSize && heapArray[r]->key < heapArray[smallest]->key) {
    smallest = r;
  }
  if (smallest != index) {
    swap(heapArray[index], heapArray[smallest]);
    heapify(smallest);
  }
}

int heap::parent(int i) { return (i - 1) / 2; }

int heap::leftChild(int i) { return 2 * i + 1; }

int heap::rightChild(int i) { return 2 * i + 2; }

void heap::swap(vertex *&a, vertex *&b) { //helper function for swapping vertex
  vertex *temp = a;
  a = b;
  b = temp;
}
