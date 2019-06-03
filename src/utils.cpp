#include "utils.h"

void create_empty_sheet(Algorithm a) {
    ofstream file;
    switch(a) {
        case DIAMETER: 
            file.open("diameter.csv", ofstream :: trunc);
            file << "n,diameter" << endl;
        case CLUSTER:
            file.open("cluster.csv", ofstream :: trunc);
            file << "n,coefficient" << endl;
            break;
        case DEGREE:
            file.open("degree.csv", ofstream :: trunc);
            file << "n,degree,count" << endl;
            break;
    } 
    file.close();
}

void write_to_sheet(Algorithm a, int n, float data, map<int, int>* degrees) {
    ofstream file;
    map<int, int> :: iterator it;
    if (a == DIAMETER || a == CLUSTER) {
        file.open(a == DIAMETER ? "diameter.csv" : "cluster.csv", ofstream :: app);
        file << n << "," << data << endl;
    } else {
        file.open("degree.csv", ofstream :: app);
        for (it = (*degrees).begin(); it != (*degrees).end(); ++it)
            file << n << "," << it->first << "," << it->second << endl;
    }
    file.close();
}

double get_random_float() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_real_distribution<double> range(0.0, 1.0);
    double r;

    while ((r = range(gen)) == 1.0);
    return r; 
}

vector<degen> get_degeneracy_ordering(Graph g) {
    vector<degen> L;
    map<Node, int> d;
    map<Node, bool> H; 
    int n = g.get_num_nodes();
    int max_degree = -1;

    for (int i = 1; i <= n; ++i) {
        Node v(i);
        H[v] = false;
        d[v] = g.get_neighbors(v).size();
        if (max_degree < d[v])
            max_degree = d[v];
    }

    vector<vector<Node>> D(max_degree + 1);

    for (int j = 1; j <= n; ++j) {
        Node v(j);
        D[d[v]].push_back(v);
    }

    for (int k = 0; k < n; ++k) {
        int i = 0;
        while (D[i].empty()) ++i;

        Node v = D[i].back();
        vector<Node> neighbors;

        D[i].pop_back();
        H[v] = true;

        for (auto w: g.get_neighbors(v)) {
            if (!H[w]) {
                D[d[w]].erase(remove(D[d[w]].begin(), D[d[w]].end(), w));
                D[--d[w]].push_back(w);
                neighbors.push_back(w);
            }
        }

        L.push_back({v, neighbors});
    }
    reverse(L.begin(), L.end());
    return L;
}