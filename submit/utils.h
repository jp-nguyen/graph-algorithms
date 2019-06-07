#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>
#include "graph.h"
#include "node.h"
using namespace std;

enum Algorithm { DIAMETER, CLUSTER, DEGREE, NONE };

void create_empty_sheet(Algorithm a);
void write_to_sheet(Algorithm a, int n, float data, float dens, map<int, int>* degrees);
double get_random_float();
int get_random_int(int lb, int ub);

struct degen {
    Node n;
    vector<Node> neighbors;
};

struct bfs {
    Node n;
    int dist;
};

vector<degen> get_degeneracy_ordering(Graph g);
bfs get_breadth_first_search(Graph g, Node s);

#endif