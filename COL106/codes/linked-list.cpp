#include <iostream>

using namespace std;

class node{
public:
    int data;
    node*next;

    node(int val) {
        this->data = val;
        this->next = NULL;
    }
};

void inseartAtHead(node* &head, int val) {
    node* n = new node(val);
    n->next = head; 
    head = n;
}

void insertAtTail(node* &head,int val) {
    node* n = new node(val);
    if(head == NULL) {
        head = n;
        return;
    }
    node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = n;
}

void display(node* head) {
    node* temp = head;
    while(temp->next != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}


int main() {
    node* head = NULL;
    insertAtTail(head, 1);
    insertAtTail(head, 2);
    insertAtTail(head, 3);
    insertAtTail(head, 4);
    insertAtTail(head, 5);
    display(head);
    inseartAtHead(head, 50);
    display(head);

    return 0;
}