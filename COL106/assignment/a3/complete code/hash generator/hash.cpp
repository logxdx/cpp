#define ull unsigned long long
#include <iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

const int base = 31;
const int inital_hash = 17;
const int prime = 246343;
const int mod = 246343;
// const int mod = 500009;
// const int mod = 600011;


ull power(ull x , int y)
{
    if(y == 0){return 1;}
    if(y == 1){return x;}
    else if(y%2 == 0){return power(x*x,y/2);}
    else if(y%2 == 1){ull k = x*(power(x*x,(y-1)/2)); return k;}
    return 0;
}


int calculateHash(const std::string& id) {
    unsigned long long hash = inital_hash;

    for (size_t i = 0; i < id.length(); i += 4) {
        unsigned long long block = 0;
        for (size_t j = 0; j < 4 && i + j < id.length(); ++j) {
            block = (block << 4) | (id[i + j]);
        }
        hash = (hash * base) + block;
    }

    return hash%mod;

        
    // unsigned long long hash = 0;
    
    // const int mod1 = 37;
    // const int mod2 = prime;

    // for(int i = id.length(); i>=0; i--) {
    //     hash = (hash + (id[i]-59)*power(mod1, i%18));
    // }

    // return hash%mod2;
    
}

void display(int n, vector<vector<string>> v) {

    // for(int i = 0; i<n; i++) {
    //     cout<<v[i][0]<<": "<<v[i][1]<<endl;
    // }

    int collisions = 0;
    float lf=100000/mod;

    for(int i = 0; i<n; i++) {
        
        for(int j = i+1; j<n; j++){
            if (v[i][1] == v[j][1]){
                collisions+=1;
                // cout<<v[i][1]<<" ";
            }
        }
    }
    cout<<"Load Factor : %f",(lf);
    cout<<endl<<"collisions : "<<collisions<<endl;
    cout<<endl<<"collision %age : "<<100*collisions/mod<<endl;
}

int main() {
    int n = 0;

    fstream newfile;
    vector<vector<string>> v;
    std::vector<string> det;

    newfile.open("hash1.txt",ios::in);
    ofstream fw("Hash_out.txt", ios::out);
    
    if (newfile.is_open()){
        string tp;
        while(getline(newfile, tp)){
            n++;
            det.clear();

            int hashValue = calculateHash(tp);
            string h = to_string(hashValue);

            det.push_back(tp);
            det.push_back(h);
            fw << tp << ": " << h << endl;

            v.push_back(det);
            }
            newfile.close();
            fw.close();
    }
        
    display(n, v);
    return 0;
}
