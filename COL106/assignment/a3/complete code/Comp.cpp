#include "Comp.h"

Comp::Comp() {
    size = 0;
}

void Comp::createAccount(std::string id, int count) {
    
    if (bankStorage1d.size() == 0) {
        Account t;
        t.id = "";
        t.balance = -1;
        bankStorage1d.resize(mod, t);
    }

    int h = hash(id);
    Account *temp = new Account();
    temp->id = id;
    temp->balance = count;

    if (bankStorage1d[h].balance==-1) {
        bankStorage1d[h] = *temp;
        delete temp;
        size++;
        return;
    }
    else {

        h++;
        while(bankStorage1d[h].balance != -1) {
            h++;
            h%=mod;
        }

        bankStorage1d[h] = *temp;
        size++;
        delete temp;
        return;
    }
    return;
}

std::vector<int> Comp::getTopK(int k) {
    return sort(bankStorage1d, k);
}

int Comp::getBalance(std::string id) {

    int h = hash(id);
    int count = 0;

    while(bankStorage1d[h].id != id) {
        h++;
        h%=mod;
        count++;

        if (count>mod) {
            return -1;
        }
    }

    return bankStorage1d[h].balance;
}

void Comp::addTransaction(std::string id, int count) {
    
    if (not doesExist(id)) {
        createAccount(id, count);
        return;
    }

    int h = hash(id);
    
    while(bankStorage1d[h].id != id) {
        h++;
        h%=mod;
    }

    bankStorage1d[h].balance += count;
    return;
}

bool Comp::doesExist(std::string id) {

    int h = hash(id);
    int count = 0;

    while(bankStorage1d[h].id != id) {
        h++;
        h%=mod;
        count++;

        if (count>mod) {
            return false;
        }
    }

    return true;
}

bool Comp::deleteAccount(std::string id) {
    
    if (doesExist(id)) {

        int h = hash(id);

        while(bankStorage1d[h].id != id) {
            h++;
            h%=100000;
        }

        bankStorage1d[h].id = "";
        bankStorage1d[h].balance = -1;
        size--;
        return true;
    }

    return false;
}

int Comp::databaseSize() {
    return size;
}

int Comp::hash(std::string id) {

    const int base = 31;
    unsigned long long hash = 17;
    // const int inital_hash = 17;
    // unsigned long long hash = inital_hash;


    for (size_t i = 0; i < id.length(); i += 4) {
        unsigned long long block = 0;
        for (size_t j = 0; j < 4 && i + j < id.length(); ++j) {
            block = (block << 4) | (id[i + j]);
        }
        hash = (hash * base) + block;
    }

    return hash%mod;
}

unsigned long long Comp::power(unsigned long long x, int y) {
        
    if (y==0) return 1;
    if (y==1) return x;
    else if (y%2==1) return power(x*x, (y+1)/2);
    else if (y%2==0) return power(x*x, y/2);
    return 0;
}

std::vector<int> Comp::sort(std::vector<Account> v, int k) {

    std::vector<int> Balances;
    std::vector<int> kBalances;
    
    for( const Account j : v) {
        if (j.balance>=0)
            Balances.push_back(j.balance);
    }

    int i, j, max_idx, n = Balances.size();
 
    for (i = 0; i < n-1; i++) {
 
        max_idx = i;
        for (j = i + 1; j < n; j++) {
            if (Balances[j] > Balances[max_idx])
                max_idx = j;
        }

        if (max_idx != i) {
            int temp = Balances[i];
            Balances[i] = Balances[max_idx];
            Balances[max_idx] = temp;
        }
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
