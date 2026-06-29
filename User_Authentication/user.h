#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "json_helper.h"

using namespace std;

template<typename T>
class User {
protected:
    string username;
    string name;
    string password;

public:
    User() {}

    User(const string &uname, const string &nm, const string &pwd)
            : username(uname), name(nm), password(pwd) {}

    virtual void displayInfo() const {
        cout << "Username: " << username << ", Name: " << name << endl;
    }

    string getUsername() const { return username; }

    string getName() const { return name; }

    string getPassword() const { return password; }
};

class Admin : public User<Admin> {
private:
    static Admin *instance;
    bool accountCreated;

    Admin(const string &uname, const string &nm, const string &pwd)
            : User(uname, nm, pwd), accountCreated(false) {}

public:

    static Admin *getInstance(const string &uname = "",
                              const string &nm = "",
                              const string &pwd = "") {
        if (!instance) {
            instance = new Admin(uname, nm, pwd);
            instance->accountCreated = true;
        }
        return instance;
    }

    bool isAccountCreated() const { return accountCreated; }

    void displayInfo() const override {
        cout << "[Admin] ";
        User::displayInfo();
    }


    void createStaff() {
        string uname, name, pwd;

        cout << "\n--- Create Staff Account ---\n";
        cout << "Enter staff username: ";
        cin >> uname;

        if (JsonHelper::isUsernameTaken(uname)) {
            cout << "Username already exists!\n";
            return;
        }

        cout << "Enter staff name: ";
        cin >> name;

        cout << "Enter staff password: ";
        cin >> pwd;

        JsonHelper::saveUser("staff", uname, name, pwd);

        cout << "Staff account created successfully!\n";
    }

    void viewStaff() {
        json data = JsonHelper::readJsonFile("users.json");

        cout << "\n--- Staff List ---\n";

        bool found = false;

        for (int i = 0; i < data.size(); i++) {
            if (data[i]["role"] == "staff") {
                cout << "Username: " <<  data[i]["username"]
                     << " | Name: " <<  data[i]["name"] << endl;
                found = true;
            }
        }

        if (!found) cout << "No staff accounts found!\n";
    }

    void updateStaff() {
        string uname, newName, newPwd;

        cout << "\nEnter staff username to update: ";
        cin >> uname;

        json target = JsonHelper::getUserData(uname);

        if (target.empty() || target["role"] != "staff") {
            cout << "Staff not found!\n";
            return;
        }

        cout << "Enter new name: ";
        cin >> newName;
        cout << "Enter new password: ";
        cin >> newPwd;

        json data = JsonHelper::readJsonFile("users.json");

        for (int i = 0; i < data.size(); i++) {
            if (data[i]["username"] == uname) {
                data[i]["name"] = newName;
                data[i]["password"] = newPwd;
                break;
            }
        }

        ofstream file("users.json");
        file << data.dump(4);
        file.close();

        cout << "Staff updated successfully!\n";
    }

    void deleteStaff() {
        string uname;

        cout << "\nEnter staff username to delete: ";
        cin >> uname;

        json data = JsonHelper::readJsonFile("users.json");
        json updated = json::array();
        bool removed = false;

        for (int i = 0; i < data.size(); i++) {
            if (data[i]["username"] == uname && data[i]["role"] == "staff") {
                removed = true;
                continue;
            }
            updated.push_back(data[i]);
        }

        if (removed) {
            ofstream file("users.json");
            file << updated.dump(4);
            file.close();
            cout << "Staff deleted successfully!\n";
        } else {
            cout << "Staff not found.\n";
        }
    }


    void adminMenu() {
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

            if (choice == 1) createStaff();
            else if (choice == 2) viewStaff();
            else if (choice == 3) updateStaff();
            else if (choice == 4) deleteStaff();
            else if (choice == 5) return;
            else cout << "Invalid option!\n";
        }
    }
};

Admin *Admin::instance = nullptr;

#endif // USER_H
