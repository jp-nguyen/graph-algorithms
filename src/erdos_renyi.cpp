#include "project3.h"
#include "graph.h"
#include "utils.h"
#include <cmath>

Graph create_erdos_renyi_graph(int n, float p) {
    /* edges to add */
    vector<int> src;
    vector<int> dest;

    /* the algorithm */ 
    int v = 1, w = -1;
    float r;

    while (v < n) {
        r = get_random_float();
        w = w + 1 + int(floor(log(1 - r) / log(1 - p)));
        while (w >= v && v < n)
            w -= v++;
        if (v < n) {
            src.push_back(v + 1);
            dest.push_back(w + 1);
        }
    }

    cout << "...creating Erdos Renyi Graph with " << n 
        << " nodes and a probability of " << p << "..." << endl;

    return make_graph(n, src, dest);
}