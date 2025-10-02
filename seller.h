#pragma once
#include "buyer.h"
#include "item.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class seller : public Buyer {

private:
    // Add seller-specific private members here
    int sellerId;
    string sellerName;
    string sellerAddress;
    string sellerPhone;
    string sellerEmail;
    
    bool idDisplayed(int itemId) const {
        // Example implementation, can be customized
        return itemId > 0; // Assuming valid IDs are positive integers
    }

    vector<Item> items; // Assuming seller has a collection of items


public:
    seller() = default;

    seller(Buyer buyer, int sellerId, const string& sellerName, const string& sellerAddress, 
            const string& sellerPhone, const string& sellerEmail)
        : Buyer(buyer.getId(), buyer.getName(), buyer.getAddress(), buyer.getPhone(), buyer.getEmail(), buyer.getAccount()), 
            sellerId(sellerId), sellerName(sellerName), sellerAddress(sellerAddress), 
            sellerPhone(sellerPhone), sellerEmail(sellerEmail) {
            Buyer::setId(buyer.getId());
        }

    virtual ~seller() = default;

    int getSellerId() const { return sellerId; }
    string getSellerName() const { return sellerName; }
    string getSellerAddress() const { return sellerAddress; }
    string getSellerPhone() const { return sellerPhone; }
    string getSellerEmail() const { return sellerEmail; }

    void setSellerName(const string& name) { sellerName = name; }
    void setSellerAddress(const string& address) { sellerAddress = address; }
    void setSellerPhone(const string& phone) { sellerPhone = phone; }
    void setSellerEmail(const string& email) { sellerEmail = email; }

    void addNewItem(int newId, const std::string& newName, int newQuantity, double newPrice) {
        Item newItem(newId, newName, newQuantity, newPrice);
        items.push_back(newItem);
    }

    void updateItem(int itemId, const std::string& newName, int newQuantity, double newPrice) {
        for (auto& item : items) {
            if (item.getId() == itemId) {
                item.alterItemById(itemId, newName, newQuantity, newPrice); // Assuming alterItemById is a method
            }
        }
    }

    void makeItemVisibleToCustomer(int itemId) {
        for (auto& item : items) {
            if (item.getId() == itemId) {
                item.setDisplay(true); // Assuming setDisplay is a method in Item class
                break;
            }
        }
    }

    // Add seller-specific members here
    void printInfo() const {
        cout << "Seller ID: " << sellerId << endl;
        cout << "Seller Name: " << sellerName << endl;
        cout << "Seller Address: " << sellerAddress << endl;
        cout << "Seller Phone: " << sellerPhone << endl;
        cout << "Seller Email: " << sellerEmail << endl;
        Buyer::printInfo(); 
    }
};