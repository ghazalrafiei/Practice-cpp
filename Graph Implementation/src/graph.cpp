#include <algorithm>
#include <iostream>
#include <map>
#include <stack>

#include "graph.h"

Graph::Graph() {
  v = 0;
  e = 0;
}

Graph::Graph(dtype n) {

  Graph();

  for (int i = 0; i < n; i++) {
    addVertex();
  }
}

Graph::dtype Graph::addVertex() { // returns the no. of added vertices

  for (int i = 0; i < v; i++) {
    if (vertices.find(i) == vertices.cend()) {
      vertices.insert(i);
      adjecent[i] = std::set<dtype>{};
      v++;

      std::cerr << "Vertex " << i << " added\n";
      return i;
    }
  }

  return -1;
}

void Graph::addVertex(int n) {

  for (int i = 0; i < n; i++) {
    addVertex();
  }

  return;
}

bool Graph::vertexExists(dtype v1) {

  return (vertices.find(v1) != vertices.cend());
}

bool Graph::addEdge(dtype v1, dtype v2, Edge_Direction d) {

  if (!(vertexExists(v1) && vertexExists(v2))) {
    return false;
  }

  if (d == Edge_Direction::D_RIGHT) {
    adjecent[v1].insert(
        std::lower_bound(adjecent[v1].cbegin(), adjecent[v1].cend(), v2), v2);
  } else if (d == Edge_Direction::D_LEFT) {
    adjecent[v2].insert(
        std::lower_bound(adjecent[v2].cbegin(), adjecent[v2].cend(), v1), v1);

  } else if (d == Edge_Direction::D_BI) {
    adjecent[v2].insert(
        std::lower_bound(adjecent[v2].cbegin(), adjecent[v2].cend(), v1), v1);

    if (v1 != v2)
      adjecent[v1].insert(
          std::lower_bound(adjecent[v1].cbegin(), adjecent[v1].cend(), v2), v2);
  }

  std::cerr << "Edge added from " << v1 << " to " << v2
            << " with direction: " << d << '\n';
  e += 1;

  return true;
}

bool Graph::deleteVertex(dtype v1) {

  if (!vertexExists(v1)) {
    return false;
  }

  std::set<dtype>::iterator vertex_it = vertices.find(v1);
  vertices.erase(v1); // we sure it exists
  v -= 1;
  adjecent[v1].clear();

  for (dtype v : vertices) {
    std::set<dtype>::iterator adj_it = adjecent[v].find(v1);
    if (adj_it != adjecent[v].cend()) {
      adjecent[v].erase(adj_it);
      e -= 1;
    }
  }

  std::cout << "Vertex " << v1 << " deleted\n";

  return true;
}

bool Graph::edgeExists(dtype v1, dtype v2, Edge_Direction d) {

  if (!(vertexExists(v1) && vertexExists(v2))) {
    std::cerr << "\nat least one of edges did not exist\n";
    return false;
  }

  bool right = 0;
  bool left = 0;

  std::set<dtype>::iterator it = adjecent[v1].find(v2);

  if (it != adjecent[v1].cend()) {
    right = true;

    if (d == Edge_Direction::D_RIGHT) {
      return true;
    }
  }

  if (it != adjecent[v2].cend()) {
    left = true;

    if (d == Edge_Direction::D_LEFT) {
      return true;
    }
  }

  if (right && left) {
    // d is bidirectional return true;
  }

  return false;
}

bool Graph::deleteRightEdge(dtype v1, dtype v2) {
  // returns false if the edge does not exist

  if (!vertexExists(v1) || !vertexExists(v2)) {
    std::cout << "At least one vertex does not exist at all.";
    return false;
  }

  std::set<dtype>::iterator it = adjecent[v1].find(v2);

  if (it != adjecent[v1].cend()) {
    adjecent[v1].erase(it);
  }

  return true;
}

bool Graph::deleteLeftEdge(dtype v1, dtype v2) {
  // we have three because you may want to delete directly

  if (!vertexExists(v1) || !vertexExists(v2)) {
    std::cout << "At least one vertex does not exist at all.";
    return false;
  }

  std::set<dtype>::iterator it = adjecent[v2].find(v1);

  if (it != adjecent[v2].cend()) {
    adjecent[v2].erase(it);
  }

  return true;
}

bool Graph::deleteEdge(dtype v1, dtype v2, Edge_Direction d) {
  // if you want to delete the edge that does not exist, nothing happen

  if (!vertexExists(v1) || !vertexExists(v2)) {
    return false;
  }

  bool deleted = false;

  if (d == 1) {
    deleted = deleteRightEdge(v1, v2);
  } else if (d == -1) {
    deleted = deleteLeftEdge(v1, v2);
  } else if (d == 0) {
    deleted = (deleteLeftEdge(v1, v2) && deleteRightEdge(v1, v2));
  }

  return deleted;
}

unsigned Graph::degree(dtype v1) {
  //-1 if the vertex does not exist

  if (vertexExists(v1))
    return adjecent[v1].size();

  return -1;
}

int Graph::connected_components(bool print_trace) {

  int n_components = 0;
  std::set<dtype> marked;

  dtype start = *vertices.begin();
  marked.insert(start);

  if(print_trace){
    std::cout<<'\n';
  }

  while (marked.size() != vertices.size()) {

    for (auto it = vertices.begin(); it != vertices.end(); it++) {

      if (marked.find(*it) == marked.end()) {

        start = *it;
        iterative_dfs(start, print_trace, marked);
        n_components += 1;

      }
    }
    // if(continue_)
  }

  if (print_trace) {
    std::cout << '\n';
  }

  return n_components;
}

bool Graph::is_connected() { return (connected_components() == 1); }

std::ostream &operator<<(std::ostream &out, const Graph &g) {

  std::cout << "\nAdjecency Lists:\n\n";

  for (int v : g.vertices) {

    std::cout << v << ": ";
    if (g.adjecent.at(v).size())

      for (std::set<Graph::dtype>::iterator it = g.adjecent.at(v).cbegin();
           it != g.adjecent.at(v).cend(); ++it) {
        std::cout << *it << ' ';
      }
    std::cout << '\n';
  }

  return out;
}
