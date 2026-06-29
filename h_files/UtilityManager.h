#ifndef UTILITYMANAGER_H
#define UTILITYMANAGER_H

#include <string>
#include "Account.h"
#include "Project_Templates/MyArray.h"
#include "Project_Templates/LinkedQueue.h"
#include "Project_Templates/PriorityQueue.h"
#include "Graph.h"
#include "Complaint.h"
#include "ServiceRequest.h"

class UtilityManager {
private:
    MyArray<Account> accounts;
    LinkedQUEUE<Complaint> complaintQueue;
    PriorityQueue<ServiceRequest> serviceQueue;
    Graph networkGraph;


public:
    Account *findAccountById(int accountId);

    Account *findAccountByPrompt();

    void loadSystemData();

    void saveSystemData();

    UtilityManager(int graphNodes = 0);

    // Account operations
    void createAccount();

    void addUsage();

    void generateBill();

    void showBills();
    void payBill();

    // Complaint operations
    void submitComplaint();

    void processNextComplaint();

    void viewAllComplaints();

    // Service Request operations
    void submitServiceRequest();

    void processNextServiceRequest();

    void viewAllServiceRequests();

    // Graph operations
    void connectServiceAreas();

    void checkServiceAreaConnection();

    void showServiceAreaConnections();

    // Menu
    void showMenu();


    MyArray<Bill> getAllBills();

    void displayBills(const MyArray<Bill> &bills, const string &title);

    void BubbleSort();

    void MergeSort();

    void HeapSort();

    void showSortingMenu();
};

#endif