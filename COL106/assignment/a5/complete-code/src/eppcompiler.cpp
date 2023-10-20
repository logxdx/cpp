/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#include <iostream>

//Write your code below this line

EPPCompiler::EPPCompiler(){

}

EPPCompiler::EPPCompiler(string out_file, int mem_limit){
    
    output_file = out_file;
    memory_size = mem_limit;
    mem_loc.resize(memory_size, -37);

}

bool isOperatoR(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/";
}

void EPPCompiler::compile(vector<vector<string>> code){

    vector<string> commands;
    
    for (vector<string> expr : code) {

        targ.parse(expr);
        
        vector<string> TargCommands = generate_targ_commands();
        
        for (string i : TargCommands) {
            commands.push_back(i);
        }
        
    }   

    write_to_file(commands);

}

void generateCodeForNode(const ExprTreeNode* node, vector<string>& commands, vector<int>& mem_loc, SymbolTable* symtable) {
    
    if (node == nullptr) {
        return;
    }

    if (node->type == "VAL") {
        commands.push_back("PUSH " + to_string(node->num));
    } 
    else if (isOperatoR(node->id)) {

        generateCodeForNode(node->right, commands, mem_loc, symtable);
        generateCodeForNode(node->left, commands, mem_loc, symtable);

        if (node->id == "+") {
            commands.push_back("ADD");
        } else if (node->id == "-") {
            commands.push_back("SUB");
        } else if (node->id == "*") {
            commands.push_back("MUL");
        } else if (node->id == "/") {
            commands.push_back("DIV");
        }

    } 
    else if (node->type == "VAR") {

        int mem_address = symtable->search(node->id);

        if (mem_address == -1) {
            for (int i = 0; i<mem_loc.size(); i++) {
                if (mem_loc[i] == -37) {
                    mem_address = i;
                    symtable->assign_address(node->id, mem_address);
                    mem_loc[i] = 0;
                    break;
                }
            }
        }

        commands.push_back("PUSH mem[" + to_string(mem_address) + "]");
    } 
    else if (node->type == "ROOT") {

        if (node->left->type == "DEL") {

            int mem_address = symtable->search(node->right->id);
            mem_loc[mem_address] = -37;

            symtable->remove(node->right->id);

            commands.push_back("DEL = mem[" + to_string(mem_address) + "]");
        
        }
        else if (node->left->type == "RET") {
            
            generateCodeForNode(node->right, commands, mem_loc, symtable);
            commands.push_back("RET = POP");

        }
        else if (node->left->type == "VAR") {
            
            int mem_address = symtable->search(node->left->id);

            if (mem_address == -1) {
                for (int i = 0; i<mem_loc.size(); i++) {
                    if (mem_loc[i] == -37) {
                        mem_address = i;
                        symtable->assign_address(node->left->id, mem_address);
                        mem_loc[i] = 0;
                        break;
                    }
                }
            }
            
            generateCodeForNode(node->right, commands, mem_loc, symtable);

            commands.push_back("mem[" + to_string(mem_address) + "] = POP");
            
        }

    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    
    vector<string> targCommands;

    generateCodeForNode(targ.expr_trees.back(), targCommands, mem_loc, targ.symtable);
    
    return targCommands;
}

void EPPCompiler::write_to_file(vector<string> commands){

    ofstream file(output_file);

    if (file.is_open()) {

        for (const string& command : commands) {
            file << command << endl;
        }
        
    }

    file.close();
    
}

EPPCompiler::~EPPCompiler(){
  
}

int main() {

    vector<string> expr1 = {"v", ":=", "4", "+", "25"};
    vector<string> expr2 = {"y", ":=", "6"};
    vector<string> expr3 = {"x", ":=", "(", "3", "+", "(", "v", "-", "y", ")", ")"};
    vector<string> expr4 = {"ret", ":=", "x"};
    vector<string> expr5 = {"del", ":=", "x"};
    vector<string> expr6 = {"del", ":=", "v"};
    vector<string> expr7 = {"del", ":=", "y"};

    EPPCompiler a("TargCommands.txt", 9);
    vector<vector<string>> b;
    b.push_back(expr1);
    b.push_back(expr2);
    b.push_back(expr3);
    b.push_back(expr4);
    b.push_back(expr5);
    b.push_back(expr6);
    b.push_back(expr7);
    a.compile(b);
    Parser p;
    p.parse(expr5);
    cout << "done";
    
}