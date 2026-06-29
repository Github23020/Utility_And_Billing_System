#ifndef COMPLAINT_H
#define COMPLAINT_H

#include <string>
#include <iostream>
#include "../User_Authentication/json.hpp"


using namespace std;
using json = nlohmann::json;

class Complaint {
private:
    int complaintId;
    int accountId;
    string description;
    string status;   // Pending / Resolved

public:
    Complaint();

    // Input & Display (used by UtilityManager)
    void input();
    void displayComplaint() const;

    // Getters
    int getComplaintId() const;
    int getAccountId() const;
    string getStatus() const;

    // JSON (used by UtilityJsonHelper)
    json toJson() const;
    void fromJson(const json& j);
    friend ostream& operator<<(ostream& out, Complaint& c);
};

#endif
