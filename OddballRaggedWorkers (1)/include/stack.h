#pragma once

#include "dataStructures.h"
#include <vector>

class stack {
public:
  stack();
  ~stack();

  void push(vertex *p);
  vertex *pop();
  vertex *top();
  bool isEmpty();

private:
  std::vector<vertex *> stackArray;
};
