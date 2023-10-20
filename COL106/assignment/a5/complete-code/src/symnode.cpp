/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){

    key = "";
    height = 1;

}

SymNode::SymNode(string k){

    key = k;
    height = 1;

}

SymNode* SymNode::LeftLeftRotation(){

    SymNode* newRoot = right;

    right = newRoot->left;
    newRoot->left = this;

    height = max((left ? left->height : 0), (right ? right->height : 0)) + 1;
    newRoot->height = max((newRoot->left ? newRoot->left->height : 0), (newRoot->right ? newRoot->right->height : 0)) + 1;

    return newRoot;

}

SymNode* SymNode::RightRightRotation(){

    SymNode* newRoot = left;
    
    left = newRoot->right;
    newRoot->right = this;

    height = max((left ? left->height : 0), (right ? right->height : 0)) + 1;
    newRoot->height = max((newRoot->left ? newRoot->left->height : 0), (newRoot->right ? newRoot->right->height : 0)) + 1;

    return newRoot;
    
}

SymNode* SymNode::LeftRightRotation(){

    left = left->LeftLeftRotation();
    return RightRightRotation();

}

SymNode* SymNode::RightLeftRotation(){
    
    right = right->RightRightRotation();
    return LeftLeftRotation();

}

SymNode::~SymNode(){

}