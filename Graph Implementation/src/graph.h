#ifndef __GRAPH__
#define __GRAPH__

#include <map>
#include <set>
#include <vector>

enum Edge_Direction {

  D_LEFT = -1,
  D_RIGHT = 1,
  D_BI = 0,
  
};

enum Trace_Method {

  T_DFS = 1,
  T_BFS = 2,

};

class Graph {

public:
  typedef unsigned dtype;
  dtype v; // count of vertices
  dtype e; // count of edges

  std::set<dtype> vertices;
  std::map<dtype, std::set<dtype>> adjecent; // each node goes to its set of adjecents

  Graph();
  Graph(dtype n);

  dtype addVertex();
  void addVertex(int n);

  bool vertexExists(dtype v1);
  bool deleteVertex(dtype v);

  bool addEdge(dtype v1, dtype v2, Edge_Direction d = D_BI);
  bool edgeExists(dtype v1, dtype v2, Edge_Direction d = D_BI);
  bool deleteEdge(dtype v1, dtype v2, Edge_Direction d = D_BI);
  bool deleteRightEdge(dtype v1, dtype v2);
  bool deleteLeftEdge(dtype v1, dtype v2);

  unsigned degree(dtype v1);

  void DFS(dtype root, bool print_trace = false, bool recursive = 0);
  
  private:
  void recursive_DFS(dtype root, bool print_trace, std::map<dtype, bool> &marked);
  void iterative_DFS(dtype root, bool print_trace = false); 
  void iterative_DFS(dtype root, bool print_trace, std::set<dtype> &marked);
  
  
  public:
  void BFS(dtype root, bool print_trace = false);

  int connected_components(bool print_trace = false); // uses iterative dfs
  bool is_connected();

      // void Kruskal();
      // void dijkstra();
      // void belman_Ford();
      // void maxflow();

  friend std::ostream &operator<<(std::ostream &out, const Graph &g);
};

#endif