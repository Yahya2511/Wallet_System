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
int getInt();

int main()
{
	string fileName = "usersData.txt";

	string activeUser = "";

	bool runProgram = true;
	bool inWelcome = true;
	bool inHome = false;
	bool inAdmin = false;

	unordered_map<string, User> users;
	unordered_map<string, User>::iterator it;

	Admin admin;

	stack<Transaction> systemHistory;

	loadUsers(users, fileName);

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

			//Login.
			if (choice == 1)
			{
				string checkUserName = User::login(users);
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
			}

			//Register.
			else if (choice == 2)
			{
				User::userRegister(users);
			}

			//Exit.
			else if (choice == 3)
			{
				inWelcome = false;
				runProgram = false;
			}

			//word as input
			else if (choice == -1)
			{
				cout << "invalid input!\nYou can not use words here!\n\n";
			}

			//else.
			else
			{
				cout << "Invalid Input\n\n";
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
				"7. Logout.\n" <<
				"8. Exit.\n" <<
				"Choice: ";

			choice = getInt();

			//View Balance.
			if (choice == 1)
			{
				cout << "Enter your password: ";
				string pass;
				cin >> pass;
				cin.ignore();

				if (pass == users[activeUser].getPassword())
					cout << "Your current balance is: " << users[activeUser].getBalance() << "\n\n";

				else
					cout << "Wrong password!\n\n";

			}

			//Make Transaction.
			else if (choice == 2)
			{
				users[activeUser].makeTransaction(users, systemHistory);
			}

			//view history
			if (choice == 3)
			{
				users[activeUser].viewHistory();
			}

			//Make a Request.
			else if (choice == 4)
			{
				cout << "Enter user name that you want money form: ";
				string receiver;
				cin >> receiver;
				cin.ignore();

				cout << "Enter amount of money you want from him: ";
				double amount;
				cin >> amount;
				cin.ignore();

				users[activeUser].requestTransaction(users);
			}


			//View request
			else if (choice == 5)
			{
				users[activeUser].viewRequest(users, systemHistory);
			}

			//Eidt Password.
			else if (choice == 6)
			{
				users[activeUser].editPassword();
			}
			
			//Logout.
			else if (choice == 7)
			{
				activeUser = "";
				inHome = false;
				inWelcome = true;
			}

			//Exit.
			else if (choice == 8)
			{
				inHome = false;
				runProgram = false;
			}

			//word as input
			else if (choice == -1)
			{
				cout << "invalid input!\nYou can not use words here!\n\n";
			}

			//else.
			else
			{
				cout << "Invalide choice!\n\n";
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

			//View Users
			if (choice == 1)
			{
				admin.viewUsersInfo(users);
			}

			//Add Users
			else if (choice == 2)
			{
				admin.AddUser(users, 1000);
			}

			//Edit Users
			else if (choice == 3)
			{
				string userName;
				cin >> userName;

				admin.EditUsersPassword(users, userName);
			}

			//Delete Users
			else if (choice == 4)
			{
				string userName;
				cin >> userName;

				admin.DeleteUser(users, userName);
			}

			//Suspend Users
			else if (choice == 5)
			{
				string userName;
				cin >> userName;

				admin.SuspendUser(users, userName);
			}

			//Activate Users
			else if (choice == 6)
			{
				string userName;
				cin >> userName;

				admin.ReactivateUser(users, userName);
			}

			//view sys history
			else if (choice == 7)
			{
				admin.ViewUniTransaction(systemHistory);
			}

			//Edit Users balance
			else if (choice == 8)
			{
				admin.adjustBalance(users);
			}

			//logout
			else if (choice == 9)
			{
				activeUser = "";
				inAdmin = false;
				inWelcome = true;
			}
			
			//Eixt
			else if (choice == 8)
			{
				inAdmin = false;
				runProgram = false;
			}

			//word as input
			else if (choice == -1)
			{
				cout << "invalid input!\nYou can not use words here!\n\n";
			}

			//else.
			else
			{
				cout << "Invalide choice!\n\n";
			}
		}
	}

	saveUsers(users, fileName);
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

	int numUsers;
	data >> numUsers;
	data.ignore();

	string userKey;
	string userPass;
	string userSatuts;
	double userBalance;

	stack<Transaction> temp;

	for (int userIndex = 0; userIndex < numUsers; userIndex++)
	{
		//user name and main data
		getline(data, userKey, '|');
		users[userKey].setUserName(userKey);

		getline(data, userPass, '|');
		users[userKey].setPassword(userPass);

		getline(data, userSatuts);
		if (userSatuts == "Active")
			users[userKey].setStatus(Status::Active);
		else
			users[userKey].setStatus(Status::Suspend);


		data >> userBalance;
		data.ignore();

		users[userKey].setBalance(userBalance);

		//user history
		int historySize;
		data >> historySize;
		data.ignore();

		string sender, reciver, date;
		double amount;

		for (int stackIndex = 0; stackIndex < historySize; stackIndex++)
		{
			getline(data, sender, '|');
			getline(data, reciver, '|');
			getline(data, date);
			data >> amount;
			data.ignore();

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
			getline(data, date);
			data >> amount;
			data.ignore();

			users[userKey].addTransactionToQueue(Transaction(sender, reciver, date, amount));
		}

		for (int stackIndex = 0; stackIndex < temp.size(); stackIndex++)
		{
			users[userKey].addTransactionToStack(temp.top());
			temp.pop();
		}
		data.ignore();
	}

	data.close();

	cout << "Data has been loaded successfully";
}

void saveUsers(unordered_map<string, User>& users, string fileName)
{
	ofstream data;

	data.open(fileName);

	if (data.fail())
	{
		cout << "Error opening file!!!!" << endl;
		exit(1);
	}

	unordered_map<string, User>::iterator it;


	data << users.size() << endl;

	for (it = users.begin(); it != users.end(); it++)
	{
		data << it->second.getUserName() << '|' <<
			it->second.getPassword() << '|';

		if (it->second.getStatus() == Status::Active)
			data << "Active\n";
		else
			data << "Suspend\n";

		data << it->second.getBalance() << '\n';

		long long historySize = it->second.getTransaction().size();
		data << historySize << '\n';
		for (int i = 0; i < historySize; i++)
		{
			data << it->second.getTransaction().top().Get_Sender() << '|' <<
				it->second.getTransaction().top().Get_Reciver() << "|" <<
				it->second.getTransaction().top().Get_date() << "\n" <<
				it->second.getTransaction().top().Get_Amount() << "\n";
		}

		long long  queueSize = it->second.getQueue().size();
		data << queueSize << '\n';
		for (int i = 0; i < queueSize; i++)
		{
			data << it->second.getQueue().front().Get_Sender() << '|' <<
				it->second.getQueue().front().Get_Reciver() << "|" <<
				it->second.getQueue().front().Get_date() << "\n" <<
				it->second.getQueue().front().Get_Amount() << "\n";
		}
		data << '\n';
	}

	data.close();

}

int getInt()
{
	string input;
	int number = 0;
	getline(cin, input, '\n');

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
