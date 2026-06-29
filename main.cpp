#include <iostream>
#include "User_Authentication/json_helper.h"
#include "User_Authentication/user.h"
#include "h_files/UtilityManager.h"
#include "h_files/UtilityJsonHelper.h"


using namespace std;

bool loginAdmin() {
    string username, pwd, role;

    cout << "\n--- Admin Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> pwd;

    if (JsonHelper::loginUser(username, pwd, role) && role == "admin") {
        cout << "Admin login successful!\n";
        return true;
    }

    cout << "Invalid admin credentials.\n";
    return false;
}

bool loginStaff(string &usernameOut) {
    string username, pwd, role;

    cout << "\n--- Staff Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> pwd;

    if (JsonHelper::loginUser(username, pwd, role) && role == "staff") {
        cout << "Staff login successful!\n";
        usernameOut = username;
        return true;
    }

    cout << "Invalid staff credentials.\n";
    return false;
}

//  STAFF MENU FUNCTION
void staffMenu(const string &username) {
    json data = JsonHelper::getUserData(username);

    if (data.empty()) {
        cout << "Staff data not found!\n";
        return;
    }

    cout << "\nWelcome, " << data["name"] << "!\n";
    cout << "Username: " << data["username"] << "\n";
    cout << "Role: Staff\n";

    UtilityManager manager(10);
    int choice;
    while (true) {
        cout << "\n=== Staff Main Menu ===\n";
        cout << "1. View Profile\n";
        cout << "2. Utility Management System\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {

            cout << "\n=== Staff Profile ===\n";
            cout << "Name: " << data["name"] << endl;
            cout << "Username: " << data["username"] << endl;
            cout << "Role: Staff" << endl;
        } else if (choice == 2) {

            manager.showMenu();
        } else if (choice == 3) {
            // Save data before logout
            manager.saveSystemData();
            cout << "\nData saved successfully.\n";
            cout << "Logging out...\n";
            return;
        } else {
            cout << "Invalid option!\n";
        }
    }
}

// admin menu

void adminMenu() {
    Admin *admin = Admin::getInstance();

    int choice;
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Create Staff\n";
        cout << "2. View Staff\n";
        cout << "3. Update Staff\n";
        cout << "4. Delete Staff\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            admin->createStaff();
        } else if (choice == 2) {
            admin->viewStaff();
        } else if (choice == 3) {
            admin->updateStaff();
        } else if (choice == 4) {

            admin->deleteStaff();
        } else if (choice == 5) {
            return;
        } else {
            cout << "Invalid option!\n";
        }
    }
}



int usman_main() {
    // initialing json file
    JsonHelper::initializeFile("users.json");


    cout << "\n========================================\n";
    cout << "   ELECTRICITY BILLING SYSTEM\n";
    cout << "========================================\n";

    cout << "\n=== System Information ===\n";
    cout << "Data Structures Used:\n";
    cout << "1. MyArray - Account and Bill storage\n";
    cout << "2. List - Usage history management\n";
    cout << "3. LinkedQueue - Complaint processing (FIFO)\n";
    cout << "4. PriorityQueue - Service requests (Max-Heap)\n";
    cout << "5. Graph - Service area connectivity\n";
    cout << "========================================\n\n";

    int choice;

    while (true) {
        cout << "\n===== Select Role =====\n";
        cout << "1. Admin\n";
        cout << "2. Staff\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (loginAdmin()) {
                adminMenu();
            }
        } else if (choice == 2) {
            string staffUser;
            if (loginStaff(staffUser)) {
                staffMenu(staffUser);
            }
        } else if (choice == 3) {
            cout << "\nThank you for using the Electricity Billing System!\n";
            cout << "========================================\n";
            return 0;
        } else {
            cout << "Invalid option.\n";
        }
    }
}