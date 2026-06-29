#ifndef BILL_H
#define BILL_H

#include <string>
#include <iostream>
#include "../User_Authentication/json.hpp"

using namespace std;
using json = nlohmann::json;

class Bill {
private:
    int billId;
    int accountId;
    double amount;
    string month;
    string dueDate;
    bool isPaid;

public:
    // Constructors
    Bill();
    Bill(int billId, int accountId, double amount,
         string month, string dueDate);

    // Getters (const)
    int getBillId() const;
    int getAccountId() const;
    double getAmount() const;
    string getMonth() const;
    string getDueDate() const;
    bool getPaidStatus() const;

    // Setters / Actions
    void setAmount(double amount);
    void setDueDate(string dueDate);
    void markAsPaid();

    // Display
    void displayBill() const;

    // JSON
    json toJson() const;
    void fromJson(const json& j);

    // Output
    friend ostream& operator<<(ostream& os, const Bill& bill);
    bool operator>(const Bill& other) const {
        return amount > other.amount;
    }

    bool operator<(const Bill& other) const {
        return amount < other.amount;
    }

    bool operator==(const Bill& other) const {
        return billId == other.billId;
    }
};

#endif