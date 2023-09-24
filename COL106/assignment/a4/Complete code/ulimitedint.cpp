/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include<iostream>

UnlimitedInt::UnlimitedInt() {
    sign = 0;
    size = 1;
    capacity = 1;
    unlimited_int = new int[capacity];
    unlimited_int[0] = 0;
}

UnlimitedInt::UnlimitedInt(string s) {
    
    bool flag = true;
    for (int i = 0; i<s.length(); i++) {
        if (s[i] != '0') {
            flag = false;
            break;
        } 
    }

    if (flag) {
        sign = 0;
        size = 1;
        capacity = 10;
        unlimited_int = new int[capacity];
        for (int i = 0; i<capacity; i++) unlimited_int[i] = 0;
    }

    else {

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
}

UnlimitedInt::UnlimitedInt(int i) {
    
    if (i == 0) {
        sign = 0;
        size = 1;
        capacity = 10;
        unlimited_int = new int[capacity];
        for (int i = 0; i<capacity; i++) unlimited_int[i] = 0;
    }

    else {

        int temp;
        
        if (i<0) {
            sign = -1;
            temp = -i;
        } else {
            sign = 1;
            temp = i;
        }

        size = 0;
        capacity = 10;
        unlimited_int = new int[capacity];

        while(temp>0) {
        
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
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    sign = sgn;
    size = sz;
    capacity = cap;
    unlimited_int = new int[size];

    for (int i = 0; i<size; i++) {
        unlimited_int[i] = ulimited_int[i];
    }
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

UnlimitedInt* UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2) { // manage memory leak

    UnlimitedInt* result = new UnlimitedInt();
    

    if (i1->sign == 0) {
        return i2;
    }
    if (i2->sign == 0) {
        return i1;
    }


    if (i1->sign == i2->sign) {
        
        int carry = 0;
        result->sign = i1->sign;
        result->size = max(i1->size, i2->size)+1;
        result->capacity = result->size;
        result->unlimited_int = new int[result->capacity];
        
        for (int i = 0; i<result->size; i++) {
            int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
            int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;
            int sum = digit1 + digit2 + carry;
            result->unlimited_int[i] = sum%10;
            carry = sum/10;
        }

        if (result->unlimited_int[result->size - 1] == 0) {            
            result->size--;
        }
        
    }
    
    else {

        
        if (i1->sign == -1) {
        
            UnlimitedInt* temp = new UnlimitedInt(i1->unlimited_int, i1->capacity, 1, i1->size);
            
            result = sub(i2, temp);
            
            delete temp;
        }
        
        else if (i2->sign == -1) {

            UnlimitedInt* temp = new UnlimitedInt(i2->unlimited_int, i2->capacity, 1, i2->size);
            
            result = sub(i1, temp);
            
            delete temp;
        }

    }

    return result;

}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt* i2) {
    
    UnlimitedInt* result = new UnlimitedInt();

    if (i1->sign == 0) {

        UnlimitedInt* result = new UnlimitedInt(i2->unlimited_int, i2->capacity, -1*(i2->sign), i2->size);
                
        return result;
    }
    if (i2->sign == 0) {
        return i1;
    }

    if (i1->sign != i2->sign) {
        
        UnlimitedInt* temp = new UnlimitedInt(i2->unlimited_int, i2->capacity, -1*(i2->sign), i2->size);
                
        result = add(i1, temp);
        
        delete temp;
        
    }

    else {

        if (i1->size > i2->size) {
            
            int borrow = 0;
            result->sign = i1->sign;
            result->size = i1->size;
            result->capacity = result->size;
            result->unlimited_int = new int[result->capacity];

            for (int i = 0; i<result->size; i++) {
                
                int digit1 = i1->unlimited_int[i];
                int digit2 = (i<i2->size) ? i2->unlimited_int[i] : 0;

                int diff = digit1 - digit2 - borrow;

                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                }

                else {
                    borrow = 0;
                }

                result->unlimited_int[i] = diff;
            }

        }

        else if (i1->size < i2->size) {
            
            int borrow = 0;
            result->sign = -(i2->sign);
            result->size = i2->size;
            result->capacity = result->size;
            result->unlimited_int = new int[result->capacity];

            for (int i = 0; i<result->size; i++) {
                
                int digit1 = i2->unlimited_int[i];
                int digit2 = (i<i1->size) ? i1->unlimited_int[i] : 0;

                int diff = digit1 - digit2 - borrow;

                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                }

                else {
                    borrow = 0;
                }

                result->unlimited_int[i] = diff;
            }
            
            while (result->size>1 && result->unlimited_int[result->size-1] == 0) {
                result->size--;
            }

        }

        else {

            int grt = 0;
            result->size = i1->size;
            result->capacity = result->size;
            result->unlimited_int = new int[result->capacity];
            
            int res_size = result->size;

            for (int i = 0; i<res_size; i++) {

                if (i1->unlimited_int[res_size-1-i] > i2->unlimited_int[res_size-1-i]) {
                    grt = 1;
                    break;
                }

                else if (i1->unlimited_int[res_size-1-i] < i2->unlimited_int[res_size-1-i]) {
                    grt = -1;
                    break;
                }

            }

            if (grt == 1) {
            
                int borrow = 0;
                result->sign = i1->sign;

                for (int i = 0; i<result->size; i++) {
                    
                    int digit1 = i1->unlimited_int[i];
                    int digit2 = i2->unlimited_int[i];

                    int diff = digit1 - digit2 - borrow;

                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    }

                    else {
                        borrow = 0;
                    }

                    result->unlimited_int[i] = diff;
                }

            }

            else if (grt == -1) {
            
                int borrow = 0;
                result->sign = -1*i2->sign;

                for (int i = 0; i<result->size; i++) {
                    
                    int digit1 = i2->unlimited_int[i];
                    int digit2 = i1->unlimited_int[i];

                    int diff = digit1 - digit2 - borrow;

                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    }

                    else {
                        borrow = 0;
                    }

                    result->unlimited_int[i] = diff;
                }

            }

            else if (grt == 0) {
                return result;
            }
            
            while (result->size>1 && result->unlimited_int[result->size-1] == 0) {
                result->size--;
            }

        }

    }

    return result;

}

string UnlimitedInt::to_string() {
    
    if (sign == 0) {
        return "0";
    }

    string s = "";

    for (int i = 0; i<size; i++) {
        s.push_back(unlimited_int[size-1-i] + '0');
    }

    s = (sign == -1) ? ('-' + s) : s;

    return s;
}
