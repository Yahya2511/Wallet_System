#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Admin
{
    string adminName;
    int adminId;

public:
    Admin();

    bool static login(string, string);

    void AddUser(map<string, class User>& usersMap, double initialBalance);
    void EditUsersPassword(map<string, User>& users, string userName);
    void DeleteUser(map<string, class User>& usersMap, string userName);
    void SuspendUser(map<string, class User>& usersMap, string userName);
    void ReactivateUser(map<string, class User>& usersMap, string userName);
  
    void viewUsersInfo(map<string, User>& users);
};