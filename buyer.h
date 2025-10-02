#ifndef BUYER_H
#define BUYER_H

#include <cstddef>
#include <string>
#include "bank_customer.h"

using namespace std;

class Buyer {
private:
    int id;
    string name;
    string address;
    string phoneNumber;
    string email;
    BankCustomer &account; // Association with BankCustomer

public:
    Buyer(int id, const string& name, const string& address, 
        const string& phoneNumber, const string& email, BankCustomer &account0)
        : id(id), name(name), address(address), phoneNumber(phoneNumber), email(email), account(account0) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhone() const { return phoneNumber; }
    string getEmail() const { return email; }
    BankCustomer& getAccount() const { return account; }

    void setId(int newId) { id = newId; }
    void setName(const std::string& newName) { name = newName; }
    void setAddress(const string& newAddress) { address = newAddress; }
    void setPhone(const string& newPhone) { phoneNumber = newPhone; }
    void setEmail(const string& newEmail) { email = newEmail; }

    void printInfo() const {
        cout << "Buyer ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        account.printInfo();
    }
};

#endif // BUYER_H