#include "graph.h"

Graph :: Graph ()
    : num_nodes(0), adj_list(nullptr) {}

Graph :: Graph(int n)
    : num_nodes(n), adj_list(new vector<Node>[n]) {}

Graph :: Graph(const Graph& g)
    : num_nodes(g.num_nodes), adj_list(new vector<Node>[g.num_nodes]) {
    for (int i = 0; i < g.num_nodes; ++i)
        adj_list[i] = g.adj_list[i];
}

Graph& Graph :: operator = (const Graph& g) {
    num_nodes = g.num_nodes;
    vector<Node>* temp = adj_list;
    adj_list = new vector<Node>[g.num_nodes];
    delete [] temp;
    for (int i = 0; i < g.num_nodes; ++i)
        adj_list[i] = g.adj_list[i];
    return *this;
}

int Graph :: get_num_nodes() {
    return num_nodes;
}

int Graph :: get_num_edges() {
    int num_edges = 0;
    for (int i = 0; i < num_nodes; ++i)
        num_edges += adj_list[i].size();
    return num_edges / 2;
}

bool Graph :: is_neighbor(Node u, Node v) {
    for (auto n: adj_list[u.id - 1])
        if (n == v)
            return true;
    return false;
}

vector<Node> Graph :: get_neighbors(Node u) {
    return adj_list[u.id - 1];
}

map<int, Node> Graph :: get_id_to_node_map() {
    map<int, Node> result;
    for (int i = 1; i <= num_nodes; ++i)
        result[i] = Node(i);
    return result;
}

void Graph :: add_edge(Node u, Node v) {
    /* unsafely assuming valid nodes */
    adj_list[u.id - 1].push_back(v);
    adj_list[v.id - 1].push_back(u);
}

void Graph :: print(ostream& out) const {
    for (int i = 0; i < num_nodes; ++i) {
        out << "Node " << i + 1 << ": ";
        for (auto v: adj_list[i])
            out << v << " ";
        out << endl;
    }
}

ostream& operator << (ostream& out, const Graph& g) {
    g.print(out);
    return out;
}

Graph :: ~Graph() {
    delete [] adj_list;
}

Graph make_graph(int num_nodes, vector<int> u, vector<int> v) {
    Graph g(num_nodes);
    int num_edges = u.size();
    for (int i = 0; i < num_edges; ++i)
        g.add_edge(u[i], v[i]);
    return g;
}