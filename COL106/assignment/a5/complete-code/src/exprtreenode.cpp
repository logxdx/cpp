/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type = "";
    id = "";
    num = 0;
}

ExprTreeNode::ExprTreeNode(string t, int v){
    
    id = "";
    
    if (t == "+") {type = "ADD"; id = "+";}
    else if (t == "-") {type = "SUB"; id = "-";}
    else if (t == "*") {type = "MUL"; id = "*";}
    else if (t == "/") {type = "DIV"; id = "/";}
    else if (t == "VAL") {type = "VAL";}
    else if (t == "=") {type = "ROOT"; id = "=";}
    else if (t == "del") {type = "DEL";}
    else if (t == "ret") {type = "RET";}
    else {type = "VAR"; id = t;}

    num = v;
    left = NULL;
    right = NULL;

}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right;
}

