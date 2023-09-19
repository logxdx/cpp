#include "list.h"

List::List(): size(0) {
    sentinel_head = new Node(true);
    sentinel_tail = new Node(true);
    sentinel_head->next = sentinel_tail;
    sentinel_head->prev = nullptr;
    sentinel_tail->prev = sentinel_head;
    sentinel_tail->next = nullptr;
}

List::~List() {
    while (size > 0) {
        delete_tail();
    }
    delete sentinel_head;
    delete sentinel_tail;
}

void List::insert(int v) {
    Node* new_node = new Node(v, sentinel_tail, sentinel_tail->prev);
    sentinel_tail->prev->next = new_node;
    sentinel_tail->prev = new_node;
    size++;
}

int List::delete_tail() {
    if (size == 0) {
        return -1;
    }
    
    Node* node_to_delete = sentinel_tail->prev;

    int value = node_to_delete->get_value();
    node_to_delete->prev->next = sentinel_tail;
    sentinel_tail->prev = node_to_delete->prev;

    node_to_delete = nullptr;
    delete node_to_delete;
    size--;
    
    return value;
}

int List::get_size() {
    return size;
}

Node* List::get_head() {
    return sentinel_head;
}
