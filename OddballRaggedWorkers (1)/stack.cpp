#include <iostream>
#include <stdexcept>
#include <vector>

#include "include/dataStructures.h"
#include "include/stack.h"

stack::stack() {} //constructor 

stack::~stack() {}//destructor 

void stack::push(vertex *p) { stackArray.push_back(p); }//simple push function 

vertex *stack::pop() { //pop function returns a vertex 
  if (isEmpty()) {
    throw std::out_of_range("Stack_Underflow");
  }
  vertex *p = stackArray.back();
  stackArray.pop_back();
  return p;
}

vertex *stack::top() { //returns the top of the stack as a vertex 
  if (isEmpty()) {
    throw std::out_of_range("Stack is Empty");
  }

  return stackArray.back();
}

bool stack::isEmpty() { return stackArray.empty(); }//checks if stack is empty 
