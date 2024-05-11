#include "Admin.h"
#include "User.h"


Admin::Admin()
{
    passwordHashing();
}

bool Admin::login(string Username, string pass)
{
    passwordHashing(pass);

    if (Username == adminName && pass == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Admin::AddUser(unordered_map<string, User>& users, double balance)
{
    while (true) 
    {
        string userName;
        cout << "Please enter user name\n\n";
        getline(cin, userName);

        if (users.find(userName) != users.end()) 
        {
            cout << "Sorry, this user name already exists!\n\n";
            continue;
        }

        else 
        {
            User user(userName, "1", balance);
            users[userName] = user;
            cout << "User " << userName << " added successfully!\n\n";
            break;
        }
    }
}

void Admin::ViewUniTransaction(stack<Transaction> sysHistory)
{
    cout << "HERE IS THE TRANSACTIONS : \n";
    if (sysHistory.empty())
    {
        cout << "There is No history\n";
        return;
    }
    stack <Transaction>temproryStack;
    temproryStack = sysHistory;
    while (!temproryStack.empty())
    {
        cout << "The sender is " << temproryStack.top().Get_Sender();
        cout << "\t";
        cout << "The amount is " << temproryStack.top().Get_Amount();
        cout << "\t";
        cout << "The reciever is " << temproryStack.top().Get_Reciver();
        cout << "\t";
        cout << "on " << temproryStack.top().Get_date();
        cout << "\n";
        cout << "*********************************************";
        cout << "\n";
        temproryStack.pop();
    }

}

void Admin::EditUsersPassword(unordered_map<string, User>& users, string userName) 
{
    string currentPassword, newPassword;
    unordered_map<string, User>::iterator it = users.find(userName);

    if (users.find(userName) != users.end()) 
    {
        cout << "Enter current password for user " << userName << ":\n";
        currentPassword = User::inputPassword();
        currentPassword = User::passwordHashing(currentPassword);

        if (it->second.getPassword() == currentPassword)
        {
            cout << "Enter new password for user " << userName << ":\n";
            newPassword = User::inputPassword();
            newPassword = User::passwordHashing(newPassword);

            it->second.setPassword(newPassword);
            cout << "Password for user " << userName << " has been updated.\n";
        }
        else
            cout << "Incorrect current password.\n";
    }
    else
        cout << "User " << userName << " not found.\n";
}

void Admin::DeleteUser(unordered_map<string, User>& users, string userName)
{
    unordered_map<string, User>::iterator it = users.find(userName);
    if (it != users.end()) 
    {
        users.erase(userName);
        cout << "User " << userName << " has been deleted.\n";
    }
    else
        cout << "User " << userName << " not found.\n";
}

void Admin::SuspendUser(unordered_map<string, User>& users, string userName)
{
    unordered_map<string, User>::iterator it = users.find(userName);
    if (it != users.end()) 
    {
        it->second.setStatus(Suspend);
        cout << "User " << userName << " has been suspended." << endl;
    }
    else 
        cout << "User " << userName << " not found." << endl;
}

void Admin::ReactivateUser(unordered_map<string, User>& users, string userName)
{
    unordered_map<string, User>::iterator it = users.find(userName);
    if (it != users.end())
    {
        it->second.setStatus(Active);
        cout << "User " << userName << " has been reactivated." << endl;
    }
    else
        cout << "User " << userName << " not found." << endl;
}

void Admin::adjustBalance(unordered_map<string, User> users) 
{
    string username;
    cout << "Enter username of the user: ";
    getline(cin, username);

    if (users.find(username) == users.end()) 
    {
        cout << "User not found try again" << endl;
        return;
    }

    cout << "Enter the new amount of money after the making adjustion: ";
    double newBalance;
    cin >> newBalance;
    cin.ignore();

    if (newBalance < 0)
        cout << "Error Balance can't be a negative value\n\n";

    users[username].setBalance(newBalance);
    cout << "User balance adjusted successfully." << endl;
}
void Admin::viewUsersInfo(unordered_map<string, User>& users)
{
    long long size = users.size();
    unordered_map<string, User>::iterator it = users.begin();
    while (it != users.end())
    {
        cout << "User Name: " << it->first << endl;
        cout << "User Balance: " << it->second.getBalance() << endl;
        cout << "Transaction history : " << endl;
        it->second.viewHistory();
        it++;
    }
}

void Admin::passwordHashing()
{
    hash<string>hashing;
    long long x = hashing("Admin");
    password = to_string(x);
}
void Admin::passwordHashing(string& pass)
{
    hash<string>hashing;
    long long x = hashing(pass);
    pass = to_string(x);
}