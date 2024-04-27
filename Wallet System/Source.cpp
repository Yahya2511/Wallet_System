#include <iostream>
#include "User.h"
#include "Transaction.h"
#include <vector>
#include "ctime"
#include <map>

using namespace std;

int main()
{
	//time_t curr_time;
	//curr_time = time(NULL);
	//
	//char tm[26]; // Buffer to hold the time string
	//ctime_s(tm, sizeof tm, &curr_time);
	//std::cout << "Today is : " << tm;

	map<string, User> users;
	
	string activeUser = "";

	bool runProgram = true;
	bool inWelcome = true;
	bool inHome = false;


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

			cin >> choice;

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

			cin >> choice;

			//View Balance.
			if (choice == 1)
			{
				cout << "Enter your password: ";
				string pass;
				cin >> pass;

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
				cout << "Enter user name that you want to make transaction to: ";
				string receiver;
				cin >> receiver;
				
				cout << "Enter amount of money you want to send to him: ";
				double amount;
				cin >> amount;

				users[activeUser].requestTransaction(users, receiver, amount);
			}

			//Eidt Password.
			else if (choice == 4)
			{
				users[activeUser].EditPassword();
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

			//else.
			else
			{
				cout << "Invalide choice!\n\n";
			}
		}
	}
	return 0;
}