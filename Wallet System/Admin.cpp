#include "Admin.h"
#include "User.h"
#include<iostream>
#include<vector>
#include<map>
#include<iterator>
#include <string>

using namespace std;

Admin::Admin() 
{
    adminName = "0";
    adminId = 0;
}

void Admin::AddUser(double initialBalance) 
{
    while (true) {
        string userName;
        cout << "Please enter user name\n\n";
        cin >> userName;
        if (users.find(userName) != users.end()) 
        {
            cout << "Sorry, this user name already exists!\n\n";
            continue;
        }
        else 
        {
            User user(userName, "1", initialBalance);
            users[userName] = user;
            cout << "User " << userName << " added successfully!\n\n";
            break;
        }
    }
}
void Admin::EditusersPassword(string& userName, string& currentPassword, string& newPassword) 
{
    map<string, User>::iterator it = users.find(userName);
    if (users.find(userName) != users.end()) 
    {
        cout << "Enter current password for user " << userName << ":\n";
        cin >> currentPassword;
        if (it->second.getPassword() == currentPassword) 
        {
            cout << "Enter new password for user " << userName << ":\n";
            cin >> newPassword;
            it->second.setPassword(newPassword);
            cout << "Password for user " << userName << " has been updated.\n";
        }
        else 
        {
            cout << "Incorrect current password.\n";
        }


    }
    else 
    {
        cout << "User " << userName << " not found.\n";
    }
}

void Admin::DeleteUser(string& userName)

{
    map<string, User>::iterator it = users.find(userName);
    if (it != users.end()) 
    {
        users.erase(userName);
        cout << "User " << userName << " has been deleted.\n";
    }
    else
        cout << "User " << userName << " not found.\n";

}

void Admin::SuspendUser(string& userName)
{

    map<string, User>::iterator it = users.find(userName);
    if (it != users.end()) 
    {
        it->second.setStatus(Suspend);
        cout << "User " << userName << " has been suspended." << endl;
    }
    else 
    {
        cout << "User " << userName << " not found." << endl;
    }
}

void Admin::ReactivateUser(string& userName)
{
    map<string, User>::iterator it = users.find(userName);
    if (it != users.end()) 
    {
        it->second.setStatus(Active);
        cout << "User " << userName << " has been reactivated." << endl;
    }
    else 
    {
        cout << "User " << userName << " not found." << endl;
    }
}