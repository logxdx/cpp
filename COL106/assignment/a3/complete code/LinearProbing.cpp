#include "LinearProbing.h"

LinearProbing::LinearProbing() {
    size = 0;
}

void LinearProbing::createAccount(std::string id, int count) {
    
    if (bankStorage1d.size() == 0) {
        Account t;
        t.id = "";
        t.balance = -1;
        bankStorage1d.resize(100001, t);
    }

    int h = hash(id);
    Account temp;
    temp.id = id;
    temp.balance = count;

    if (bankStorage1d[h].balance == -1) {
        bankStorage1d[h] = temp;
        size++;
        return;
    }
    else {

        h++;
        while(bankStorage1d[h].balance != -1) {
            h++;
            h%=100000;
        }

        bankStorage1d[h] = temp;
        size++;
        return;
    }
    return;
}

std::vector<int> LinearProbing::getTopK(int k) {
    return sort(bankStorage1d, k);
}

int LinearProbing::getBalance(std::string id) {

    int h = hash(id);
    int count = 0;

    while(bankStorage1d[h].id != id) {
        h++;
        h%=100000;
        count++;

        if (count>100000) {
            return -1;
        }
    }

    return bankStorage1d[h].balance;
}

void LinearProbing::addTransaction(std::string id, int count) {
    
    if (not doesExist(id)) {
        createAccount(id, count);
        return;
    }

    int h = hash(id);
    
    while(bankStorage1d[h].id != id) {
        h++;
        h%=100000;
    }

    bankStorage1d[h].balance += count;
    return;
}

bool LinearProbing::doesExist(std::string id) {

    int h = hash(id);
    int count = 0;

    while(bankStorage1d[h].id != id) {
        h++;
        h%=100000;
        count++;

        if (count>100000) {
            return false;
        }
    }

    return true;
}

bool LinearProbing::deleteAccount(std::string id) {
    
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

int LinearProbing::databaseSize() {
    return size;
}

int LinearProbing::hash(std::string id) {
    
    unsigned long long hash = 0;
    
    const int mod1 = 37;
    const int mod2 = 100003;

    for(int i = id.length(); i>=0; i--) {
        hash = (hash + (id[i]-53)*power(mod1, i%23));
    }

    return hash%mod2;
}

unsigned long long LinearProbing::power(unsigned long long x, int y) {
        
    if (y==0) return 1;
    if (y==1) return x;
    else if (y%2==1) return power(x*x, (y+1)/2);
    else if (y%2==0) return power(x*x, y/2);
    return 0;
}

std::vector<int> LinearProbing::sort(std::vector<Account> v, int k) {

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
