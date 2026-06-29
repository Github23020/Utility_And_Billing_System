#include "../h_files/UtilityJsonHelper.h"

// File names
string UtilityJsonHelper::accountsFile   = "accounts.json";
string UtilityJsonHelper::complaintsFile = "complaints.json";
string UtilityJsonHelper::requestsFile   = "requests.json";
string UtilityJsonHelper::graphFile      = "graph.json";

// ---------------- Accounts ----------------
bool UtilityJsonHelper::saveAccounts(MyArray<Account>& accounts) {
    json arr = json::array();

    for (int i = 0; i < accounts.get_size(); i++) {
        Account& a = accounts[i];
        json obj;

        obj["accountId"] = a.getAccountId();
        obj["name"]      = a.getName();
        obj["address"]   = a.getAddress();
        obj["type"]      = a.getType();

        obj["usage"] = a.exportUsageJson();
        obj["bills"] = a.exportBillsJson();

        arr.push_back(obj);
    }

    ofstream file(accountsFile);
    file << arr.dump(4);
    return true;
}

bool UtilityJsonHelper::loadAccounts(MyArray<Account>& accounts) {
    ifstream file(accountsFile);
    if (!file.good()) return false;

    json arr;
    file >> arr;
    accounts.clear();

    for (auto& obj : arr) {
        Account a(
                obj["accountId"],
                obj["name"],
                obj["address"],
                obj["type"]
        );
        a.importUsageJson(obj["usage"]);
        a.importBillsJson(obj["bills"]);
        accounts.append(a);
    }
    return true;
}

// ---------------- Complaints ----------------
bool UtilityJsonHelper::saveComplaints(LinkedQUEUE<Complaint>& q) {
    json arr = json::array();
    LinkedQUEUE<Complaint> temp = q;

    while (!temp.isEmpty()) {
        Complaint c = temp.dequeue();
        arr.push_back(c.toJson());
    }

    ofstream file(complaintsFile);
    file << arr.dump(4);
    return true;
}

bool UtilityJsonHelper::loadComplaints(LinkedQUEUE<Complaint>& q) {
    ifstream file(complaintsFile);
    if (!file.good()) return false;

    json arr;
    file >> arr;

    for (auto& obj : arr) {
        Complaint c;
        c.fromJson(obj);
        q.enqueue(c);
    }
    return true;
}

// ---------------- Service Requests ----------------
bool UtilityJsonHelper::saveServiceRequests(PriorityQueue<ServiceRequest>& pq) {
    json arr = json::array();
    PriorityQueue<ServiceRequest> temp = pq;

    while (!temp.isEmpty()) {
        ServiceRequest s = temp.dequeue();
        arr.push_back(s.toJson());
    }

    ofstream file(requestsFile);
    file << arr.dump(4);
    return true;
}

bool UtilityJsonHelper::loadServiceRequests(PriorityQueue<ServiceRequest>& pq) {
    ifstream file(requestsFile);
    if (!file.good()) return false;

    json arr;
    file >> arr;

    for (auto& obj : arr) {
        ServiceRequest s;
        s.fromJson(obj);
        pq.enqueue(s);
    }
    return true;
}

// ---------------- Graph ----------------
// ---------------- Graph ----------------
bool UtilityJsonHelper::saveGraph(Graph& g) {
    json obj = g.toJson();  // Now returns json
    ofstream file(graphFile);
    file << obj.dump(4);
    return true;
}

bool UtilityJsonHelper::loadGraph(Graph& g) {
    ifstream file(graphFile);
    if (!file.good()) return false;

    json obj;
    file >> obj;
    g.fromJson(obj);  // Now takes json parameter
    return true;
}