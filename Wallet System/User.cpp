#include "User.h"
#include <string>
#include "Transaction.h"

User::User()
{
	userName = "0";
	password = "0";
	balance = 0;
	status = Status::Active;
}

User::User(string name, string pass, double bal)
{
	userName = name;
	password = pass;
	balance = bal;
	status = Status::Active;
}

bool User::makeTransaction(map<string, User>& users, string reciever, double amount)
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

	if (users.find(reciever) == users.end())
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
	users[reciever].addToBalance(amount);
	balance -= amount;

	cout << "successfull Transaction!\n\n";

	addToHistory(users, reciever, amount);

	return true;
}

bool User::requestTransaction(map<string, User>& users, string request_reciever, double amount)
{
	if (status == Status::Suspend)
	{
		cout << "Can not make transaction!\nReason: Account is suspended\n\n";
		return false;
	}
	if (users.find(request_reciever) == users.end())
	{
		cout << "Can not make transaction!\nReason: Sender not found\n\n";
		return false;
	}
	if (users[request_reciever].getStatus() == Suspend)
	{
		cout << "Can not make transaction!\nReason: Sender is suspended\n\n";
		return false;
	}
	addRequest(users, request_reciever, amount);

}

void User::addRequest(map<string, User>& users, string request_reciever, double amount)
{
	Transaction t(request_reciever, userName, amount);
	users[request_reciever].transactionQueue.push(t);
}

void User::viewRequets(map<string, User>& users)
{
	Transaction t = transactionQueue.front();
	cout << "The user number " << t.Get_Reciver() << " Requests from you " << t.Get_Amount() << " dollars" << endl;

	string ans;
	do
	{
		cout << "Enter yes to agree on the transaction no otherwise(yes / no)\n";
		cin >> ans;
	} while (ans != "yes" && ans != "no");
	if (ans == "yes")
	{
		if (balance < t.Get_Amount())
		{
			cout << "Your balance is not enough please charge and try again\n";
			return;
		}
		balance -= t.Get_Amount();
		users[t.Get_Reciver()].addToBalance(t.Get_Amount());
		addToHistory(users, t.Get_Reciver(), t.Get_Amount());
		transactionQueue.pop();
	}
	else if (ans == "no")
	{
		transactionQueue.pop();
	}

}


void User::addToHistory(map<string, User>& users, string reciever, double amount)
{
	Transaction t = Transaction(userName, reciever, amount);
	historyOfTransaction.push(t);
	users[reciever].GetTransaction().push(t);
}

stack<Transaction>& User::GetTransaction()
{
	return historyOfTransaction;
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

Status User::getStatus()
{
	return status;
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

void User::viewHistory()
{
	cout << "HERE IS THE TRANSACTIONS : \n";
	if (historyOfTransaction.empty())
	{
		cout << "There is No history\n";
		return;
	}
	stack <Transaction>temproryStack;
	temproryStack = historyOfTransaction;
	while (!temproryStack.empty())
	{
		cout << "The sender is " << temproryStack.top().Get_Sender();
		cout << "\t";
		cout << "The amount is " << temproryStack.top().Get_Amount();
		cout << "\t";
		cout << "The reciever is " << temproryStack.top().Get_Reciver();
		cout << "\n";
		cout << "*********************************************";
		cout << "\n";
		temproryStack.pop();
	}
}