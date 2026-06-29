#include "../h_files/UtilityManager.h"
#include "../h_files/UtilityJsonHelper.h"
#include <iostream>

using namespace std;

// Constructor
UtilityManager::UtilityManager(int graphNodes)
        : networkGraph(graphNodes) {
    loadSystemData();
}

// Find account by ID
Account *UtilityManager::findAccountById(int id) {
    for (int i = 0; i < accounts.get_size(); i++) {
        if (accounts[i].getAccountId() == id)
            return &accounts[i];
    }
    return nullptr;
}

// Prompt user for account ID and find account
Account *UtilityManager::findAccountByPrompt() {
    int id;
    cout << "Enter Account ID: ";
    cin >> id;
    return findAccountById(id);
}


void UtilityManager::createAccount() {
    Account acc;
    acc.input();
    accounts.append(acc);
    cout << "Account created successfully!\n";
}

void UtilityManager::addUsage() {
    Account *acc = findAccountByPrompt();
    if (!acc) {
        cout << "Account not found\n";
        return;
    }
    acc->addUsage();
}

// Generate bill
void UtilityManager::generateBill() {
    Account *acc = findAccountByPrompt();
    if (!acc) {
        cout << "Account not found\n";
        return;
    }
    Bill newBill = acc->generateBill();
    cout << "Bill generated successfully!\n";
    newBill.displayBill();

}

// Show all bills for account
void UtilityManager::showBills() {
    Account *acc = findAccountByPrompt();
    if (!acc) {
        cout << "Account not found\n";
        return;
    }
    acc->displayBills();

}


// Submi complaint
void UtilityManager::submitComplaint() {
    Complaint c;
    c.input();
    complaintQueue.enqueue(c);
    cout << "Complaint submitted successfully!\n";
}

//  next complaint in queue
void UtilityManager::processNextComplaint() {
    if (complaintQueue.isEmpty()) {
        cout << "No complaints to process\n";
        return;
    }
    Complaint c = complaintQueue.dequeue();
    cout << "Processing complaint:\n";
    c.displayComplaint();
}

// View all complaints
void UtilityManager::viewAllComplaints() {
    if (complaintQueue.isEmpty()) {
        cout << "No complaints in queue\n";
        return;
    }
    cout << "Complaints in queue (FIFO order):\n";
    complaintQueue.printQueue();
}


void UtilityManager::submitServiceRequest() {
    ServiceRequest s;
    s.input();
    serviceQueue.enqueue(s);
    cout << "Service request submitted successfully!\n";
}


void UtilityManager::processNextServiceRequest() {
    if (serviceQueue.isEmpty()) {
        cout << "No service requests to process\n";
        return;
    }
    ServiceRequest s = serviceQueue.dequeue();
    cout << "Processing service request (highest priority):\n";
    s.displayRequest();
}

//  service requests in priority order
void UtilityManager::viewAllServiceRequests() {
    if (serviceQueue.isEmpty()) {
        cout << "No service requests in queue\n";
        return;
    }
    cout << "Service requests in priority order (highest first):\n";
    serviceQueue.printHeap();
}

void UtilityManager::connectServiceAreas() {
    int area1, area2;

    cout << "\n--- Connect Service Areas ---\n";
    cout << "Enter first service area ID (0-" << (networkGraph.getNodeCount() - 1) << "): ";
    cin >> area1;
    cout << "Enter second service area ID (0-" << (networkGraph.getNodeCount() - 1) << "): ";
    cin >> area2;

    networkGraph.addConnection(area1, area2);
}


void UtilityManager::checkServiceAreaConnection() {
    int area1, area2;

    cout << "\n--- Check Service Area Connection ---\n";
    cout << "Enter first service area ID: ";
    cin >> area1;
    cout << "Enter second service area ID: ";
    cin >> area2;

    if (networkGraph.isConnected(area1, area2)) {
        cout << "Service areas " << area1 << " and " << area2 << " are connected.\n";
    } else {
        cout << "Service areas " << area1 << " and " << area2 << " are NOT connected.\n";
    }
}

// Display all
void UtilityManager::showServiceAreaConnections() {
    networkGraph.displayConnections();
}

// ---------------- Menu ----------------
void UtilityManager::showMenu() {
    int choice;

    do {
        cout << "\n=== Utility Management Menu ===\n";
        cout << "1. Create New Account\n";
        cout << "2. Add Usage to Account\n";
        cout << "3. Generate Bill\n";
        cout << "4. View Bills\n";
        cout << "5. Submit Complaint\n";
        cout << "6. Process Next Complaint\n";
        cout << "7. View All Complaints\n";
        cout << "8. Submit Service Request\n";
        cout << "9. Process Next Service Request\n";
        cout << "10. View All Service Requests\n";
        cout << "11. Connect Service Areas\n";
        cout << "12. Check Service Area Connection\n";
        cout << "13. View Service Area Network\n";
        cout << "=== SORTING ALGORITHMS ===\n";
        cout << "14. Sorting Algorithms \n";
        cout << "15. Save Data & Return to Staff Menu\n";
        cout << "0. Return to Staff Menu (without save)\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                createAccount();
                break;
            }
            case 2: {
                addUsage();
                break;
            }
            case 3: {
                generateBill();
                break;
            }
            case 4: {
                showBills();
                break;
            }
            case 5: {
                submitComplaint();
                break;
            }
            case 6: {
                processNextComplaint();
                break;
            }
            case 7: {
                viewAllComplaints();
                break;
            }
            case 8: {
                submitServiceRequest();
                break;
            }
            case 9: {
                processNextServiceRequest();
                break;
            }
            case 10: {
                viewAllServiceRequests();
                break;
            }
            case 11: {
                connectServiceAreas();
                break;
            }
            case 12: {
                checkServiceAreaConnection();
                break;
            }
            case 13: {
                showServiceAreaConnections();
                break;
            }
            case 14: {
                showSortingMenu();
                break;
            }
            case 15: {
                saveSystemData();
                cout << "Data saved successfully.\n";
                return;
            }
            case 0: {
                cout << "Returning to Staff Menu...\n";
                return;
            }
            default: {
                cout << "Invalid choice!\n";
            }
        }
    } while (choice != 0);
}

void UtilityManager::loadSystemData() {
    UtilityJsonHelper::loadAccounts(accounts);
    UtilityJsonHelper::loadComplaints(complaintQueue);
    UtilityJsonHelper::loadServiceRequests(serviceQueue);
    UtilityJsonHelper::loadGraph(networkGraph);
}

// Save all data to JSON files
void UtilityManager::saveSystemData() {
    UtilityJsonHelper::saveAccounts(accounts);
    UtilityJsonHelper::saveComplaints(complaintQueue);
    UtilityJsonHelper::saveServiceRequests(serviceQueue);
    UtilityJsonHelper::saveGraph(networkGraph);
}


// Get all bills from all accounts
MyArray<Bill> UtilityManager::getAllBills() {
    MyArray<Bill> allBills;

    for (int i = 0; i < accounts.get_size(); i++) {
        Account &acc = accounts[i];
        for (int j = 0; j < acc.billList.get_size(); j++) {
            allBills.append(acc.billList[j]);
        }
    }

    return allBills;
}

// Simple display function
void UtilityManager::displayBills(const MyArray<Bill> &bills, const string &title) {
    cout << "\n" << title << ":\n";
    cout << "ID | Account | Amount | Units | Month | Status\n";
    cout << "----------------------------------------------\n";

    if (bills.get_size() == 0) {
        cout << "No bills found.\n";
        return;
    }

    for (int i = 0; i < bills.get_size(); i++) {
        const Bill &bill = bills[i];
        double units = bill.getAmount() / 10.0;

        cout << bill.getBillId() << " | ";
        cout << bill.getAccountId() << " | ";
        cout << "$" << fixed << setprecision(2) << bill.getAmount() << " | ";
        cout << fixed << setprecision(1) << units << " units | ";
        cout << bill.getMonth() << " | ";
        cout << (bill.getPaidStatus() ? "Paid" : "Unpaid") << endl;
    }
    cout << "----------------------------------------------\n";
}

void mergeArrays(Bill arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    Bill *leftArr = new Bill[n1];
    Bill *rightArr = new Bill[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge temp arrays back
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].getAmount() <= rightArr[j].getAmount()) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

// Helper function for merge sort
void mergeSortHelper(Bill arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        // Merge the sorted halves
        mergeArrays(arr, left, mid, right);
    }
}

// Helper function for heap sort
void heapify(Bill arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < n && arr[left].getAmount() > arr[largest].getAmount())
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right].getAmount() > arr[largest].getAmount())
        largest = right;

    // If largest is not root
    if (largest != i) {
        // Swap
        Bill temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void UtilityManager::BubbleSort() {
    cout << "\n=== BUBBLE SORT ===\n";

    MyArray<Bill> allBills = getAllBills();

    if (allBills.get_size() == 0) {
        cout << "No bills found.\n";
        return;
    }

    // BEFORE SORTING
    displayBills(allBills, "BEFORE SORTING");


    int n = allBills.get_size();
    Bill *billsArray = new Bill[n];
    for (int i = 0; i < n; i++) {
        billsArray[i] = allBills[i];
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (billsArray[j].getAmount() > billsArray[j + 1].getAmount()) {

                Bill temp = billsArray[j];
                billsArray[j] = billsArray[j + 1];
                billsArray[j + 1] = temp;
            }
        }
    }


    MyArray<Bill> sortedBills;
    for (int i = 0; i < n; i++) {
        sortedBills.append(billsArray[i]);
    }

    delete[] billsArray;

    // AFTER SORTING
    displayBills(sortedBills, "AFTER BUBBLE SORT");
}

void UtilityManager::MergeSort() {
    cout << "\n=== MERGE SORT ===\n";

    MyArray<Bill> allBills = getAllBills();

    if (allBills.get_size() == 0) {
        cout << "No bills found.\n";
        return;
    }

    // BEFORE SORTING
    displayBills(allBills, "BEFORE SORTING");

    int n = allBills.get_size();
    Bill *billsArray = new Bill[n];
    for (int i = 0; i < n; i++) {
        billsArray[i] = allBills[i];
    }

    // MANUAL MERGE SORT
    mergeSortHelper(billsArray, 0, n - 1);

    MyArray<Bill> sortedBills;
    for (int i = 0; i < n; i++) {
        sortedBills.append(billsArray[i]);
    }

    delete[] billsArray;

    // AFTER SORTING
    displayBills(sortedBills, "AFTER MERGE SORT");
}

void UtilityManager::HeapSort() {
    cout << "\n=== HEAP SORT ===\n";

    MyArray<Bill> allBills = getAllBills();

    if (allBills.get_size() == 0) {
        cout << "No bills found.\n";
        return;
    }

    // BEFORE SORTING
    displayBills(allBills, "BEFORE SORTING");


    int n = allBills.get_size();
    Bill *billsArray = new Bill[n];
    for (int i = 0; i < n; i++) {
        billsArray[i] = allBills[i];
    }


    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(billsArray, n, i);
    }

    for (int i = n - 1; i > 0; i--) {

        Bill temp = billsArray[0];
        billsArray[0] = billsArray[i];
        billsArray[i] = temp;

        heapify(billsArray, i, 0);
    }


    MyArray<Bill> sortedBills;
    for (int i = 0; i < n; i++) {
        sortedBills.append(billsArray[i]);
    }

    delete[] billsArray;

    // AFTER SORTING
    displayBills(sortedBills, "AFTER HEAP SORT");
}


// Sorting menu
void UtilityManager::showSortingMenu() {
    int choice;

    do {
        cout << "\n=== SORTING ALGORITHMS (Manual Implementation) ===\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Merge Sort\n";
        cout << "3. Heap Sort\n";
        cout << "4. View All Bills\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                BubbleSort();
                break;
            }
            case 2: {
                MergeSort();
                break;
            }
            case 3: {
                HeapSort();
                break;
            }
            case 4: {
                displayBills(getAllBills(), "ALL BILLS");
                break;
            }
            case 0: {
                return;
            }
            default: {
                cout << "Invalid choice!\n";
            }
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 0);
}