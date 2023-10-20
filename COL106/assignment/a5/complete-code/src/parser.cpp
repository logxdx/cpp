/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){

    symtable = new SymbolTable();

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

// convert infix expression to prefix expression for easy parsing
vector<string> infixToPrefix(const vector<string>& infixTokens) {

    vector<string> prefix;
    vector<char> operators;
    
    for (int i = infixTokens.size() - 1; i >= 0; i--) {
    
        const string token = infixTokens[i];
        
        if (isOperand(token[0])) {

            prefix.insert(prefix.begin(), token); // Operand, add to output
        
        } else if (isOperatorChar(token[0])) {

            if (token.size() == 2) {
                prefix.insert(prefix.begin(), token);
                continue;
            }
    
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
        if (ch == '-') {
            continue;
        }
        if (isdigit(ch) == false) {
            return false;
        }
    }
    return true;
}

ExprTreeNode* buildExpressionTree(vector<string>& tokens, SymbolTable* symtable) {

    if (tokens.empty()) {
        return nullptr;
    }

    string token = tokens.front();
    tokens.erase(tokens.begin());

    if (isOperator(token)) {
        ExprTreeNode* root = new ExprTreeNode(token, -5);

        // Recursively build left and right subtrees
        root->left = buildExpressionTree(tokens, symtable);
        root->right = buildExpressionTree(tokens, symtable);

        return root;
    } else if (isNumber(token)) {
        return new ExprTreeNode("VAL", stoi(token));
    } else {
        if (token != "del" || token != "ret") {
            symtable->insert(token);
        }
        return new ExprTreeNode(token, -5);
    }

}

void Parser::parse(vector<string> code) {
    
    code[1] = "=";    
    vector<string> code_prefix = infixToPrefix(code);
    expr_trees.push_back(buildExpressionTree(code_prefix, symtable));   

}

Parser::~Parser(){
  
}
