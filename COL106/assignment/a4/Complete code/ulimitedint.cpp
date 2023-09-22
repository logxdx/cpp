/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt() {
    sign = 0;
    size = 1;
    capacity = 10;
    unlimited_int = new int[capacity];
    for (int i; i<capacity; i++) {
        unlimited_int[i] = 0;
    }
}

UnlimitedInt::UnlimitedInt(string s) {
    
    bool flag = true;
    for (int i = 0; i<s.length(); i++) {
        if (s[i] != '0') {
            flag = false;
            return;
        } 
    }

    if (flag) {
        sign = 0;
        size = 1;
        capacity = 10;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
        return;
    }

    
    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1);
    } else {
        sign = 1;
    }

    size = s.length();
    capacity = size;
    unlimited_int = new int[capacity];

    for (int i = 0; i < size; i++) {
        unlimited_int[i] = s[size-1-i] - '0';
    }

}

UnlimitedInt::UnlimitedInt(int i) {
    
    if (i == 0) {
        sign = 0;
        size = 1;
        capacity = 10;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
        return;
    }

    int temp;
    
    if (i<0) {
        sign = -1;
        temp = -i;
    } else {
        sign = 1;
    }

    size = 0;
    capacity = 10;
    unlimited_int = new int[capacity];

    if (size > capacity) {
            int *new_unlimited_int = new int[2*capacity];
            
            for (int j = 0; j < capacity; j++) {
                new_unlimited_int[j] = unlimited_int[j];
            }
            
            capacity *= 2;
            unlimited_int = new_unlimited_int;
            delete[] new_unlimited_int;
        }

        unlimited_int[size] = temp%10;
        temp = temp/10;
        size++;
}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    string s = "";
    for (int i = 0; i<size; i++) {
        s = char(unlimited_int[i]) + s;
    }
    return UnlimitedInt(s).unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2) {
    int carry = 0;

    if (i1->get_sign() == 0) {
        return i2;
    }
    if (i2->get_sign() == 0) {
        return i1;
    }

    UnlimitedInt* result;

    if (i1->get_sign() == i2->get_sign()) {
        
        result->sign = i1->get_sign();
        result->size = max(i1->get_size(), i2->get_size());
        result->capacity = result->size;
        result->unlimited_int = new int[result->capacity];
        
        for (int i = 0; i<result->size; i++) {
            int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
            int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;
            int sum = digit1 + digit2 + carry;
            result->unlimited_int[i] = sum%10;
            carry = sum/10;
        }

        if (carry > 0) {

            result->capacity++;
            int* new_int = new int[result->capacity];
            new_int[result->size] = carry;
            result->size++;

            for (int i = 0; i < result->capacity-1; i++) {
                new_int[i] = result->unlimited_int[i];
            }
            
            result->unlimited_int = new_int;
            delete[] new_int;

        } 
        
        else {
            result = sub(i1, i2);
        }
    }

    return result;

}

string UnlimitedInt::to_string() {
    if (sign == 0) {
        return "0";
    }

    string s = (sign == -1) ? "-" : "";

    for (int i = 0; i<size; i++) {
        s += char(unlimited_int[i]) + '0';
    }

    return s;
}
