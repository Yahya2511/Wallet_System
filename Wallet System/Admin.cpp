#include "Admin.h"
#include "User.h"


Admin::Admin()
{
	adminName = "Admin";
	adminId = 1;
}

bool Admin::login(string Username, string Password)
{
    if (Username == "admin" && Password == "admin") {
        return true;
    }
    else
        return false;
}

void Admin::AddUser(map<string, User>& users, double balance)
{
    while (true) 
    {
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
// edited part is removing current pass and new pass form the function atribute.

//Note this code can be cleaner by applying the if(!true){return}

void Admin::EditUsersPassword(map<string, User>& users, string userName) 
{
    string currentPassword, newPassword;
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
            cout << "Incorrect current password.\n";
    }
    else
        cout << "User " << userName << " not found.\n";
}

void Admin::DeleteUser(map<string, User>& users, string userName)
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

void Admin::SuspendUser(map<string, User>& users, string userName)
{
    map<string, User>::iterator it = users.find(userName);
    if (it != users.end()) 
    {
        it->second.setStatus(Suspend);
        cout << "User " << userName << " has been suspended." << endl;
    }
    else 
        cout << "User " << userName << " not found." << endl;
}

void Admin::ReactivateUser(map<string, User>& users, string userName)
{
    map<string, User>::iterator it = users.find(userName);
    if (it != users.end())
    {
        it->second.setStatus(Active);
        cout << "User " << userName << " has been reactivated." << endl;
    }
    else
        cout << "User " << userName << " not found." << endl;
}

void Admin::viewUsersInfo(map<string, User>& users)
{
    int size = users.size();
    map<string, User>::iterator it = users.begin();
    while (it != users.end())
    {
        cout << "User Name: " << it->first << endl;
        cout << "User Balance: " << it->second.getBalance() << endl;
        cout << "Transaction history : " << endl;
        it->second.viewHistory();
        it++;
    }
}
