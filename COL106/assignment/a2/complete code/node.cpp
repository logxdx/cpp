#include "node.h"
#include <iostream>

using namespace std;

Node::Node(bool sentinel): is_sentinel(sentinel), next(nullptr), prev(nullptr) {}

Node::Node(int v, Node* nxt, Node* prv): value(v), is_sentinel(false), next(nxt), prev(prv) {}

bool Node::is_sentinel_node() {
    return is_sentinel;
}

int Node::get_value() {
    return value;
}
