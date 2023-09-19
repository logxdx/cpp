#include "stack_a.h"
#include <iostream>
#include <stdexcept>

using namespace std;


Stack_A::Stack_A(){
    size = 0;
}


void Stack_A::push(int data) {
  
    if (size<1024){
        stk[size++] = data;
    }
    else {
        throw std::runtime_error("Stack Full");
    }
}

int Stack_A::pop() {
  
    if (size == 0){
        throw std::runtime_error("Empty Stack");
    }
    return stk[--size];
}


int Stack_A::get_element_from_top(int idx) {
   
    if (idx < 0 or idx >= size) {
        throw std::runtime_error("Index out of range");
    }
    return stk[size - idx -1];
}

int Stack_A::get_element_from_bottom(int idx) {
   
    if (idx < 0 or idx >= size) {
        throw std::runtime_error("Index out of range");
    }
    return stk[idx];
}


void Stack_A::print_stack(bool top_or_bottom) {
    
    if (top_or_bottom) {
        for (int i = size-1; i>=0; i--) {
            cout << stk[i] << endl;
        }
    }
    else {
        for (int i=0; i<size; i++) {
            cout << stk[i] << endl;
        }
    }
}


int Stack_A::add() {
   
    if (size>=2) {
        
        int op1 = Stack_A::pop();
        int op2 = Stack_A::pop();
        int res = op2 + op1;
        
        Stack_A::push(res);
        return res;
    }
    else {
        throw std::runtime_error("Not Enough Arguments");
    }
}

int Stack_A::subtract() {
 
    if (size>=2) {
        
        int op1 = Stack_A::pop();
        int op2 = Stack_A::pop();
        int res = op2 - op1;
        
        Stack_A::push(res);
        return res;
    }
    else {
        throw std::runtime_error("Not Enough Arguments");
    }
}

int Stack_A::multiply() {
  
    if (size>=2) {
        
        int op1 = Stack_A::pop();
        int op2 = Stack_A::pop();
        int res = op2 * op1;
        
        Stack_A::push(res);
        return res;
    }
    else {
        throw std::runtime_error("Not Enough Arguments");
    }
}

int Stack_A::divide() {
  
    if (size>=2) {
        
        int op1 = Stack_A::pop();

        if (op1 == 0) {
            throw std::runtime_error("Divide by Zero Error");
        }
        else
        {
            int op2 = Stack_A::pop();
    
            if (op1*op2 < 0 and op2%op1 !=0) {
                int res = op2 / op1 - 1;
                Stack_A::push(res);
                return res;
            }
            else {
                int res = op2 / op1;
                Stack_A::push(res);
                return res;
            }
        }
    
    }
    else {
        throw std::runtime_error("Not Enough Arguments");
    }
}


int* Stack_A::get_stack() {
    return stk;
}

int Stack_A::get_size() {
    return size;
}
