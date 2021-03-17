#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <queue>

#include "graph.h"

void Graph::recursive_DFS(dtype root, bool print_trace, std::map<dtype, bool> &marked) {

  marked[root] = true;

  if (print_trace)
    std::cout << root << " -> ";

  if (adjecent[root].size()) {
    for (int adj : adjecent[root]) {
      if (!marked[adj]) {
        recursive_DFS(adj, print_trace,marked);
      }
    }
  }


  return;
}

void Graph::iterative_DFS(dtype root, bool print_trace) {

  std::map<dtype, bool> marked;
  std::stack<dtype> unseen_vertices;

  unseen_vertices.push(root);
  marked[root] = true;

  if (print_trace)
    std::cout << 0 << " -> ";

  while (unseen_vertices.size() > 0) {

    bool added = false;

    for (std::set<dtype>::iterator it = adjecent[root].cbegin();
         it != adjecent[root].cend(); ++it) {
      if (!marked[*it]) {
        unseen_vertices.push(*it);
        root = *it;
        marked[*it] = true;

        if (print_trace)
          std::cout << *it << " -> ";

        added = true;
        break;
      }
    }

    if (!added) {

      unseen_vertices.pop();
      if (unseen_vertices.size() > 0)
        root = unseen_vertices.top();
    }
  }
  return;
}

void Graph::DFS(dtype root, bool print_trace, bool recursive) { // if print, remove the last ->
  
  if (print_trace) {
    std::cout << "\nDFS with ";
    if (recursive) {
      std::cout << "recursive method:\n";
    } else {
      std::cout << "iterative method:\n";
    }
  }

  if (!recursive)
    iterative_DFS(root, print_trace);

  else{
    std::map<dtype, bool> marked;
    recursive_DFS(root, print_trace, marked);

  }

  if (print_trace) {
    std::cout << "END\n";
  }

  return;
}

void Graph::iterative_DFS(dtype root, bool print_trace, std::set<dtype> &marked_set) {

  std::map<dtype, bool> marked;
  std::stack<dtype> unseen_vertices;

  unseen_vertices.push(root);
  marked[root] = true;
  if(marked.find(root) != marked.end())
    marked_set.insert(root);

  if (print_trace)
    std::cout << root << " -> ";

  while (unseen_vertices.size() > 0) {

    bool added = false;

    for (std::set<dtype>::iterator it = adjecent[root].cbegin();
         it != adjecent[root].cend(); ++it) {
      if (!marked[*it]) {
        unseen_vertices.push(*it);
        root = *it;
        marked[*it] = true;
        marked_set.insert(*it);

        if (print_trace)
          std::cout << *it << " -> ";

        added = true;
        break;
      }
    }

    if (!added) {

      unseen_vertices.pop();
      if (unseen_vertices.size() > 0)
        root = unseen_vertices.top();
    }
  }

  return;
}

void Graph::BFS(dtype root, bool print_trace){

  std::cout << "\nBFS:\n";

  std::map<dtype, bool> marked;
  std::queue<dtype> unseen_vertices;

  unseen_vertices.push(root);
  marked[root] = true;

  if(print_trace)
    std::cout<<root<<" - ";

  while (unseen_vertices.size() > 0){

    dtype head = unseen_vertices.front();
    unseen_vertices.pop();

    if(degree(head)){

      for (std::set<dtype>::iterator it = adjecent[head].cbegin(); it != adjecent[head].cend(); it++) {
        
        if (!marked[*it]){

          unseen_vertices.push(*it);
          marked[*it] = true;
          std::cout<<*it<<" - ";
        }
      }
    }
    
  }

  std::cout << "END\n\n";

  return;
}