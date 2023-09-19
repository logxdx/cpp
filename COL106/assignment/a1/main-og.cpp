#include<iostream>
#include<vector>
using namespace std;

class SET {

    private:
        vector<vector<int>> sets;

    public:
        int sign = -1;
        int Int_MIN = 2147483648 * sign;

        bool existence(int i, vector<vector<int>> &v){

            if (i+1>v.size()){
                return false;
            }
            
            else{
                return true;
            }
        }

        void create_set(int i){
            sets.resize(i+1);
            sets[i].push_back(Int_MIN);
        }

        int Union(int i, int j){

            if (not existence(i, sets)){
                create_set(i);
            }

            if (not existence(j, sets)){
                create_set(j);
            }

            vector<int> s1=sets[i];
            vector<int> s2=sets[j];
            vector<int> s3;
            s3.push_back(Int_MIN);

            int k=1, l=1;

            while(k<s1.size() and l<s2.size()){
                if (s1[k]<s2[l]){
                    s3.push_back(s1[k]);
                    k++;
                }
                else if (s1[k]>s2[l]){
                    s3.push_back(s2[l]);
                    l++;
                }
                else{
                    s3.push_back(s1[k]);
                    k++;
                    l++;
                }
            }

            while(k<s1.size()){
                s3.push_back(s1[k]);
                k++;
            }

            while(l<s2.size()){
                s3.push_back(s2[l]);
                l++;
            }

            sets[i] = s3;
            return sets[i].size()-1;
        }

        int Intersection(int i, int j){
                
            if (not existence(i, sets)){
                create_set(i);
            }

            if (not existence(j, sets)){
                create_set(j);
            }

            vector<int> s1=sets[i];
            vector<int> s2=sets[j];
            vector<int> s3;
            s3.push_back(Int_MIN);

            int k=1, l=1;

            while(k<s1.size() and l<s2.size()){
                if (s1[k]<s2[l]){
                    k++;
                }
                else if (s1[k]>s2[l]){
                    l++;
                }
                else if(s1[k]==s2[l]){
                    s3.push_back(s1[k]);
                    k++;
                    l++;
                }
            }

            sets[i] = s3;
            return sets[i].size()-1;
        }

        int Difference(int i, int j){
                    
            if (not existence(i, sets)){
                create_set(i);
            }

            if (not existence(j, sets)){
                create_set(j);
            }

            vector<int> s1=sets[i];
            vector<int> s2=sets[j];
            vector<int> s3;
            s3.push_back(Int_MIN);

            int k=1, l=1;

            while(k<s1.size() and l<s2.size()){
                if (s1[k]<s2[l]){
                    s3.push_back(s1[k]);
                    k++;
                }
                else if (s1[k]>s2[l]){
                    l++;
                }
                else{
                    k++;
                    l++;
                }
            }

            while(k<s1.size()){
                s3.push_back(s1[k]);
                k++;
            }

            sets[i] = s3;
            return sets[i].size()-1;
        }

        int Symmetric_Difference(int i, int j){
            
            if (not existence(i, sets)){
                create_set(i);
            }

            if (not existence(j, sets)){
                create_set(j);
            }

            int set_size = sets.size();

            sets.resize(set_size+3);
            sets[set_size] = sets[i];
            sets[set_size+1] = sets[j];
            sets[set_size+2] = sets[i];
            
            Union(set_size, set_size+1);
            Intersection(set_size+1,set_size+2);
            Difference(set_size,set_size+1);
            
            sets[i]=sets[set_size];
            sets.resize(set_size);
            
            return sets[i].size()-1;
        }

        int Belongs_To(int i, int x){

            if (not existence(i, sets)){
                return -1;
            }

            else{        
                int l=0, r=sets[i].size();
                vector<int> arr = sets[i];
                
                while(l<=r){
                    int m=l+(r-l)/2;
                    if(arr[m]==x){
                        return 1;
                    }
                    if(arr[m] < x){
                        l=m+1;
                    }
                    else{
                        r=m-1;
                    }
                }
                return 0;
            }
        }

        int Insert(int i, int value) {

            if (not existence(i, sets)){
                create_set(i);
            }

            vector<int>::iterator it;

            for (it = sets[i].begin(); it<sets[i].end(); it++){
                if(*it == value){
                    break;
                }
                else if((*it<value and it==sets[i].end()-1) or (*it<value and value<*(it+1)) or (value<*it and it==sets[i].begin())){
                    sets[i].insert(it+1,value);
                    break;
                }
            }
            return sets[i].size()-1;
        }

        int Delete(int i, int value){

            if (not existence(i, sets)){
                return -1;
            }

            else{
                bool existed = false;
                for(int j=1; j<sets[i].size(); j++){
                    if (sets[i][j]==value){
                        sets[i].erase(sets[i].begin()+j);
                        existed = true;
                    }
                }
            }
            return sets[i].size()-1;
        }

        int Size(int i){

            if (not existence(i, sets)){
                    create_set(i);
                    return 0;
            }
            
            else{
                return sets[i].size()-1;
            }    
        }

        void print(int i){

            if ((not existence(i, sets)) or sets[i].size()==1){
                cout<<endl;
                return;
            }

            else{
                vector<int> s=sets[i];
                for (int i=1; i<s.size()-1; i++){
                    cout<<s[i]<<",";
                }
                cout<<s[s.size()-1]<<endl;
            }
        }
};


int main() {
    SET s;
    int function_number, set_num, data;
    
    while(cin>>function_number>>set_num){

        if ((function_number == 6) or (function_number == 9)){
            switch(function_number){
                case 6:
                    cout<<s.Size(set_num)<<endl;
                    break;
                case 9:
                    s.print(set_num);
                    break;
                default:
                    break;
            }
        }

        else{
            cin>>data;
            switch(function_number){
                case 1:
                    cout<<s.Insert(set_num, data)<<endl;
                    break;
                case 2:
                    cout<<s.Delete(set_num, data)<<endl;
                    break;
                case 3:
                    cout<<s.Belongs_To(set_num, data)<<endl;
                    break;
                case 4:
                    cout<<s.Union(set_num, data)<<endl;
                    break;
                case 5:
                    cout<<s.Intersection(set_num, data)<<endl;
                    break;
                case 7:
                    cout<<s.Difference(set_num, data)<<endl;
                    break;
                case 8:
                    cout<<s.Symmetric_Difference(set_num, data)<<endl;
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}

