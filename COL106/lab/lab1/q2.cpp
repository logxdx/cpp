#include <iostream>
using namespace std;


void swap_vals_using_pointers(int *p, int *q) {
    cout << "pointer p " << *p <<endl;
    cout << "pointer q " << *q << "\n" << endl;
    int temp = *p;
    *p = *q;
    *q = temp;
    cout << "swapped" << endl;
    cout << "pointer p " << *p <<endl;
    cout << "pointer q " << *q <<endl;
}

void swap_vals_using_reference(int &x, int &y) {
    cout << "x: " << x << endl; 
    cout << "y: " << y << endl; 
    int temp = x;
    x = y;
    y = temp;
    cout << "swapped \n";
    cout << "x: " << x << endl; 
    cout << "y: " << y << endl; 
}

int main(){

int x = 10;
int y =20;
int *p = &x;
int *q = &y;


// cout << p << endl;
// cout << *p << endl;
// cout << q << endl;
// cout << *q << endl;
// cout << "\n" << endl;


cout << x << endl << y << endl;
swap_vals_using_pointers(p, q);
cout << x << endl << y << endl;
swap_vals_using_reference(x, y);
cout << x << endl << y << endl;
}