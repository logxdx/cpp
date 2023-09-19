#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin>>a>>b;
    if (a*b < 0 and a%b != 0) {
        cout<<a/b-1<<endl;
    } else {
        cout<<a/b<<endl;
    }
}
