#include "project3.h"
#include "graph.h"
#include "utils.h"
using namespace std;

int get_diameter(Graph graph) {
    int n = graph.get_num_nodes();
    set<Node> explored;
    Node s(get_random_int(1, n));
    int max = 0;
    bfs b;

    for (int i = 0; i < 5 && explored.size() < n; ++i) {
        while (explored.find(s) != explored.end())
            s = Node(get_random_int(1, n));
        explored.insert(s);

        while (true) {
            b = get_breadth_first_search(graph, s);
            explored.insert(b.n);
            if (max >= b.dist)
                break;
            s = b.n;
            max = b.dist;
        }
    }

    return max;
}

float get_clustering_coefficient(Graph graph) {
    float dem = 0;
    int num = 0, n = graph.get_num_nodes(), deg, m;
    vector<degen> L = get_degeneracy_ordering(graph);

    for (int i = 1; i <= n; ++i) {
        deg = graph.get_neighbors(Node(i)).size();
        dem += deg * (deg - 1.0) / 2.0;
    }

    for (auto v: L) {
        m = v.neighbors.size();
        for (int i = 0; i < m - 1; ++i)
            for (int j = i + 1; j < m; ++j)
                if (graph.is_neighbor(v.neighbors[i], v.neighbors[j]))
                    ++num;
    }

    return (float) 3 * num / dem;
}

map<int, int> get_degree_distribution(Graph graph) {
    map<int, int> degrees;
    int n = graph.get_num_nodes();

    for (int i = 1; i <= n; ++i)
        degrees[graph.get_neighbors(Node(i)).size()]++;

    return degrees;
}