/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include <iostream>

//Write your code below this line

SymbolTable::SymbolTable(){

}

int getHeight(SymNode* node) {
    
    if (node == NULL) {
        return 0;
    }
    return node->height;

}

int getBalance(SymNode* node) {
        
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
    
}

SymNode* balance(SymNode* node) {
    
    if (node == nullptr)
        return node;

    int balanceFactor = getBalance(node);

    // Left heavy
    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0) {
            node->left = node->left->LeftLeftRotation();
        }
        return node->RightRightRotation();
    }
    // Right heavy
    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0) {
            node->right = node->right->RightRightRotation();
        }
        return node->LeftLeftRotation();
    }

    return node;
}

SymNode* findMin(SymNode* node) {

    while (node->left != nullptr) {
        node = node->left;
    }
    return node;

}

SymNode* insert_recursive(SymNode* node, string k) {
    
    if (node == NULL) {
        node = new SymNode(k);
        return node;
    }

    if (k < node->key) {
        node->left = insert_recursive(node->left, k);
    }
    else if (k > node->key) {
        node->right = insert_recursive(node->right, k);
    }
    else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return balance(node);

}

void SymbolTable::insert(string k){

    root = insert_recursive(root, k);
    size++;


}

SymNode* remove_recursive(SymNode* node, string k) {

    if (node == NULL) {
        return node;
    }

    if (k < node->key) {
        node->left = remove_recursive(node->left, k);
    }
    else if (k > node->key) {
        node->right = remove_recursive(node->right, k);
    }
    else {

        if (node->left == NULL && node->right == NULL) {
            delete node;
            return NULL;
        }
        else if (node->left == NULL) {
            SymNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL) {
            SymNode* temp = node->left;
            delete node;
            return temp;
        }
        else {
            SymNode* temp = findMin(node->right);
            node->key = temp->key;
            node->address = temp->address;
            node->right = remove_recursive(node->right, temp->key);
        }

    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return balance(node);

}

void SymbolTable::remove(string k){

    root = remove_recursive(root, k);
    size--;


}

int SymbolTable::search(string k){

    SymNode* current = root;

    while (current != NULL) {
        if (k == current->key) {
            return current->address;
        }
        else if (k < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return -2;

}

void SymbolTable::assign_address(string k,int idx){

    SymNode* current = root;

    while (current != NULL) {
        if (k == current->key) {
            current->address = idx;
            return;
        }
        else if (k < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return;

}

int SymbolTable::get_size(){
    
    return size;

}

SymNode* SymbolTable::get_root(){

    return root;

}

void delete_tree(SymNode* node) {

    if (node != NULL) {
        
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;

    }
    return;
}

SymbolTable::~SymbolTable(){

    if (root != NULL) {
        delete_tree(root);
    }
}

void print_AVL_Tree(SymNode* root, int depth = 0) {
    
        if (root == NULL) {
            return;
        }
    
        print_AVL_Tree(root->right, depth + 1);

        for (int i = 0; i < 2*depth; i++) {
            cout << "   ";
        }
        cout << root->key << endl << endl;
        
        print_AVL_Tree(root->left, depth + 1);

}
