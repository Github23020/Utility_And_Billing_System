#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

const string FILE_NAME = "users.json";

class JsonHelper {
public:

    static void initializeFile(const string &filename) {
        ifstream file(filename);
        if (!file.good()) {
            ofstream createFile(filename);
            createFile << "[]";
            createFile.close();
        }
    }

    static json readJsonFile(const string &filename) {
        initializeFile(filename);
        json data = json::array();

        ifstream file(filename);
        if (file.good()) {
            try {
                file >> data;
            } catch (...) {
                data = json::array();
            }
        }
        return data;
    }

    static bool adminExists() {
        json data = readJsonFile(FILE_NAME);

        for (int i = 0; i < data.size(); i++) {
            if (data[i]["role"] == "admin")
                return true;
        }
        return false;
    }

    static bool isUsernameTaken(const string &uname) {
        json data = readJsonFile(FILE_NAME);

        for (int i = 0; i < data.size(); i++) {
            if (data[i]["username"] == uname)
                return true;
        }
        return false;
    }

    static void saveUser(const string &role,
                         const string &uname,
                         const string &name,
                         const string &pwd) {
        json data = readJsonFile(FILE_NAME);

        json newUser = {
                {"role",     role},
                {"username", uname},
                {"name",     name},
                {"password", pwd}
        };

        data.push_back(newUser);

        ofstream file(FILE_NAME);
        file << data.dump(4);
        file.close();
    }

    static bool loginUser(const string &uname,const string &pwd,string &role_out){
        json data = readJsonFile(FILE_NAME);

        for (int i = 0; i < data.size(); i++) {
            if (data[i]["username"] == uname &&
                data[i]["password"] == pwd) {
                role_out = data[i]["role"];
                return true;
            }
        }
        return false;
    }

    static json getUserData(const string &uname) {
        json data = readJsonFile(FILE_NAME);

        for (int i = 0; i < data.size(); i++) {
            if (data[i]["username"] == uname)
                return data[i];
        }

        return json(); // return empty json object
    }
};

#endif
