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

void User::userRegister(map<string, User>& users)
{

	string Username;
	string Password;
	bool has_upper = false;  //to check if the passowrd has atleast one uppercase
	cout << "Hi! Let`s get started \n\n";
	while (true)
	{
		cout << "Please enter user name\n\n";
		cin >> Username;
		if (users.find(Username) != users.end()) {
			cout << "Sorry this user name is already exist!\n\n";
			continue;
		}
		else break;
	}
	while (true)
	{


		cout << "Please enter you`re password \n\n";

		cin >> Password;
		if (Password.length() < 8) {
			cout << "Please make sure you`er password length atleast 8 letters\n\n";
			continue;
		}
		for (char pass : Password) {
			if (isupper(pass)) {
				has_upper = true;
				break;
			}

		}
		if (has_upper == true) {
			cout << "DONE\n\n";
			break;
		}
		if (has_upper != true) {
			cout << "Please make sure that you have atleast one uppercase letter\n\n";
			continue;
		}

	}
	users[Username] = User(Username, Password, 1000);

}

bool User::makeTransaction(map<string, User> &users,string reciever, double amount)
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

	addToHistory(users, reciever,  amount);

	return true;
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