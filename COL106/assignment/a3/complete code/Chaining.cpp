#include "Chaining.h"

Chaining::Chaining() {
    bankStorage2d.resize(100000, bankStorage1d);
    size = 0;
}

void Chaining::createAccount(std::string id, int count) {
    
    int h = hash(id);
    Account temp;
    
    temp.id = id;
    temp.balance = count;
    
    bankStorage2d[h].push_back(temp);
    size+=1;
    
    return;
}

std::vector<int> Chaining::getTopK(int k) {
    return sort(bankStorage2d, k);
}

int Chaining::getBalance(std::string id) {
    
    int h = hash(id);
    std::vector<Account> v = bankStorage2d[h];
    
    for(int i = 0; i<v.size(); i++) {
        if(v[i].id == id) {
            return v[i].balance;
        }
    }

    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    
    if (not doesExist(id)) {
        createAccount(id, count);
        return;
    }

    int h = hash(id);

    for(int i = 0; i<bankStorage2d[h].size(); i++) {
        if(bankStorage2d[h][i].id == id) {
            bankStorage2d[h][i].balance += count;
            return;
        }
    }
}

bool Chaining::doesExist(std::string id) {
    
    int h = hash(id);
    std::vector<Account> v = bankStorage2d[h];
    
    for(int i = 0; i<v.size(); i++) {
        if(v[i].id == id) {
            return true;
        }
    }

    return false;
}

bool Chaining::deleteAccount(std::string id) {
    
    if (doesExist(id)) {
        
        int h = hash(id);

        for(int i = 0; i<bankStorage2d[h].size(); i++) {
            if(bankStorage2d[h][i].id == id) {
                bankStorage2d[h].erase(bankStorage2d[h].begin()+i);
                size--;
                return true;
            }
        }
    }

    return false;
}

int Chaining::databaseSize() {
    return size;
}

int Chaining::hash(std::string id) {
    
    unsigned long long hash = 0;
    
    const int mod1 = 37;
    const int mod2 = 100003;

    for(int i = id.length(); i>=0; i--) {
        hash = (hash + (id[i]-53)*power(mod1, i%23));
    }

    return hash%mod2;
}

unsigned long long Chaining::power(unsigned long long x, int y) {
        
    if (y==0) return 1;
    if (y==1) return x;
    else if (y%2==1) return power(x*x, (y+1)/2);
    else if (y%2==0) return power(x*x, y/2);
    return 0;
}

std::vector<int> Chaining::sort(std::vector<std::vector<Account>> v, int k) {

    std::vector<int> Balances;
    std::vector<int> kBalances;
    
    for(const std::vector<Account> i : v) {
        for( const Account j : i) {
            Balances.push_back(j.balance);
        }
    }

    int i, j, max_idx, n = Balances.size();
 
    for (i = 0; i<n-1; i++) {
 
        max_idx = i;
        for (j = i + 1; j < n; j++) {
            if (Balances[j] > Balances[max_idx])
                max_idx = j;
        }

        int temp = Balances[i];
        Balances[i] = Balances[max_idx];
        Balances[max_idx] = temp;
    }

    if (k==0) {
        return kBalances;
    }

    if (k<size) {
        for(int i = 0; i<k; i++) {
            kBalances.push_back(Balances[i]);
        }
    }
    else {
        for(int i = 0; i<size; i++) {
            kBalances.push_back(Balances[i]);
        }
    }

    return kBalances;
}
