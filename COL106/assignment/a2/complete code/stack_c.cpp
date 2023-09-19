#include "stack_c.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Stack_C::Stack_C(): stk(nullptr) {
    try {
        stk = new List();
    } 
    catch (std::bad_alloc& e) {
        throw std::runtime_error("Out of Memory");
    }
}

Stack_C::~Stack_C() {
    delete stk;
}


void Stack_C::push(int data) {
    stk->insert(data);
}

int Stack_C::pop() {
    if (stk->get_size() == 0) {
        throw std::runtime_error("Empty Stack");
    }
    else
    {
        return stk->delete_tail();
    }
}


int Stack_C::get_element_from_top(int idx) {

    int size = stk->get_size();

    if (idx < 0 || idx >= size) {
        throw std::runtime_error("Index out of range");
    }
    else {
        Node* temp = stk->get_head();
        for (int i = 0; i<=size-idx-1; i++) {
            temp = temp -> next;
        }
        int data = temp->get_value();
        temp = nullptr;
        delete temp;
        return data;
    }
}

int Stack_C::get_element_from_bottom(int idx) {

    int size = stk->get_size();

    if (idx < 0 || idx >= size) {
        throw std::runtime_error("Index out of range");
    }
    else {
        Node* temp = stk->get_head();
        for (int i = 0; i<=idx; i++) {
            temp = temp -> next;
        }
        int data = temp->get_value();
        temp = nullptr;
        delete temp;
        return data;
    }
}


void Stack_C::print_stack(bool top_or_bottom) {
    if (top_or_bottom) {
        Node* temp = stk->get_head()->next;
        while (temp->is_sentinel_node() == false) {
            cout << temp->get_value()<<" ";
            temp = temp->next;
        }
        cout<<endl;
        delete temp;
    }
    else {
        Node* temp = stk->get_head()->next;
        while (temp->is_sentinel_node() == false) {
            temp = temp->next;
        }
        temp = temp->prev;
        while(temp->is_sentinel_node() == false) {
            cout<<temp->get_value()<<" ";
            temp = temp->prev;
        }
        cout<<endl;
        delete temp;
    }
}


int Stack_C::add() {

    if (stk->get_size() < 2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = stk->delete_tail();
    int op2 = stk->delete_tail();
    int res = op2 + op1;

    stk->insert(res);
    return res;
}

int Stack_C::subtract() {

    if (stk->get_size() < 2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = stk->delete_tail();
    int op2 = stk->delete_tail();
    int res = op2 - op1;

    stk->insert(res);
    return res;
}

int Stack_C::multiply() {

    if (stk->get_size() < 2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = stk->delete_tail();
    int op2 = stk->delete_tail();
    int res = op2 * op1;

    stk->insert(res);
    return res;
}

int Stack_C::divide() {

    if (stk->get_size() < 2) {
        throw std::runtime_error("Not Enough Arguments");
    }

    int op1 = stk->delete_tail();

    if (op1 == 0) {
        throw std::runtime_error("Divide by Zero Error");
    }

    int op2 = stk->delete_tail();
    
    if (op1*op2 < 0 and op2%op1 !=0) {
        int res = op2 / op1 - 1;
        stk->insert(res);
        return res;
    }
    else {
        int res = op2 / op1;
        stk->insert(res);
        return res;
    }
}

List* Stack_C::get_stack() {
    return stk;
}

int Stack_C::get_size() {
    return stk->get_size();
}
