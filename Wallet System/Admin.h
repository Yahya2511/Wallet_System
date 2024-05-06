#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class Admin
{
    string adminName;
    int adminId;

public:
    Admin();

    bool static login(string, string);

    void AddUser(unordered_map<string, class User>& usersMap, double initialBalance);
    void EditUsersPassword(unordered_map<string, class User>& users, string userName);
    void DeleteUser(unordered_map<string, class User>& usersMap, string userName);
    void SuspendUser(unordered_map<string, class User>& usersMap, string userName);
    void ReactivateUser(unordered_map<string, class User>& usersMap, string userName);

    void ViewUniTransaction(stack<class Transaction> sysHistory);
  
    void adjustBalance(unordered_map<string, class User>);
    void viewUsersInfo(unordered_map<string, class User>& users);
};
