#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "User.h"
#include "Transaction.h"
#include "ctime"

using namespace std;

void loadUsers(map<string, User>& users, string fileName);

void saveUsers(map<string, User>& users, string fileName);
int getInt();

	/*
	time_t curr_time;
	curr_time = time(NULL);
	
	char tm[26]; // Buffer to hold the time string
	ctime_s(tm, sizeof tm, &curr_time);
	std::cout << "Today is : " << tm;
	*/

int main()
{
	string fileName = "usersData.txt";

	string activeUser = "";

	bool runProgram = true;
	bool inWelcome = true;
	bool inHome = false;
	bool inAdmin= false;

	map<string, User> users;
	map<string, User>::iterator it;

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
					activeUser = checkUserName;
					inWelcome = false;
					inHome = true;
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
				"3. Make a Request.\n" << 
				"4. Edit Password.\n" << 
				"5. Logout.\n" << 
				"6. Exit.\n" <<
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
				users[activeUser].makeTransaction(users);
			}

			//Make a Request.
			else if (choice == 3)
			{
				cout << "Enter user name that you want money form: ";
				string receiver;
				cin >> receiver;
				cin.ignore();
				
				cout << "Enter amount of money you want from him: ";
				double amount;
				cin >> amount;
				cin.ignore();

				users[activeUser].requestTransaction(users, receiver, amount);
			}

			//Eidt Password.
			else if (choice == 4)
			{
				users[activeUser].editPassword();
			}

			//Logout.
			else if (choice == 5)
			{
				activeUser = "";
				inHome = false;
				inWelcome = true;
			}

			//Exit.
			else if (choice == 6)
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
	}

	saveUsers(users, fileName);
	return 0;
}

void loadUsers(map<string, User>& users, string fileName)
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

		int historySize;
		data >> historySize;
		data.ignore();

		string sender, reciver;
		double amount;

		for (int stackIndex = 0; stackIndex < historySize; stackIndex++)
		{
			getline(data, sender, '|');
			getline(data, reciver);
			data >> amount;
			data.ignore();

			temp.push(Transaction(sender, reciver, amount));
		}

		int queueSize;
		data >> queueSize;
		data.ignore();

		for (int queueIndex = 0; queueIndex < queueSize; queueIndex++)
		{
			getline(data, sender, '|');
			getline(data, reciver);
			data >> amount;
			data.ignore();

			users[userKey].addTransactionToQueue(Transaction(sender, reciver, amount));
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

void saveUsers(map<string, User>& users, string fileName)
{
	ofstream data;

	data.open(fileName);

	if (data.fail())
	{
		cout << "Error opening file!!!!" << endl;
		exit(1);
	}
	
	map<string, User>::iterator it;

	
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
				it->second.getTransaction().top().Get_Reciver() << "\n" << 
				it->second.getTransaction().top().Get_Amount() << "\n";
		}

		long long  queueSize = it->second.getQueue().size();
		data << queueSize << '\n';
		for (int i = 0; i < queueSize; i++)
		{
			data << it->second.getQueue().front().Get_Sender() << '|' <<
				it->second.getQueue().front().Get_Reciver() << "\n" <<
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