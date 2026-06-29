#include "../h_files/Bill.h"

using namespace std;

Bill::Bill() {
    billId = 0;
    accountId = 0;
    amount = 0.0;
    month = "N/A";
    dueDate = "N/A";
    isPaid = false;
}

Bill::Bill(int bId, int accId, double amt,
           string m, string d) {
    if (bId < 0) {
        cout << "Warning: Bill ID cannot be negative. Setting to 0.\n";
        bId = 0;
    }

    if (accId < 0) {
        cout << "Warning: Account ID cannot be negative. Setting to 0.\n";
        accId = 0;
    }

    if (amt < 0) {
        cout << "Warning: Amount cannot be negative. Setting to 0.\n";
        amt = 0.0;
    }

    billId = bId;
    accountId = accId;
    amount = amt;
    month = m;
    dueDate = d;
    isPaid = false;
}

// Getters
int Bill::getBillId() const {
    return billId;
}

int Bill::getAccountId() const {
    return accountId;
}

double Bill::getAmount() const {
    return amount;
}

string Bill::getMonth() const {
    return month;
}

string Bill::getDueDate() const {
    return dueDate;
}

bool Bill::getPaidStatus() const {
    return isPaid;
}

// ---------------- Setters / Actions ----------------
void Bill::setAmount(double amt) {
    if (amt < 0) {
        cout << "Error: Amount cannot be negative.\n";
        return;
    }
    amount = amt;
}

void Bill::setDueDate(string d) {
    dueDate = d;
}

void Bill::markAsPaid() {
    isPaid = true;
}

// Display
void Bill::displayBill() const {
    cout << "\n===== Bill Details =====\n";
    cout << "Bill ID:     " << billId << endl;
    cout << "Account ID:  " << accountId << endl;
    cout << "Amount:      $" << fixed << setprecision(2) << amount << endl;
    cout << "Month:       " << month << endl;
    cout << "Due Date:    " << dueDate << endl;
    cout << "Status:      " << (isPaid ? "Paid" : "Unpaid") << endl;
}

json Bill::toJson() const {
    json j;
    j["billId"] = billId;
    j["accountId"] = accountId;
    j["amount"] = amount;
    j["month"] = month;
    j["dueDate"] = dueDate;
    j["isPaid"] = isPaid;
    return j;
}

void Bill::fromJson(const json& j) {
    if (j.contains("billId")) billId = j["billId"];
    if (j.contains("accountId")) accountId = j["accountId"];
    if (j.contains("amount")) amount = j["amount"];
    if (j.contains("month")) month = j["month"];
    if (j.contains("dueDate")) dueDate = j["dueDate"];
    if (j.contains("isPaid")) isPaid = j["isPaid"];
}


ostream& operator<<(ostream& os, const Bill& bill) {
    os << "[Bill#" << bill.billId
       << ", Account:" << bill.accountId
       << ", Amount:$" << fixed << setprecision(2) << bill.amount
       << ", Status:" << (bill.isPaid ? "Paid" : "Unpaid") << "]";
    return os;
}