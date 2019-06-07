#include "project3.h"
#include "graph.h"
#include "node.h"
#include "tests.h"
#include "utils.h"
using namespace std;

#define REPS 3

double get_p(int n) {
    return 2 * log(n) / n;
}

void run_diameters() {
    Graph g;
    float diameter;

    create_empty_sheet(DIAMETER);
    for (int n = 10; n <= 100000; n *= 2) {
        diameter = 0;
        for (int i = 0; i < REPS; ++i) {
            g = create_erdos_renyi_graph(n, get_p(n));
            diameter += (float) get_diameter(g);
        }
        diameter /= REPS;
        cout <<  "From " << n << " nodes, got diameter " << diameter << endl;
        write_to_sheet(DIAMETER, n, diameter, 0, nullptr);
    }
}

void run_clustering_coefficients() {
    Graph g;
    float coeff;
    double dens;

    create_empty_sheet(CLUSTER);
    for (int n = 10; n <= 100000; n *= 2) {
        coeff = 0;
        dens = 0;
        for (int i = 0; i < REPS; ++i) {
            g = create_erdos_renyi_graph(n, get_p(n));
            coeff += get_clustering_coefficient(g);
            dens += g.get_num_edges() / (n * (n - 1) / 2.0);
        }
        coeff /= REPS;
        dens /= REPS;
        cout <<  "From " << n << " nodes, got coefficient " << coeff 
            << " and edge density " << dens << endl;
        write_to_sheet(CLUSTER, n, coeff, dens, nullptr);
    }
}

void run_degree_distributions() {
    Graph g;
    map<int, int> degrees;

    create_empty_sheet(DEGREE);
    for (int n = 1000; n <= 100000; n *= 10) {
        g = create_erdos_renyi_graph(n, get_p(n));
        degrees = get_degree_distribution(g);
        write_to_sheet(DEGREE, n, 0, 0, &degrees);
    }
}

void test_diameter() {
    Graph graph1 = make_graph(6, 
        vector<int>{2, 2, 2, 2, 2, 1, 1, 3, 4}, 
        vector<int>{1, 3, 4, 5, 6, 3, 4, 6, 5});
    Graph graph2 = make_graph(7, 
        vector<int>{1, 1, 1, 1, 2, 4, 4, 4 }, 
        vector<int>{2, 3, 4, 7, 5, 5, 6, 7});
    Graph graph3 = make_graph(12, 
        vector<int>{3, 3, 3, 3, 7, 7, 7, 7, 6, 6, 6, 9, 8 }, 
        vector<int>{4, 8, 2, 7, 2, 6, 10, 11, 2, 1, 9, 5, 12});
    
    for (int i = 0; i < 100; ++i) {
        assert(get_diameter(graph1) == 2);
        assert(get_diameter(graph2) == 3);
        assert(get_diameter(graph3) == 6);
    }
}

void test_clustering_coefficient() {
    
    Graph graph1 = make_graph(5, 
        vector<int>{1, 1, 2, 2, 3, 3, 4},
        vector<int>{2, 3, 4, 5, 4, 5, 5});
    Graph graph2 = make_graph(5,
        vector<int>{1, 1, 2, 3, 3}, 
        vector<int>{2, 3, 3, 4, 5});

    cout << get_clustering_coefficient(graph1) << endl; // should be 0.461538
    cout << get_clustering_coefficient(graph2) << endl; // should be 0.375
}

void generate_nodes_and_probability() {
    create_empty_sheet(NONE);
    for (int n = 10; n <= 100000; n *= 2)
        write_to_sheet(NONE, n, get_p(n), 0, nullptr);
    for (int n = 1000; n <= 100000; n *= 10)
        write_to_sheet(NONE, n, get_p(n), 0, nullptr);
}

int main() {
    run_tests();

    run_diameters();
    run_clustering_coefficients();
    run_degree_distributions();

    // generate_nodes_and_probability();

    // test_diameter();
    // test_clustering_coefficient();
    
    return 0;
}
