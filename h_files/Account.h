#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "UsageRecord.h"
#include "Bill.h"
#include "Project_Templates/DoublyLinkedList.h"
#include "Project_Templates/MyArray.h"
#include "../User_Authentication/json.hpp"

using namespace std;
using json = nlohmann::json;

class Account {
private:
    int accountId;
    string name;
    string address;
    string accountType;


public:
    // Constructors
    Account();
    Account(int id, string name, string address, string type);

    // Getters (const)
    int getAccountId() const;
    string getName() const;
    string getAddress() const;
    string getType() const;

    // Setters
    void setName(string n);
    void setAddress(string a);
    void setType(string t);

    // Input / Display
    void input();
    void displayAccount() const;
    void display() const;

    // Usage
    void addUsage(double units, string month);
    void addUsage();
    double getTotalUsage() const;
    void displayUsage() const;

    // Billing
    Bill generateBill(double ratePerUnit = 10.0);
    void addBill(Bill b);
    void displayBills() const;

    // JSON
    json exportUsageJson() const;
    json exportBillsJson() const;
    void importUsageJson(json j);
    void importBillsJson(json j);

    LinkedList<UsageRecord> usageHistory;
    MyArray<Bill> billList;

};

#endif