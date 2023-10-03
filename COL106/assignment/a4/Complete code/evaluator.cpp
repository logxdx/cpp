/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    delete symtable;
}

bool isOperatorChar(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}

bool isOperand(char c) {
    return ((c >= '0' && c <= '9') || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '=') return -1;
    return -5;
}

vector<string> infixToPrefix(const vector<string>& infixTokens) {
    vector<string> prefix;
    vector<char> operators;
    
    for (int i = infixTokens.size() - 1; i >= 0; i--) {
        const string token = infixTokens[i];
        
        if (isOperand(token[0])) {
            prefix.insert(prefix.begin(), token); // Operand, add to output
        } else if (isOperatorChar(token[0])) {
            while (!operators.empty() && precedence(operators.back()) >= precedence(token[0])) {
                string op(1, operators.back());
                prefix.insert(prefix.begin(), op);
                operators.pop_back();
            }
            operators.push_back(token[0]);
        } else if (token == ")") {
            operators.push_back(token[0]);
        } else if (token == "(") {
            while (!operators.empty() && operators.back() != ')') {
                string op(1, operators.back());
                prefix.insert(prefix.begin(), op);
                operators.pop_back();
            }
            operators.pop_back(); // Pop the ')'
        }
    }
    
    while (!operators.empty()) {
        string op(1, operators.back());
        prefix.insert(prefix.begin(), op);
        operators.pop_back();
    }
    
    return prefix;
}

bool isOperator(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "=";
}

bool isNumber(string c) {
    for (char const &ch : c) {
        if (isdigit(ch) == false) {
            return false;
        }
    }
    return true;
}

ExprTreeNode* buildExpressionTree(vector<string>& tokens) {

    if (tokens.empty()) {
        return nullptr;
    }

    string token = tokens.front();
    tokens.erase(tokens.begin());

    if (isOperator(token)) {
        ExprTreeNode* root = new ExprTreeNode(token, new UnlimitedRational());

        // Recursively build left and right subtrees
        root->left = buildExpressionTree(tokens);
        root->right = buildExpressionTree(tokens);

        return root;
    } else if (isNumber(token)) {
        return new ExprTreeNode("VAL", new UnlimitedInt(token));
    } else {
        return new ExprTreeNode(token, new UnlimitedRational());
    }
}

void Evaluator::parse(vector<string> code) {
    
    code[1] = "=";    
    vector<string> code_prefix = infixToPrefix(code);
    expr_trees.push_back(buildExpressionTree(code_prefix));
}

UnlimitedRational* answer_nikalne_wali_machine(ExprTreeNode* exp_tree, SymbolTable* sym_t) {

    if (exp_tree->type == "ADD") {
        UnlimitedRational* answer =  UnlimitedRational::add(answer_nikalne_wali_machine(exp_tree->left, sym_t), answer_nikalne_wali_machine(exp_tree->right, sym_t));
        exp_tree->evaluated_value = answer;
        return answer;
    }

    else if (exp_tree->type == "SUB") {
        UnlimitedRational* answer = UnlimitedRational::sub(answer_nikalne_wali_machine(exp_tree->left, sym_t), answer_nikalne_wali_machine(exp_tree->right, sym_t));
        exp_tree->evaluated_value = answer;
        return answer;
    }

    else if (exp_tree->type == "MUL") {
        UnlimitedRational* answer =  UnlimitedRational::mul(answer_nikalne_wali_machine(exp_tree->left, sym_t), answer_nikalne_wali_machine(exp_tree->right, sym_t));
        exp_tree->evaluated_value = answer;
        return answer;
    }

    else if (exp_tree->type == "DIV") {
        UnlimitedRational* answer = UnlimitedRational::div(answer_nikalne_wali_machine(exp_tree->left, sym_t), answer_nikalne_wali_machine(exp_tree->right, sym_t));
        exp_tree->evaluated_value = answer;
        return answer;
    }
    
    else if (exp_tree->type == "VAL") {
        return exp_tree->evaluated_value;
    }

    else if (exp_tree->type == "VAR") {
        UnlimitedRational* answer = sym_t->search(exp_tree->id);
        exp_tree->evaluated_value = answer;
        return answer;
    }  

    return nullptr;
}

void Evaluator::eval() {

    ExprTreeNode* root = expr_trees[expr_trees.size()-1];

    string s = root->left->id;

    UnlimitedRational* a = answer_nikalne_wali_machine(root->right,symtable);

    symtable->insert(s,a);
    
    return;
}
