#include<string>
#include<iostream>

std::string k = "abcde";

int main() {
    for( int i = 0; i<k.length(); i++) {
        unsigned int block = 0;
        block =  0 | (k[i]);
        std::cout<<block<<std::endl;
    }
}