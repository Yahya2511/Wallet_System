#include "User.h"
#include <string>

User::User(string name, string pass, double bal)
{
	userName = name;
	password = pass;
	balance = bal;
	status = Status::Active;
}

bool User::makeTransaction(vector<User> &users,string userName, double amount)
{
	//check suspended accounts
	if (status == Status::Suspend)
	{
		cout << "Can not make transaction!\nReason: Account is suspended\n\n";
		return false;
	}

	//enter password
	string passCheck;
	
	cout << "Enter Password: ";
	cin >> passCheck;
	
	if (password != passCheck)
	{
		cout << "Can not make transaction!\nReason: wrong password\n\n";
		return false;
	}

	//find the user that you want to send to
	int userPostion = -1;
	for (int userIndex = 0; userIndex < users.size(); userIndex++)
	{
		if (userName == users[userIndex].getUserName())
		{
			userPostion = userIndex;
			break;
		}
	}
	if (userPostion == -1)
	{
		cout << "Can not make transaction!\nReason: User not found\n\n";
		return false;
	}

	//check amount
	if (balance < amount)
	{
		cout << "Can not make transaction!\nReason: do not have enough money\n\n";
		return false;
	}

	//make transaction
	users[userPostion].setBalance(users[userPostion].getBalance() + amount);
	balance -= amount;

	cout << "successfull Transaction!\n\n";
	return true;
}

string User::getUserName() 
{
	return User::userName;
}
/*
 need some coditions first
void User::setUserName(string s)
{
	User::userName = s;
}
*/

string User::getPassword()
{
	return User::password;
}
void User::setPassword(string s)
{
	User::password = s;
}

double User::getBalance() 
{
	return balance;
}
void User::addToBalance(double amount)
{
	cout << User::userName << " balance before: " << balance << endl;
	balance += amount;
	cout << User::userName << " balance after: " << balance << endl;
} 
void User::setBalance(double b)
{
	cout << User::userName << " balance before: " << balance << endl;
	balance = b;
	cout << User::userName << " balance after: " << balance << endl;
}

User::~User()
{

}