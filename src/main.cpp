#include "project3.h"
#include "graph.h"
#include "node.h"
#include "tests.h"
#include "utils.h"
using namespace std;

#define REPS 3

double get_r(int n) {
    return 2 * log(n) / n;
}

void run_diameters() {
    Graph g;
    float diameter;

    // create_empty_sheet(DIAMETER);
    for (int n = 10; n <= 100000; n *= 10) {
        diameter = 0;
        for (int i = 0; i < REPS; ++i) {
            g = create_erdos_renyi_graph(n, get_r(n));
            diameter += (float) get_diameter(g);
        }
        diameter /= REPS;
        cout <<  "From " << n << " nodes, got diameter " << diameter << endl;
        // write_to_sheet(DIAMETER, n, diameter, nullptr);
    }
}

void run_clustering_coefficients() {
    Graph g;
    float coeff;

    create_empty_sheet(CLUSTER);
    for (int n = 10; n <= 100000; n *= 2) {
        coeff = 0;
        for (int i = 0; i < REPS; ++i) {
            g = create_erdos_renyi_graph(n, get_r(n));
            coeff += get_clustering_coefficient(g);
        }
        coeff /= REPS;
        cout <<  "From " << n << " nodes, got coefficient " << coeff << endl;
        write_to_sheet(CLUSTER, n, coeff, nullptr);
    }
}

void run_degree_distributions() {
    Graph g;
    map<int, int> degrees;

    create_empty_sheet(DEGREE);
    for (int n = 1000; n <= 100000; n *= 10) {
        g = create_erdos_renyi_graph(n, get_r(n));
        degrees = get_degree_distribution(g);
        write_to_sheet(DEGREE, n, 0, &degrees);
    }
}

int main() {
    run_tests();

    // run_diameters();
    run_clustering_coefficients();
    run_degree_distributions();
    /* 
    vector<int> u{1, 1, 2, 2, 3, 3, 4};
    vector<int> v{2, 3, 4, 5, 4, 5, 5}; 
    Graph g =  make_graph(5, u, v);
    float coeff = get_clustering_coefficient(g);

    cout << coeff << endl;
    */

    return 0;
}
