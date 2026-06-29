#include "../h_files/ServiceRequest.h"
#include <iostream>

using namespace std;
// Constructor
ServiceRequest::ServiceRequest() {
    requestId = 0;
    accountId = 0;
    serviceType = "";
    priority = 0;
}

// Input
void ServiceRequest::input() {
    cout << "Enter Request ID: ";
    cin >> requestId;
    cout << "Enter Account ID: ";
    cin >> accountId;
    cin.ignore();

    cout << "Enter Service Type: ";
    getline(cin, serviceType);

    cout << "Enter Priority (higher number = higher priority): ";
    cin >> priority;
}

// Display
void ServiceRequest::displayRequest() const {
    cout << "\nRequest ID: " << requestId
              << "\nAccount ID: " << accountId
              << "\nService Type: " << serviceType
              << "\nPriority: " << priority << endl;
}

// PriorityQueue support
int ServiceRequest::getPriority() const {
    return priority;
}

// Comparison operators for PriorityQueue (Max-Heap)
bool ServiceRequest::operator<(const ServiceRequest& other) const {
    return priority < other.priority;
}

bool ServiceRequest::operator>(const ServiceRequest& other) const {
    return priority > other.priority;
}

bool ServiceRequest::operator==(const ServiceRequest& other) const {
    return priority == other.priority;
}

// JSON
json ServiceRequest::toJson() const {
    json j;
    j["requestId"] = requestId;
    j["accountId"] = accountId;
    j["serviceType"] = serviceType;
    j["priority"] = priority;
    return j;
}

void ServiceRequest::fromJson(const json& j) {
    if (j.contains("requestId")) requestId = j["requestId"];
    if (j.contains("accountId")) accountId = j["accountId"];
    if (j.contains("serviceType")) serviceType = j["serviceType"];
    if (j.contains("priority")) priority = j["priority"];
}

// Output operator for printing
ostream& operator<<(ostream& out, const ServiceRequest& sr) {
    out << "[RequestID: " << sr.requestId
        << ", Account: " << sr.accountId
        << ", Type: " << sr.serviceType
        << ", Priority: " << sr.priority << "]";
    return out;
}