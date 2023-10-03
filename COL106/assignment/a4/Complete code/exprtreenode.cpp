/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode() {
    type = "";
    left = nullptr;
    right = nullptr;
    val = new UnlimitedRational();
    evaluated_value = new UnlimitedRational();
    id = "";
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
    if (t == "+") {type = "ADD";}
    else if (t == "-") {type = "SUB";}
    else if (t == "*") {type = "MUL";}
    else if (t == "/") {type = "DIV";}
    else if (t == "VAL") {type = "VAL";}
    else if (t == "=") {type = "ROOT";}
    else {type = "VAR"; id = t;}

    val = v;
    left = nullptr;
    right = nullptr;
    evaluated_value = v;

}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v) {
    
    if (t == "+") {type = "ADD";}
    else if (t == "-") {type = "SUB";}
    else if (t == "*") {type = "MUL";}
    else if (t == "/") {type = "DIV";}
    else if (t == "VAL") {type = "VAL";}
    else if (t == "=") {type = "ROOT";}
    else {type = "VAR"; id = t;}

    val = new UnlimitedRational(v, new UnlimitedInt(1));
    left = nullptr;
    right = nullptr;
    evaluated_value = new UnlimitedRational(v, new UnlimitedInt(1));
    
}

ExprTreeNode::~ExprTreeNode() {
    delete val;
    delete evaluated_value;
}