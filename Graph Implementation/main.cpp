#include "src/graph.h"
#include <iostream>

int main() {
  unsigned test_graph_node_size = 6; // 0-base
  Graph my_graph = Graph(test_graph_node_size);

  my_graph.addEdge(4, 0);
  my_graph.addEdge(0, 2);
  my_graph.addEdge(1, 3);
  my_graph.addEdge(2, 3);
  my_graph.addEdge(2, 4);

  my_graph.DFS(0, true, false);


  my_graph.addVertex();
  my_graph.addVertex();

  my_graph.addEdge(6, 7);
  my_graph.addEdge(5, 6);

  std::cout << my_graph;

  my_graph.DFS(0, true, true);
  my_graph.DFS(0, true, true);
  my_graph.BFS(0, true);

  my_graph.deleteVertex(3);

  std::cout << my_graph;

  std::cout<< "\nThe graph has "<<my_graph.connected_components()<<" components.\n";
  std::cout<<"\nIs the graph connected? "<<(my_graph.is_connected()? "Yes." : "No.")<<'\n';



  return 0;
}