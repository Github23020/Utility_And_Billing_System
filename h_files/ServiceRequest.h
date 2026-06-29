#ifndef SERVICEREQUEST_H
#define SERVICEREQUEST_H

#include <string>
#include <iostream>
#include "../User_Authentication/json.hpp"

using namespace std;
using json = nlohmann::json;

class ServiceRequest {
private:
    int requestId;
    int accountId;
    string serviceType;
    int priority;

public:
    ServiceRequest();


    void input();
    void displayRequest() const;


    int getPriority() const;


    bool operator<(const ServiceRequest& other) const;
    bool operator>(const ServiceRequest& other) const;
    bool operator==(const ServiceRequest& other) const;


    json toJson() const;
    void fromJson(const json& j);

    // Output operator for printing
    friend ostream& operator<<(ostream& out, const ServiceRequest& sr);
};

#endif