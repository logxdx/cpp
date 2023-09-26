/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable() {

    size = 0;
    root = nullptr;
}

SymbolTable::~SymbolTable() {
   
    delete_tree(root);
}

void delete_tree(SymEntry* root) {
    
    if (root != nullptr) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

void SymbolTable::insert(string k, UnlimitedRational* v) {
    
    root = insert_recursive(root, k, v);
    size++;

}

SymEntry* insert_recursive(SymEntry* node, string k, UnlimitedRational* v) {
   
    if (node == nullptr) {
        node = new SymEntry(k, v);
    }
    else if (k < node->key) {
        node->left = insert_recursive(node->left, k, v);
    }
    else if (k > node->key) {
        node->right = insert_recursive(node->right, k, v);
    }
    else {
        node->val = v;  // may not be required
    }
    return node;

}

void SymbolTable::remove(string k) {

    root = remove_recursive(root, k);
    size--;

}

SymEntry* remove_recursive(SymEntry* node, string k) {
   
    if (node == nullptr) {
        return node;
    }
    else if (k < node->key) {
        node->left = remove_recursive(node->left, k);
    }
    else if (k > node->key) {
        node->right = remove_recursive(node->right, k);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr) {
            SymEntry* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) {
            SymEntry* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            // Inorder successor
            SymEntry* temp = node->right;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            node->key = temp->key;
            node->val = temp->val;
            node->right = remove_recursive(node->right, temp->key);
            delete temp;
        }
    }
    return node;

}

UnlimitedRational* SymbolTable::search(string k) {

    return search_recursive(root, k);

}

UnlimitedRational* search_recursive(SymEntry* node, string k) {
 
    if (node == nullptr) {
        return nullptr;
    }
    else if (k < node->key) {
        return search_recursive(node->left, k);
    }
    else if (k > node->key) {
        return search_recursive(node->right, k);
    }
    else {
        return node->val;
    }

}

int SymbolTable::get_size() {
    
    return size;

}

SymEntry* SymbolTable::get_root() {
    
    return root;

}
