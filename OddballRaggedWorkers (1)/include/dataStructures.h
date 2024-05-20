#pragma once

struct vertex {
  int pi; // parent
  int key;
  int distance; // shortest dist of this vertex from src vertex
  int index;
};

struct edge {
  int index;
  int u;   // start
  int v;   // end
  float w; // weight
  edge *next;
};
