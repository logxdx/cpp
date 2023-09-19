#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    Comp();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    const int mod = 500009;
    int size;
    unsigned long long power(unsigned long long, int);
    std::vector<int> sort(std::vector<Account>, int);
};

#endif // COMP_H
