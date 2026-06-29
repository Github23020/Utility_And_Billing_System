#ifndef UTILITY_JSON_HELPER_H
#define UTILITY_JSON_HELPER_H

#include <fstream>
#include <string>
#include "../User_Authentication/json.hpp"


#include "Account.h"
#include "Complaint.h"
#include "ServiceRequest.h"
#include "Graph.h"

#include "Project_Templates/MyArray.h"
#include "Project_Templates/LinkedQueue.h"
#include "Project_Templates/PriorityQueue.h"

using json = nlohmann::json;
using namespace std;

class UtilityJsonHelper {
public:
    static string accountsFile;
    static string complaintsFile;
    static string requestsFile;
    static string graphFile;

    static bool saveAccounts(MyArray<Account>& accounts);
    static bool loadAccounts(MyArray<Account>& accounts);

    static bool saveComplaints(LinkedQUEUE<Complaint>& q);
    static bool loadComplaints(LinkedQUEUE<Complaint>& q);

    static bool saveServiceRequests(PriorityQueue<ServiceRequest>& pq);
    static bool loadServiceRequests(PriorityQueue<ServiceRequest>& pq);

    static bool saveGraph(Graph& g);
    static bool loadGraph(Graph& g);
};

#endif
