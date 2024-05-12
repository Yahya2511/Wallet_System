#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "User.h"
#include "Transaction.h"
#include "Admin.h"
#include "ctime"

using namespace std;

void loadUsers(unordered_map<string, User>& users, string fileName);
void saveUsers(unordered_map<string, User>& users, string fileName);

void loadSystemHistory(stack<Transaction>& systemHistory, string fileName);
void saveSystemHistory(stack<Transaction>& systemHistory, string fileName);

int getInt();

int main()
{
	string usersFileName = "usersData.txt";
	string systemHistoryFileName = "systemHistory.txt";

	string activeUser = "";

	bool runProgram = true;
	bool inWelcome = true;
	bool inHome = false;
	bool inAdmin = false;

	unordered_map<string, User> users;
	Admin admin;
	stack<Transaction> systemHistory;

	loadUsers(users, usersFileName);
	loadSystemHistory(systemHistory, systemHistoryFileName);

	while (runProgram)
	{
		while (inWelcome)
		{
			int choice;

			cout << "~~~~~~~~~~~ Welcome to the Wallet system ~~~~~~~~~~~\n\n" <<
				"1. Login.\n" <<
				"2. Register.\n" <<
				"3. Exit.\n" <<
				"Choice: ";

			choice = getInt();

			string checkUserName;

			switch (choice)
			{
			case 1:
				checkUserName = User::login(users, admin);
				if (checkUserName != "")
				{
					if (checkUserName == "Admin")
					{
						activeUser = checkUserName;
						inWelcome = false;
						inAdmin = true;
					}
					else
					{
						activeUser = checkUserName;
						inWelcome = false;
						inHome = true;
					}
				}
				break;
			case 2:
				User::userRegister(users);
				break;
			case 3:
				inWelcome = false;
				runProgram = false;
				break;
			case -1:
				cout << "invalid input!\nYou can not use words here!\n\n";
				break;
			default:
				cout << "Invalid Input\n\n";
				break;
			}
		}
		while (inHome)
		{
			int choice;
			cout << "Hi " << activeUser << "\n\n" <<
				"Enter the operation you want to select\n" <<
				"1. View Balance.\n" <<
				"2. Make Transaction.\n" <<
				"3. View History.\n" <<
				"4. Make a Request.\n" <<
				"5. View Request.\n" <<
				"6. Edit Password.\n" <<
				"7. Block User.\n" <<
				"8. Unblock User.\n" <<
				"9. Logout.\n" <<
				"10. Exit.\n" <<
				"Choice: ";

			choice = getInt();

			switch (choice)
			{
			case 1: 
				users[activeUser].viewBalance();
				break;
			case 2:
				users[activeUser].makeTransaction(users, systemHistory);
				break;
			case 3:
				users[activeUser].viewHistory();
				break;
			case 4:
				users[activeUser].requestTransaction(users);
				break;
			case 5:
				users[activeUser].viewRequest(users, systemHistory);
				break;
			case 6:
				users[activeUser].editPassword();
				break;
			case 7:
				users[activeUser].blockUser(users);
				break;
			case 8:
				users[activeUser].unBlockUser(users);
				break;
			case 9:
				activeUser = "";
				inHome = false;
				inWelcome = true;

				cout << "Logged out successful.\n\n";
				break;
			case 10:
				inHome = false;
				runProgram = false;
				break;
			case -1:
				cout << "invalid input!\nYou can not use words here!\n\n";
				break;
			default:
				cout << "Invalide choice (" << choice << ")\n\n";
				cout << "you can only choose form the above list\n";
				break;
			}
		}
		while (inAdmin)
		{
			int choice;
			cout << "Hi " << activeUser << "\n\n" <<
				"Enter the operation you want to select\n" <<
				"1. View all users.\n" <<
				"2. Add User.\n" <<
				"3. Edit User.\n" <<
				"4. Delete User.\n" <<
				"5. Suspend User.\n" <<
				"6. Activate User.\n" <<
				"7. View System Transation History.\n" <<
				"8. Adjust User's Balance.\n" <<
				"9. Logout.\n" <<
				"10. Exit.\n" <<
				"Choice: ";

			choice = getInt();

			string userName;

			switch (choice)
			{
			case 1:
				admin.viewUsersInfo(users);
				break;
			case 2:
				admin.AddUser(users, 1000);
				break;
			case 3:
				cout << "Enter User name to edit him/her: ";
				getline(cin, userName);

				admin.EditUsersPassword(users, userName);

				break;
			case 4:
				cout << "Enter User name to Delete him/her: ";
				getline(cin, userName);

				admin.DeleteUser(users, userName);
				break;
			case 5:
				cout << "Enter User name to suspend him/her: ";
				getline(cin, userName);

				admin.SuspendUser(users, userName);
				break;
			case 6:
				cout << "Enter User name to activate him/her: ";
				getline(cin, userName);

				admin.ReactivateUser(users, userName);
				break;
			case 7:
				admin.ViewUniTransaction(systemHistory);
				break;
			case 8:
				admin.adjustBalance(users);
				break;
			case 9:
				activeUser = "";
				inAdmin = false;
				inWelcome = true;

				cout << "Logged out successful.\n\n";
				break;
			case 10:
				inAdmin = false;
				runProgram = false;
				break;
			case -1:
				cout << "invalid input!\nYou can not use words here!\n\n";
				break;
			default:
				cout << "Invalide choice (" << choice << ")\n\n";
				cout << "you can only choose form the above list\n";
				break;
			}
		}
	}

	saveUsers(users, usersFileName);
	saveSystemHistory(systemHistory, systemHistoryFileName);

	cout << "Program Exited.\n";
	return 0;
}

void loadUsers(unordered_map<string, User>& users, string fileName)
{
	ifstream data;

	data.open(fileName);

	if (data.fail())
	{
		cout << "Error opening file!!!!" << endl;
		exit(1);
	}

	string userKey;
	string userPass;
	string gmail;
	string userStatus;
	string strBalance;
	double userBalance = 0;

	stack<Transaction> temp;
	
	while (!data.eof())
	{
		//username
		getline(data, userKey, '|');
		if (userKey == "0")
		{
			cout << "System History is empty\n";
			data.close();
			return;
		}
		//Password
		getline(data, userPass, '|');
		//gmail
		getline(data, gmail, '|');
		//Status
		getline(data, userStatus, '|');
		
		getline(data, strBalance);

		//Balance
		userBalance = stod(strBalance);

		users[userKey] = User(userKey, userPass, userBalance, gmail);

		if (userStatus == "Active")
			users[userKey].setStatus(Status::Active);
		else
			users[userKey].setStatus(Status::Suspend);

		int setSize;
		data >> setSize;
		data.ignore();

		string blockedUserName;

		for (int setIndex = 0; setIndex < setSize; setIndex++)
		{
			getline(data, blockedUserName);
			users[userKey].getBlockedSet().insert(blockedUserName);
		}


		//user history
		int historySize;
		data >> historySize;
		data.ignore();

		string sender, reciver, date, strAmount;
		double amount;

		for (int stackIndex = 0; stackIndex < historySize; stackIndex++)
		{
			getline(data, sender, '|');
			getline(data, reciver, '|');
			getline(data, date, '|');
			getline(data, strAmount);
			
			amount = stod(strAmount);

			temp.push(Transaction(sender, reciver, date, amount));
		}

		
		//requests part
		int queueSize;
		
		data >> queueSize;
		data.ignore();

		for (int queueIndex = 0; queueIndex < queueSize; queueIndex++)
		{
			getline(data, sender, '|');
			getline(data, reciver, '|');
			getline(data, date, '|');
			getline(data, strAmount);

			amount = stod(strAmount);

			users[userKey].addTransactionToVector(Transaction(sender, reciver, date, amount));
		}

		while (!temp.empty())
		{
			users[userKey].addTransactionToStack(temp.top());
			temp.pop();
		}
	}

	data.close();

	cout << "Users data has been loaded successfully\n";
}
void saveUsers(unordered_map<string, User>& users, string fileName)
{
	ofstream data;

	bool fileEnd = false;

	data.open(fileName);

	if (data.fail())
	{
		cout << "Error opening file!!!!" << endl;
		exit(1);
	}

	unordered_map<string, User>::iterator it;

	if (users.empty())
	{
		data << 0;
		data.close();
		return;
	}

	for (it = users.begin(); it != users.end(); it++)
	{
		data << it->second.getUserName() << '|' <<
			it->second.getPassword() << '|' << 
			it->second.getGmail() << '|';

		if (it->second.getStatus() == Status::Active)
			data << "Active|";
		else
			data << "Suspend|";

		data << it->second.getBalance() << '\n';

		//blocked users
		data << it->second.getBlockedSet().size() << '\n';
		while (!it->second.getBlockedSet().empty())
		{
			data << *it->second.getBlockedSet().begin() << '\n';
			it->second.getBlockedSet().erase(it->second.getBlockedSet().begin());
		}

		long long historySize = it->second.getTransaction().size();
		data << historySize << '\n';
		while (!it->second.getTransaction().empty())
		{
			data << it->second.getTransaction().top().Get_Sender() << '|' <<
				it->second.getTransaction().top().Get_Reciver() << "|" <<
				it->second.getTransaction().top().Get_date() << "|" <<
				it->second.getTransaction().top().Get_Amount() << "\n";

			it->second.getTransaction().pop();
		}



		long long  queueSize = it->second.getVector().size();
		data << queueSize;
		if (queueSize == 0)
		{
			it++;
			if (it != users.end())
			{
				data << "\n";
			}
			it--;
		}
		else
		{
			data << "\n";
		}
		while (!it->second.getVector().empty())
		{
			data << it->second.getVector().front().Get_Sender() << '|' <<
				it->second.getVector().front().Get_Reciver() << "|" <<
				it->second.getVector().front().Get_date() << "|" <<
				it->second.getVector().front().Get_Amount();

			string front = it->second.getVector().front().Get_date();
			string back = it->second.getVector().back().Get_date();
			it->second.getVector().pop_back();

			it++;
			if (it != users.end() || (front != back))
			{
				data << "\n";
			}
			it--;
		}
	}

	data.close();
}

void loadSystemHistory(stack<Transaction>& systemHistory, string fileName)
{
	ifstream data;

	data.open(fileName);

	if (data.fail())
	{
		cout << "Error opening file!!!!" << endl;
		exit(1);
	}

	stack<Transaction> temp;

	string sender, reciver, date, strAmount;
	double amount;

	while (!data.eof())
	{
		getline(data, sender, '|');
		if (sender == "0")
		{
			cout << "System History is empty\n";
			data.close();
			return;
		}
		getline(data, reciver, '|');
		getline(data, date, '|');
		getline(data, strAmount);

		amount = stod(strAmount);

		temp.push(Transaction(sender, reciver, date, amount));
	}

	while (!temp.empty())
	{
		systemHistory.push(temp.top());
		temp.pop();
	}

	data.close();

	cout << "System data has been loaded successfully\n";

}
void saveSystemHistory(stack<Transaction>& systemHistory, string fileName)
{
	ofstream data;

	data.open(fileName);

	if (data.fail())
	{
		cout << "Error opening file!!!!" << endl;
		exit(1);
	}

	if (systemHistory.empty())
	{
		data << 0;
		data.close();
		return;
	}

	while (!systemHistory.empty())
	{
		data << systemHistory.top().Get_Sender() << "|"
			<< systemHistory.top().Get_Reciver() << "|"
			<< systemHistory.top().Get_date() << "|"
			<< systemHistory.top().Get_Amount();
		systemHistory.pop();
		if (!systemHistory.empty())
		{
			data << '\n';
		}
	}
}

int getInt()
{
	string input;
	int number = 0;
	getline(cin, input);

	if (input.length() > 7)
		return -1;

	bool notInt = false;
	for (char c : input)
	{
		if (c >= '0' && c <= '9')
		{
			number = number * 10 + (c - '0');
		}
		else
		{
			return -1;
		}
	}
	return number;
}