#ifndef USAGERECORD_H
#define USAGERECORD_H

#include <string>
#include "../User_Authentication/json.hpp"

using namespace std;
using json = nlohmann::json;

class UsageRecord {
private:
    double units;     // units consumed
    string month;     // month name or number

public:
    // Constructors
    UsageRecord();
    UsageRecord(double units, const string& month);

    // Getters
    double getUnits() const;
    string getMonth() const;

    // Setters
    void setUnits(double u);
    void setMonth(const string& m);

    // Display
    void display() const;

    // JSON support
    json toJson() const;
    void fromJson(const json& j);

    // Output operator for printing (ADD THIS)
    friend ostream& operator<<(ostream& os, const UsageRecord& record);
};

#endif