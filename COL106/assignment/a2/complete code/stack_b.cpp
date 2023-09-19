#include "stack_b.h"
#include <iostream>
#include <stdexcept>

using namespace std;


Stack_B::Stack_B() : stk(nullptr), size(0), capacity(1024) {
        try {
            stk = new int[capacity];
        } 
        catch (std::bad_alloc& e) {
            throw std::runtime_error("Out of Memory");
        }
    }

Stack_B::~Stack_B() { 
    delete[] stk; 
    }


void Stack_B::push(int data) {
   
    if (size >= capacity) {
        int newCap = (capacity * 2);
        int* newstk = nullptr;
        
        try {
            newstk = new int[newCap];
        } 
        catch (std::bad_alloc& e) {
            throw std::runtime_error("Out of Memory");
        }

        for (int i = 0; i < size; i++) {
            newstk[i] = stk[i];
        }
        delete[] stk;
        stk = newstk;
        capacity = newCap;
    }
    stk[size++] = data;
}

int Stack_B::pop() {
  
    if (size == 0) {
        throw std::runtime_error("Empty Stack");
    }
    
    int top = stk[--size];
    if (size < capacity * 0.36 and capacity > 1024) {
        int newCap = max(static_cast<int>(capacity * 0.6), 1024);
        int* newstk = nullptr;
        
        try {
            newstk = new int[newCap];
        } 
        catch (std::bad_alloc& e) {
            throw std::runtime_error("Out of Memory");
        }

        for (int i = 0; i < size; i++) {
            newstk[i] = stk[i];
        }
        delete[] stk;
        stk = newstk;
        capacity = newCap;
        }
    return top;
}


int Stack_B::get_element_from_top(int idx) {
    
    if (idx < 0 or idx >= size) {
        throw std::runtime_error("Index out of range");
    }
    return stk[size - idx - 1];
}

int Stack_B::get_element_from_bottom(int idx) {
  
    if (idx < 0 or idx >= size) {
        throw std::runtime_error("Index out of range");
    }
    return stk[idx];
}


void Stack_B::print_stack(bool top_or_bottom) {

    if (top_or_bottom) {
        for (int i = size-1; i>=0; i--) {
            cout<<stk[i]<<endl;
        }
    }
    else
    {
        for (int i = 0; i <size; i++) {
            cout << stk[i]<<endl;
        }
    }
}


int Stack_B::add() {
  
    if (size<2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = Stack_B::pop();
    int op2 = Stack_B::pop();
    int res = op2 + op1;

    Stack_B::push(res);
    return res;
}

int Stack_B::subtract() {
   
    if (size<2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = Stack_B::pop();
    int op2 = Stack_B::pop();
    int res = op2 - op1;

    Stack_B::push(res);
    return res;
}

int Stack_B::multiply() {
  
    if (size<2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = Stack_B::pop();
    int op2 = Stack_B::pop();
    int res = op2 * op1;

    Stack_B::push(res);
    return res;
}

int Stack_B::divide() {
    
    if (size<2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = Stack_B::pop();
    
    if (op1 == 0) {
        throw std::runtime_error("Divide by Zero Error");
    }

    int op2 = Stack_B::pop();
    
    if (op1*op2 < 0 and op2%op1 !=0) {
        int res = op2 / op1 - 1;
        Stack_B::push(res);
        return res;
    }
    else {
        int res = op2 / op1;
        Stack_B::push(res);
        return res;
    }
}


int* Stack_B::get_stack() {
    return stk;
}

int Stack_B::get_size() {
    return size;
}
