#include <iostream>
#include "bank_customer.h"
#include "buyer.h"
#include <vector>
#include "seller.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT, ADMIN_LOGIN};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
using namespace std;

vector<Buyer> buyers;
vector<seller> sellers;

int main() {
    //create a loop prompt 
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;
    bool adminRunning = false;
    bool viewDetails = false;
    bool searchRunning = false;
    bool createRunning = false;
    bool removeRunning = true;

    BankCustomer acc1(1, "Alice", 5000.0);
    BankCustomer acc2(2, "Bob", 3000.0);

    // Dummy Buyers
    buyers.push_back(Buyer(1, "Alice", "Jl. Mawar", "0812345678", "alice@mail.com", acc1));
    buyers.push_back(Buyer(2, "Bob", "Jl. Melati", "0898765432", "bob@mail.com", acc2));

    // Dummy Sellers
    sellers.push_back(seller(buyers[1], 101, "Bob Store", "Jl. Melati No.2", "0811223344", "storebob@mail.com"));
    
    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected." << endl;
                /* if Login is selected, based on authority then provide options:
                assume user is logged in as Buyer for now
                1. Chek Account Status (will display if user is Buyer or Seller or both and linked banking account status)
                Will display Buyer, Seller and Banking Account details
                2. Upgrade Account to Seller
                Will prompt user to enter Seller details and create a Seller account linked to Buyer account
                Will reject if a user dont have a banking account linked
                3. Create Banking Account (if not already linked), will be replaced with banking functions
                Must provides: initial deposit amount, Address, Phone number, Email
                Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw
                4. Browse Store Functionality
                Will display all stores initially
                Need to select a store to browse each store inventory
                Will display all items in the store inventory
                After selecting an item, will display item details and option to add to cart
                After adding to cart, will notify user item is added to cart
                5. Order Functionality
                Will display all items in cart
                Will provide option to remove item from cart
                Will provide option to checkout
                After checkout invoide will be generated (will go to payment functionality)
                6. Payment Functionality
                Will display all listed invoices
                Pick an invoice to pay
                Will display invoice details and total amount
                Will provide option to pay invoice
                Payment is done through confirmation dialogue
                In confirmation dialogue, will display account balance as precursor
                User will need to manually enter invoice id to pay
                After paying balance will be redacted from buyer and added to the responding seller account
                After payment, order status will be changed to paid
                7. Logout (return to main menu)
                Display confirmation dialogue
                If confirmed, return to main menu
                If not, return to Buyer menu
                8. Delete Account (remove both Buyer and Seller account and relevant banking account)
                Display confirmation dialogue
                If confirmed, delete account and return to main menu
                If not, return to Buyer menu

                assume user is logged in as Seller for now
                9. Check Inventory
                10. Add Item to Inventory
                11. Remove Item from Inventory
                12. View Orders (will display all orders placed to this seller
                Only orders with paid status will be listed
                Order details will listing items, quantity, total amount, buyer details, order status (paid, cancelled, completed)
                extra functions
                9. Exit to main Menu
                10. Exit Program
                **/
                break;
            case REGISTER:
                regPrompt = CREATE_BUYER; // reset regPrompt to CREATE_BUYER when entering register menu
                while (regPrompt != BACK){
                    cout << "Register selected. " << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;
                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                    switch (regPrompt) {
                        case CREATE_BUYER:
                            cout << "Create Buyer Account selected." << endl;
                            break;
                        case CREATE_SELLER:
                            cout << "Create Seller Account selected." << endl;
                            break;
                        case BACK:
                            cout << "Back selected." << endl;
                            break;
                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                }
                /* if register is selected then went throuhh registration process:
                1. Create a new Buyer Account
                Must provides: Name, Home Address, Phone number, Email
                2. Option to create a Seller Account (will be linked to Buyer account)
                Must Provides 1: Home Address, Phone number, Email
                Must provides 2: Store Name, Store Address, Store Phone number, Store Email
                Must provides 3: initial deposit amount
                After finished immediately logged in as Buyer/Seller
                */
                break;
            case EXIT:
                cout << "Exiting." << endl;
                break;

            /** After login create a sub prompt that provides the following features
            1. Account Management
                - View All Buyers, Sellers
                - View All details of Buyers, Sellers
                - Seek certain buyer of seller based on Name / account Id / address / phone number
                - Create new buyer/seller/Bank account
                - Remove buyer/seller based on ID (all related info will be deleted)
            2. System Report
                - Total number of Buyers, Sellers
                - Total number of Banking Accounts
            */
            case ADMIN_LOGIN:
                /* Prompt for username & password then check the entries with our hard coded features */
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                    cout << "Admin login successful." << endl;
                    adminRunning = true;
                    while (adminRunning) {
                        cout << "\n--- Admin Menu ---\n";
                        cout << "1. View All Buyers\n";
                        cout << "2. View All Sellers\n";
                        cout << "3. View All Details (Buyers or Sellers)\n";
                        cout << "4. Search Buyer/Seller by Name/ID/Address/Phone\n";
                        cout << "5. Create new Buyer/Seller/Bank account\n";
                        cout << "6. Remove Buyer/Seller by ID\n";
                        cout << "7. Logout\n";
                        int adminChoice;
                        cin >> adminChoice;

                        switch (adminChoice) {
                            case 1:
                                cout << "List of Buyers\n";
                                if (buyers.empty()) {
                                    cout << "No buyers available.\n";
                                } else {
                                    for (const auto &b : buyers) {
                                        cout << "Name: " << b.getName()
                                            << " | Balance: $" << b.getAccount().getBalance()
                                            << endl;
                                    }
                                }
                                break;
                            case 2:
                                cout << "List of Sellers\n";
                                if (sellers.empty()) {
                                    cout << "No sellers available.\n";
                                } else {
                                    for (const auto& seller : sellers) {
                                        cout << "Store Name: " << seller.getSellerName()
                                             << " | Balance: $" << seller.getAccount().getBalance()
                                             << endl;
                                    }
                                }
                                break;
                            case 3:
                                viewDetails = true;
                                while (viewDetails) {
                                    cout << "\n--- View Details Menu ---\n";
                                    cout << "1. View All Buyer Details\n";
                                    cout << "2. View All Seller Details\n";
                                    cout << "3. Back\n";
                                    int detailChoice;
                                    cin >> detailChoice;

                                    switch (detailChoice) {
                                        case 1: {
                                            cout << "\n--- Buyer Details ---\n";
                                            if (buyers.empty()) {
                                                cout << "No buyers available.\n";
                                            } else {
                                                for (const auto &b : buyers) {
                                                    b.printInfo();
                                                    cout << "----------------------\n";
                                                }
                                            }
                                            break;
                                        }
                                        case 2: {
                                            cout << "\n--- Seller Details ---\n";
                                            if (sellers.empty()) {
                                                cout << "No sellers available.\n";
                                            } else {
                                                for (const auto &s : sellers) {
                                                    s.printInfo();
                                                    cout << "----------------------\n";
                                                }
                                            }
                                            break;
                                        }
                                        case 3:
                                            cout << "Back to Admin Menu.\n";
                                            viewDetails = false;
                                            break;
                                        default:
                                            cout << "Invalid option.\n";
                                            break;
                                    }
                                }
                                break;
                            case 4:
                                searchRunning = true;
                                while (searchRunning) {
                                    cout << "\n--- Search Menu ---\n";
                                    cout << "1. Search Buyer\n";
                                    cout << "2. Search Seller\n";
                                    cout << "3. Back\n";
                                    int searchChoice;
                                    cin >> searchChoice;

                                    switch (searchChoice) {
                                        case 1: { // Search Buyer
                                            cout << "Search Buyer by:\n";
                                            cout << "1. ID\n2. Name\n3. Phone\n4. Address\n";
                                            int opt; cin >> opt;
                                            bool found = false;

                                            if (opt == 1) {
                                                cout << "Enter Buyer ID: ";
                                                int id; cin >> id;
                                                for (const auto& b : buyers) {
                                                    if (b.getId() == id) { b.printInfo(); found = true; break; }
                                                }
                                            } else if (opt == 2) {
                                                cout << "Enter Buyer Name: ";
                                                string name; cin >> name;
                                                for (const auto& b : buyers) {
                                                    if (b.getName() == name) { b.printInfo(); found = true; break; }
                                                }
                                            } else if (opt == 3) {
                                                cout << "Enter Buyer Phone: ";
                                                string phone; cin >> phone;
                                                for (const auto& b : buyers) {
                                                    if (b.getPhone() == phone) { b.printInfo(); found = true; break; }
                                                }
                                            } else if (opt == 4) {
                                                cout << "Enter Buyer Address: ";
                                                string addr; cin >> addr;
                                                for (const auto& b : buyers) {
                                                    if (b.getAddress() == addr) { b.printInfo(); found = true; break; }
                                                }
                                            }

                                            if (!found) cout << "Buyer not found.\n";
                                            break;
                                        }
                                        case 2: { // Search Seller
                                            cout << "Search Seller by:\n";
                                            cout << "1. ID\n2. Store Name\n3. Phone\n4. Address\n";
                                            int opt; cin >> opt;
                                            bool found = false;

                                            if (opt == 1) {
                                                cout << "Enter Seller ID: ";
                                                int id; cin >> id;
                                                for (const auto& s : sellers) {
                                                    if (s.getSellerId() == id) { s.printInfo(); found = true; break; }
                                                }
                                            } else if (opt == 2) {
                                                cout << "Enter Store Name: ";
                                                string store; cin >> store;
                                                for (const auto& s : sellers) {
                                                    if (s.getSellerName() == store) { s.printInfo(); found = true; break; }
                                                }
                                            } else if (opt == 3) {
                                                cout << "Enter Store Phone: ";
                                                string phone; cin >> phone;
                                                for (const auto& s : sellers) {
                                                    if (s.getSellerPhone() == phone) { s.printInfo(); found = true; break; }
                                                }
                                            } else if (opt == 4) {
                                                cout << "Enter Store Address: ";
                                                string addr; cin >> addr;
                                                for (const auto& s : sellers) {
                                                    if (s.getSellerAddress() == addr) { s.printInfo(); found = true; break; }
                                                }
                                            }

                                            if (!found) cout << "Seller not found.\n";
                                            break;
                                        }
                                        case 3:
                                            cout << "Back to Admin Menu.\n";
                                            searchRunning = false;
                                            break;
                                        default:
                                            cout << "Invalid option.\n";
                                            break;
                                    }
                                }
                                break;
                            case 5:
                                createRunning = true;
                                while (createRunning) {
                                    cout << "\n--- Create Menu ---\n";
                                    cout << "1. Create Buyer Account\n";
                                    cout << "2. Create Seller Account\n";
                                    cout << "3. Create Bank Account only\n";
                                    cout << "4. Back\n";
                                    int createChoice;
                                    cin >> createChoice;

                                    switch (createChoice) {
                                        case 1: { // Create Buyer
                                            int id; string name, addr, phone, email; double balance;
                                            cout << "Enter Buyer ID: "; cin >> id;
                                            cout << "Enter Name: "; cin >> name;
                                            cout << "Enter Address: "; cin >> addr;
                                            cout << "Enter Phone: "; cin >> phone;
                                            cout << "Enter Email: "; cin >> email;
                                            cout << "Enter Initial Balance: "; cin >> balance;

                                            // buat BankCustomer
                                            BankCustomer *newAcc = new BankCustomer(id, name, balance);
                                            // simpan Buyer
                                            buyers.push_back(Buyer(id, name, addr, phone, email, *newAcc));
                                            cout << "Buyer created successfully!\n";
                                            break;
                                        }
                                        case 2: { // Create Seller (butuh Buyer dulu)
                                            if (buyers.empty()) {
                                                cout << "No buyers available! Create a buyer first.\n";
                                                break;
                                            }
                                            int sid, bid;
                                            string storeName, storeAddr, storePhone, storeEmail;

                                            cout << "Enter Seller ID: "; cin >> sid;
                                            cout << "Link to Buyer ID: "; cin >> bid;

                                            // cari buyer
                                            Buyer *linkedBuyer = nullptr;
                                            for (auto &b : buyers) {
                                                if (b.getId() == bid) {
                                                    linkedBuyer = &b;
                                                    break;
                                                }
                                            }
                                            if (!linkedBuyer) {
                                                cout << "Buyer not found!\n";
                                                break;
                                            }

                                            cout << "Enter Store Name: "; cin >> storeName;
                                            cout << "Enter Store Address: "; cin >> storeAddr;
                                            cout << "Enter Store Phone: "; cin >> storePhone;
                                            cout << "Enter Store Email: "; cin >> storeEmail;

                                            sellers.push_back(seller(*linkedBuyer, sid, storeName, storeAddr, storePhone, storeEmail));
                                            cout << "Seller created successfully!\n";
                                            break;
                                        }
                                        case 3: { // Create Bank Account only
                                            int id; string name; double balance;
                                            cout << "Enter Account ID: "; cin >> id;
                                            cout << "Enter Name: "; cin >> name;
                                            cout << "Enter Initial Balance: "; cin >> balance;

                                            BankCustomer *newAcc = new BankCustomer(id, name, balance);
                                            cout << "Bank account created successfully!\n";
                                            // catatan: kalau mau, bisa simpan di vector<BankCustomer>
                                            break;
                                        }
                                        case 4:
                                            cout << "Back to Admin Menu.\n";
                                            createRunning = false;
                                            break;
                                        default:
                                            cout << "Invalid option.\n";
                                            break;
                                    }
                                }
                                break;
                            case 6:
                                cout << "Remove account by ID\n";
                                break;
                            case 7:
                                cout << "Logging out from Admin.\n";
                                adminRunning = false;
                                break;
                            default:
                                cout << "Invalid option.\n";
                                break;
                        }
                    }
                } else {
                    cout << "Invalid admin credentials. Access denied.\n";
                }

                
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
        cout << endl;
    }

    //BankCustomer customer1(1, "Alice", 1000.0);
    //Buyer buyer1(1, customer1.getName(), customer1);
    return 1;
}