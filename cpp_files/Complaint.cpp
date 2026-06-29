#include "../h_files/Complaint.h"

// Constructor
Complaint::Complaint() {
    complaintId = 0;
    accountId = 0;
    description = "";
    status = "Pending";
}

// Input
void Complaint::input() {
    cout << "Enter Complaint ID: ";
    cin >> complaintId;
    cout << "Enter Account ID: ";
    cin >> accountId;
    cin.ignore();

    cout << "Enter Complaint Description: ";
    getline(cin, description);

    status = "Pending";
}

// Display
void Complaint::displayComplaint() const {
    cout << "\nComplaint ID: " << complaintId
         << "\nAccount ID: " << accountId
         << "\nDescription: " << description
         << "\nStatus: " << status << endl;
}

// Getters
int Complaint::getComplaintId() const { return complaintId; }
int Complaint::getAccountId() const { return accountId; }
string Complaint::getStatus() const { return status; }

// JSON
json Complaint::toJson() const {
    json j;
    j["complaintId"] = complaintId;
    j["accountId"] = accountId;
    j["description"] = description;
    j["status"] = status;
    return j;
}

void Complaint::fromJson(const json& j) {
    complaintId = j["complaintId"];
    accountId = j["accountId"];
    description = j["description"];
    status = j["status"];
}
ostream& operator<<(ostream& out, Complaint& c) {
    out << "[ComplaintID: " << c.complaintId
        << ", AccountID: " << c.accountId
        << ", Status: " << c.status
        << "]";
    return out;
}
