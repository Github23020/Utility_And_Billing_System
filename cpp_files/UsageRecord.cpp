#include "../h_files/UsageRecord.h"
#include <iostream>

using namespace std;

// Constructors
UsageRecord::UsageRecord()
        : units(0), month("Unknown") {}

UsageRecord::UsageRecord(double u, const string& m)
        : units(u), month(m) {}

// Getters
double UsageRecord::getUnits() const { return units; }
string UsageRecord::getMonth() const { return month; }

// Setters
void UsageRecord::setUnits(double u) { units = u; }
void UsageRecord::setMonth(const string& m) { month = m; }

// Display
void UsageRecord::display() const {
    cout << "Usage: " << units << " units (" << month << ")\n";
}

// JSON
json UsageRecord::toJson() const {
    json j;
    j["units"] = units;
    j["month"] = month;
    return j;
}

void UsageRecord::fromJson(const json& j) {
    units = j["units"];
    month = j["month"];
}

// Output operator (ADD THIS)
ostream& operator<<(ostream& os, const UsageRecord& record) {
    os << record.units << " units (" << record.month << ")";
    return os;
}