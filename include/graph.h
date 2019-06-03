#ifndef GRAPH_H
#define GRAPH_H

#include "project3.h"
#include "node.h"
#include <iostream>
using namespace std;

class Graph : public AbstractGraph {
    int num_nodes;
    vector<Node>* adj_list;
public:
    Graph();
    Graph(int n);
    Graph(const Graph& g);
    Graph& operator = (const Graph& g);
    int get_num_nodes(); 
    int get_num_edges(); 
    bool is_neighbor(Node u, Node v) ;
    vector<Node> get_neighbors(Node u); 
    map<int, Node> get_id_to_node_map();
    void add_edge(Node u, Node v);
    void print(ostream& out) const;
    friend ostream& operator << (ostream& out, const Graph& g);
    ~Graph(); 
};

#endif