#include <iostream>
#include <vector>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isOperand(char c) {
    return ((c >= '0' && c <= '9') || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

vector<string> infixToPrefix(const vector<string>& infixTokens) {
    vector<string> prefix;
    vector<char> operators;
    
    for (int i = infixTokens.size() - 1; i >= 0; i--) {
        const string& token = infixTokens[i];
        
        if (isOperand(token[0])) {
            prefix.insert(prefix.begin(), token); // Operand, add to output
        } else if (isOperator(token[0])) {
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

int main() {
    vector<string> infixExpression1 = {"(", "3", "+", "5", ")", "*", "(", "2", "+", "7", ")"};
    vector<string> prefixExpression1 = infixToPrefix(infixExpression1);
    vector<string> infixExpression2 = {"v", ":=", "(", "13", "+", "(", "2", "+", "(", "2", "/", "51", ")", ")", ")"};
    vector<string> prefixExpression2 = infixToPrefix(infixExpression2);
    // vector<string> infixExpression3 = {"v", ":=", "(", "1", "+", "(", "2", "*","5", ")", ")"};
    vector<string> infixExpression3 = {"v", ":=", "1", "+", "2", "*","x"};
    vector<string> prefixExpression3 = infixToPrefix(infixExpression3);

    cout << "Infix Expression: ";
    for (const string& token : infixExpression1) {
        cout << token << " ";
    }
    cout << endl;

    cout << "Prefix Expression: ";
    for (const string& token : prefixExpression1) {
        cout << token << " ";
    }
    cout << endl;

    cout << "Infix Expression: ";
    for (const string& token : infixExpression2) {
        cout << token << " ";
    }
    cout << endl;

    cout << "Prefix Expression: ";
    for (const string& token : prefixExpression2) {
        cout << token << " ";
    }
    cout << endl;

    cout << "Infix Expression: ";
    for (const string& token : infixExpression3) {
        cout << token << " ";
    }
    cout << endl;

    cout << "Prefix Expression: ";
    for (const string& token : prefixExpression3) {
        cout << token << " ";
    }
    cout << endl;

    return 0;
}
