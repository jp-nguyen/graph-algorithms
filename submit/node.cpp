#include "node.h"

Node :: Node() : id(-1) {}

Node :: Node(int i) : id(i) {}

Node :: Node(const Node& n) : id(n.id) {}

Node& Node :: operator = (const Node& n) {
    id = n.id;
    return *this;
}

bool Node :: operator == (const Node& n) const {
    return id == n.id;
}

bool Node :: operator < (const Node& n) const {
    return id < n.id;
}

void Node :: print(ostream& out) const {
    out << id;
}
ostream& operator << (ostream& out, const Node& n) {
    n.print(out);
    return out;
}
Node :: ~Node() {}