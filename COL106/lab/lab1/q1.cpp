#include <iostream>
using namespace std;

class Employee {

protected:
    int password;

public:
    int id;

    Employee(int id, int password) {
        this->id = id;
        this->password = password;
    }

    void work() {
        cout << "I am Employee " << id << " I am working" << endl;
        }

    void login(int entered_password) {
        if (entered_password == password) {
            cout << "Login Successful" << endl;
        }
        else {
            cout << "Unsuccessful" << endl;
        }
    }
};

class Developer: public Employee {
public:
    Developer(int id, int password): Employee(id, password){};
};

class Manager: public Employee {
public:
    int manager_id;
    Manager(int id, int password, int manager_id): Employee(id, password){
        this->manager_id = manager_id;
    };

    void work() {
        cout << "I am Manager " << manager_id << " I am working" << endl;
    }

    void change_password(int old_password, int new_password) {
        if (old_password == password) {
            password = new_password;
            cout << "Password changed successfully" << endl;
        } else {
            cout << "Incorrect password" << endl;
        }
    }
};

int main() {
    Employee e(1, 1234);
    e.work();
    e.login(1234);

    Manager m(2, 1234, 12);
    m.work();
    m.login(123);
    m.change_password(1234, 1597);

    Developer d(3, 5768);
    d.work();
    d.login(5768);

    return 0;
}