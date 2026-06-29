#include "../h_files/Account.h"
#include <iostream>

using namespace std;
// Constructors
Account::Account() {
    accountId = 0;
    name = "";
    address = "";
    accountType = "domestic";
}

Account::Account(int id, string nm, string addr, string type) {
    accountId = id;
    name = nm;
    address = addr;
    accountType = type;
}

//  Getters
int Account::getAccountId() const {
    return accountId;
}

string Account::getName() const {
    return name;
}

string Account::getAddress() const {
    return address;
}

string Account::getType() const {
    return accountType;
}

//  Setters
void Account::setName(string n) {
    name = n;
}

void Account::setAddress(string a) {
    address = a;
}

void Account::setType(string t) {
    accountType = t;
}

//Input
void Account::input() {
    cout << "Enter Account ID: ";
    cin >> accountId;
    if (accountId < 0) {
        cout << "Warning: Account ID cannot be negative. Setting to 0.\n";
        accountId = 0;
    }
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Account Type: ";
    getline(cin, accountType);
}


void Account::displayAccount() const {
    cout << "\n=== Account Details ===\n";
    cout << "ID: " << accountId
              << "\nName: " << name
              << "\nAddress: " << address
              << "\nType: " << accountType << endl;
}

void Account::display() const {
    displayAccount();
}

// Usage
void Account::addUsage(double units, string month) {
    if (units < 0) {
        cout << "Error: Usage units cannot be negative.\n";
        return;
    }
    usageHistory.append(UsageRecord(units, month));
}

void Account::addUsage() {
    double units;
    string month;

    cout << "Enter Units: ";
    cin >> units;

    if (units < 0) {
        cout << "Error: Usage units cannot be negative.\n";
        return;
    }

    cin.ignore();
    cout << "Enter Month: ";
    getline(cin, month);

    addUsage(units, month);
}

double Account::getTotalUsage() const {
    double total = 0;
    for (int i = 0; i < usageHistory.getSize(); i++) {
        total += usageHistory.getAt(i).getUnits();
    }
    return total;
}

void Account::displayUsage() const {
    if (usageHistory.getSize() == 0) {
        cout << "No usage records available.\n";
        return;
    }

    cout << "\n=== Usage History ===\n";
    for (int i = 0; i < usageHistory.getSize(); i++) {
        UsageRecord r = usageHistory.getAt(i);
        cout << r.getMonth() << " : " << r.getUnits() << " units\n";
    }
    cout << "Total Usage: " << getTotalUsage() << " units\n";
}

// ---------------- Billing ----------------
Bill Account::generateBill(double ratePerUnit) {
    if (ratePerUnit <= 0) {
        cout << "Error: Rate per unit must be positive.\n";
        return Bill();
    }

    int billId = billList.get_size() + 1;
    double amount = getTotalUsage() * ratePerUnit;

    Bill b(billId, accountId, amount, "Current", "Next Month");
    addBill(b);
    return b;
}

void Account::addBill(Bill b) {
    billList.append(b);
}

void Account::displayBills() const {
    if (billList.get_size() == 0) {
        cout << "No bills available.\n";
        return;
    }

    cout << "\n=== Bill History ===\n";
    for (int i = 0; i < billList.get_size(); i++) {
        billList[i].displayBill();
    }
}

// ---------------- JSON ----------------
json Account::exportUsageJson() const {
    json arr = json::array();
    for (int i = 0; i < usageHistory.getSize(); i++) {
        UsageRecord r = usageHistory.getAt(i);
        json record;
        record["units"] = r.getUnits();
        record["month"] = r.getMonth();
        arr.push_back(record);
    }
    return arr;
}

json Account::exportBillsJson() const {
    json arr = json::array();
    for (int i = 0; i < billList.get_size(); i++) {
        arr.push_back(billList[i].toJson());
    }
    return arr;
}

void Account::importUsageJson(json j) {
    if (!j.is_array()) {
        cout << "Error: Invalid usage JSON format.\n";
        return;
    }

    for (auto& item : j) {
        if (item.contains("units") && item.contains("month")) {
            double units = item["units"];
            string month = item["month"];
            usageHistory.append(UsageRecord(units, month));
        }
    }
}

void Account::importBillsJson(json j) {
    if (!j.is_array()) {
        cout << "Error: Invalid bills JSON format.\n";
        return;
    }

    for (auto& item : j) {
        Bill b;
        b.fromJson(item);
        billList.append(b);
    }
}


