#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <map>
#include "graph.h"
#include "node.h"
using namespace std;

enum Algorithm { DIAMETER, CLUSTER, DEGREE };

void create_empty_sheet(Algorithm a);
void write_to_sheet(Algorithm a, int n, float data, map<int, int>* degrees);
double get_random_float();

struct degen {
    Node n;
    vector<Node> neighbors;
};

vector<degen> get_degeneracy_ordering(Graph g);

#endif