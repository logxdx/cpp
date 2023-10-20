/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line
// TODO : Implement correctly

MinHeap::MinHeap() {

    size = 0;
    root = NULL;

}

// void heapifyUp(HeapNode* node) {

//     if (node == NULL)
//         return;

//     while (node->par != NULL && node->val < node->par->val) {
    
//         std::swap(node->val, node->par->val);
//         node = node->par;
    
//     }
// }

// void heapifyDown(HeapNode* node) {
    
//     if (node == NULL)
//         return;

//     while (true) {
    
//         HeapNode* min_node = node;
    
//         if (node->left != NULL && node->left->val < min_node->val) {
//             min_node = node->left;
//         }
    
//         if (node->right != NULL && node->right->val < min_node->val) {
//             min_node = node->right;
//         }

//         if (min_node != node) {
    
//             std::swap(node->val, min_node->val);
//             node = min_node;
    
//         } 
//         else {
//             break;
//         }
//     }
// }

// HeapNode* getParentNode(int index, int size, HeapNode* root) {
//     if (index <= 1 || index > size) {
//         return NULL;  // Index is out of range or it's the root node.
//     }

//     // The parent index of a node at index 'i' in a binary heap is i / 2.
//     return getNodeAt(index / 2, size, root);
// }

// HeapNode* getNodeAt(int index, int size, HeapNode* root) {

//     if (index < 1 || index > size) {
//         return NULL;  // Index is out of range.
//     }

//     HeapNode* current = root;

//     for (int bit = 1 << (size - 2); bit > 0; bit >>= 1) {

//         if (current == NULL) {
//             return NULL;  // Invalid index.
//         }

//         if (index & bit) {
//             current = current->right;
//         } 
//         else {
//             current = current->left;
//         }
//     }
//     return current;
// }

void MinHeap::push_heap(int num) {
        
    // HeapNode* new_node = new HeapNode(num);

    // if (root == NULL) {
    //     root = new_node;
    // } 
    // else {
    
    //     HeapNode* parent = getParentNode(size + 1, size);
    
    //     if (parent->left == NULL) {
    //         parent->left = new_node;
    //     } 
    //     else {
    //         parent->right = new_node;
    //     }
        
    //     new_node->par = parent;
    //     heapifyUp(new_node);
    
    // }
    // size++;

}

int MinHeap::get_min() {

    // if (root == NULL) {
    //     return -1;
    // }
    // return root->val;
    return 0;

}

void MinHeap::pop() {

    // if (root == NULL) {
    //     return;
    // }

    // HeapNode* last_node = getNodeAt(size);

    // if (last_node != root) {
        
    //     root->val = last_node->val;
    //     HeapNode* parent = last_node->par;
        
    //     if (parent->left == last_node) {
    //         parent->left = NULL;
    //     } 
    //     else {
    //         parent->right = NULL;
    //     }
    
    //     delete last_node;
    //     heapifyDown(root);

    // } 
    // else {

    //     delete root;
    //     root = NULL;

    // }
    // size--;

}

MinHeap::~MinHeap() {
    
}