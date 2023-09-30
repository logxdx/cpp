/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include<iostream>

int abs_compare(UnlimitedInt* i1, UnlimitedInt *i2) {

    if (i1->get_size() != i2->get_size()) {
        return i1->get_size() > i2->get_size();
    }

    else {
        
        int res_size = i1->get_size();

        for (int i = 0; i<res_size; i++) {
            if (i1->get_array()[res_size-1-i] > i2->get_array()[res_size-1-i]) {
                return 1;
            }
            else if (i1->get_array()[res_size-1-i] < i2->get_array()[res_size-1-i]) {
                return 0;
            }
        }
    }

    return -1;
    
}

UnlimitedInt::UnlimitedInt() {
    sign = 0;
    size = 1;
    capacity = 1;
    unlimited_int = new int[capacity];
    unlimited_int[0] = 0;
}

UnlimitedInt::UnlimitedInt(string s) {

    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1);
    } else {
        sign = 1;
    }
    
    bool zero = true;
    for (int i = 0; i<s.length(); i++) {
        if (s[i] != '0') {
            zero = false;
            break;
        } 
    }

    if (zero) {
        sign = 0;
        size = 1;
        capacity = 1;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
    }

    else {

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
        capacity = 1;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
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
        
            if (size >= capacity) {
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
    return unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}

int UnlimitedInt::get_capacity() {
    return capacity;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2) {

    UnlimitedInt* result = new UnlimitedInt();
    

    if (i1->sign == 0) {
        return i2;
    }
    if (i2->sign == 0) {
        return i1;
    }


    if (i1->sign == i2->sign) {
        int carry = 0;
        int res_size, res_sign, res_cap;
        res_sign = i1->sign;
        res_size = max(i1->size, i2->size)+1;
        res_cap = res_size;
        int *limited_int = new int[res_cap];
        
        for (int i = 0; i<res_size; i++) {
            int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
            int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;
            int sum = digit1 + digit2 + carry;
            limited_int[i] = sum%10;
            carry = sum/10;
        }

        result = new UnlimitedInt(limited_int, res_cap, res_sign, res_size);

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
    
    UnlimitedInt* result;

    if (i1->sign == 0) {
        result =  new UnlimitedInt(i2->unlimited_int, i2->capacity, -1*(i2->sign), i2->size);
        return result;
                
    }
    
    if (i2->sign == 0) {
        result =  new UnlimitedInt(i1->unlimited_int, i1->capacity, i1->sign, i1->size);
        return result;
    }

    if (i1->sign != i2->sign) {
        
        result = new UnlimitedInt(i2->unlimited_int, i2->capacity, -1*(i2->sign), i2->size);
        result = UnlimitedInt::add(i1, result);

    }

    else {

        if (i1->size > i2->size) {
            
            int res_size, res_sign, res_cap, borrow = 0;
            res_sign = i1->sign;
            res_size = i1->size;
            res_cap = res_size;
            int *limited_int = new int[res_cap];

            for (int i = 0; i<res_size; i++) {
                
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

                limited_int[i] = diff;

            }

            result = new UnlimitedInt(limited_int, res_cap, res_sign, res_size);

            while (result->size>1 && result->unlimited_int[result->size-1] == 0) {
                result->size--;
            }

        }

        else if (i1->size < i2->size) {
            
            int res_size, res_sign, res_cap, borrow = 0;
            res_sign = -1*(i2->sign);
            res_size = i2->size;
            res_cap = res_size;
            int *limited_int = new int[res_cap]; 
 
            for (int i = 0; i<res_size; i++) {
                
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

                limited_int[i] = diff;
            }

            result = new UnlimitedInt(limited_int, res_cap, res_sign, res_size);

            while (result->size>1 && result->unlimited_int[result->size-1] == 0) {
                result->size--;
            }

        }

        else {

            int grt = 0;
            int res_size, res_sign, res_cap;
            res_size = i1->size;
            res_cap = res_size;
            int *limited_int = new int[res_cap];
            

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
                res_sign = i1->sign;

                for (int i = 0; i<res_size; i++) {
                    
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

                    limited_int[i] = diff;
                }

                result = new UnlimitedInt(limited_int, res_cap, res_sign, res_size);

                while (result->size>1 && result->unlimited_int[result->size-1] == 0) {
                    result->size--;
                }


            }

            else if (grt == -1) {
            
                int borrow = 0;
                res_sign = -1*(i2->sign);

                for (int i = 0; i<res_size; i++) {
                    
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

                    limited_int[i] = diff;
                }

                result = new UnlimitedInt(limited_int, res_cap, res_sign, res_size);
            
                while (result->size>1 && result->unlimited_int[result->size-1] == 0) {
                    result->size--;
                }

            }

            else if (grt == 0) {
                result = new UnlimitedInt();
                return result;
            }

        }

    }

    return result;

}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {

    UnlimitedInt* result = new UnlimitedInt();
    int counter1 = 0, counter2 = 0;

    if (i1->sign == 0 || i2-> sign == 0) {
        return result;
    }

    int res_size, res_sign, res_cap;

    res_sign = (i1->sign)*(i2->sign);
    res_size = i1->size + i2->size;
    res_cap = res_size;
    int *limited_int = new int[res_size];

    for ( int i = 0; i < res_size; i++) {
        limited_int[i] = 0;
    }
    for (int i = 0; i<i1->size; i++) {
        
        int carry = 0;
        int digit1 = i1->unlimited_int[i];
        counter2 = 0;

        for (int j = 0; j<i2->size; j++) {

            int digit2 = i2->unlimited_int[j];

            int prod = digit1*digit2 + carry + limited_int[counter1 + counter2];
            
            carry = prod/10;
            limited_int[counter1 + counter2] = prod%10;
            // limited_int[i + j] += prod;

            counter2++;
        }

        if (carry > 0) {
            limited_int[counter1 + counter2] += carry;
        }
        counter1++;
    }
    
    result = new UnlimitedInt(limited_int, res_cap, res_sign, res_size);

    while (result->size>1 && result->unlimited_int[result->size-1] == 0) {
        result->size--;
    }

    return result;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {

    UnlimitedInt* result = new UnlimitedInt();

    if (i1->sign == 0) {
        return result;
    }

    if (i1->to_string() == i2->to_string()) {
        result = new UnlimitedInt(1);
        return result;
    }

    if (abs_compare(i1, i2) == 0) {

        if ((i1->get_sign())*(i2->get_sign()) < 0) {
            result = new UnlimitedInt(-1);
        }
        return result;
    }

    if (i2->sign != 0) {

        UnlimitedInt* Dividend = new UnlimitedInt(i1->unlimited_int, i1->capacity, 1, i1->size);
        UnlimitedInt* Divisor = new UnlimitedInt(i2->unlimited_int, i2->capacity, 1, i2->size);
        UnlimitedInt* one = new UnlimitedInt(1);

        while (sub(Dividend, Divisor)->sign >= 0 || sub(Dividend, Divisor)->sign != -1) {
            
            UnlimitedInt* temp_res;
            // cout<<"Dividend : "<<Dividend->to_string()<<endl;
            // cout<<sub(Dividend, Divisor)->to_string()<<endl;
            temp_res = new UnlimitedInt(sub(Dividend, Divisor)->to_string());
            // Dividend = new UnlimitedInt(temp_res->unlimited_int, temp_res->capacity, temp_res->sign, temp_res->size);
            Dividend = new UnlimitedInt(temp_res->to_string());
            result = add(result, one);
            // cout<<temp_res->to_string()<<endl;
            // cout<<result->to_string()<<endl;
        }

        if (sub(Dividend, Divisor)->sign == -1 && ((i1->sign * i2->sign) == -1)) {
            result = add(result, one);
        }

        // if (sub(Dividend, Divisor)->sign == 0) {
            // result = add(result, one);
        // }

        result->sign = (i1->sign)*(i2->sign);

    }

            // cout<<"Result : "<<result->to_string()<<endl;
    return result;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {

    UnlimitedInt* result = new UnlimitedInt();
    
    // result = new UnlimitedInt(div(i1, i2)->to_string());
    cout<<i1->to_string()<<endl;
    cout<<i2->to_string()<<endl;
    cout<<div(i1, i2)->to_string()<<endl;
    cout<<mul(i2, div(i1, i2))->to_string()<<endl;
    result = new UnlimitedInt(sub(i1, mul(i2, div(i1,i2)))->to_string());

    return result;
}

string UnlimitedInt::to_string() {
    
    if (sign == 0) {
        return "0";
    }

    string s = "";

    for (int i = 0; i<size; i++) {
        s += char(unlimited_int[size-1-i] + '0');
    }

    s = (sign == -1) ? ('-' + s) : s;

    return s;
}

int main() {

    int i = 0;

    // UnlimitedInt* i1 = new UnlimitedInt(354);
    UnlimitedInt* i1 = new UnlimitedInt("965314684111");
    UnlimitedInt* i2 = new UnlimitedInt("26546531");
    UnlimitedInt* i3 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), i1->get_sign(), i1->get_size());
    UnlimitedInt* i4 = new UnlimitedInt(4);
    
    // cout << i1->to_string() << endl;
    // cout << i2->to_string() << endl;
    // cout << i3->to_string() << endl;
    // cout << UnlimitedInt::add(i3,i4)->to_string() << endl;
    
        // for (int i = 0; i< i1->get_size(); i++) {
        //     cout<<i1->get_array()[i]<<endl;
        // }
    while(i < 10) {
    // while(i1 -> get_sign() != 0) {
        // cout<<(UnlimitedInt::mul(i1, i2))->to_string()<<endl;
        i1 = (UnlimitedInt::mul(i1, i2));
        cout<<"RESULT : "<<i1->to_string()<<endl;
        cout<<endl;
        // i1 = UnlimitedInt::sub(i1, i2);
        // cout<<i1->to_string()<<endl;
        // i1 = UnlimitedInt::mul(i1, i2);
        // cout<<i1->to_string()<<endl;
        // i1 = UnlimitedInt::div(i1, i2);
        // cout<<i1->to_string()<<endl;
        // i1 = UnlimitedInt::mod(i1, i2);
        // cout<<i1->to_string()<<endl;
        i++;
        // cout<<endl<<endl;
    }
    
    delete i1;
    delete i2;
    delete i3;
    return 0;

}