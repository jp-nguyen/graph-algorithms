#ifndef NODE_H
#define NODE_H

#include "project3.h"
#include <iostream>
using namespace std;

class Node {
public:
    int id;
    Node();
    Node(int i);
    Node(const Node& n);
    Node& operator = (const Node& n);
    bool operator == (const Node& n) const;
    bool operator < (const Node& n) const;
    void print(ostream& out) const;
    friend ostream& operator << (ostream& out, const Node& n);
    ~Node();
};

#endif