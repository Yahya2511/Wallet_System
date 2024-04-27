#include "User.h"
#include <string>
#include "Transaction.h"

//const.
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

//Login and register
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
string User::login(map<string, User>& users)
{
	string userName;
	cout << "Enter user name: ";
	cin >> userName;

	string pass;
	cout << "Enter password: ";
	cin >> pass;

	if (users.find(userName) == users.end())
	{
		cout << "Can not login!\nReason: User not found.\n\n";
		return "";
	}

	if (users[userName].getPassword() != password)
	{
		cout << "Can not login!\nReason: Wrong password.\n\n";
		return "";
	}

	cout << "Logged in successfully\n\n";
	return userName;
}

//make transaction
bool User::makeTransaction(map<string, User>& users)
{
	//check suspended accounts

	if (status == Status::Suspend)
	{
		cout << "Can not make transaction!\nReason: Account is suspended\n\n";
		return false;
	}

	string receiver;
	cout << "Enter the name of the user you want to make transactoin to: ";
	cin >> receiver;
	

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

	if (users.find(receiver) == users.end())
	{
		cout << "Can not make transaction!\nReason: User not found\n\n";
		return false;
	}

	int amount;
	cout << "Enter the amount of money you want to transfer.";
	cin >> amount;
	//check amount
	if (balance < amount)
	{
		cout << "Can not make transaction!\nReason: do not have enough money\n\n";
		return false;
	}

	//make transaction
	users[receiver].addToBalance(amount);
	balance -= amount;

	cout << "successfull Transaction!\n\n";

	addToHistory(users, receiver, amount);

	return true;
}

//transactions history
void User::addToHistory(map<string, User>& users, string receiver, double amount)
{
	Transaction t = Transaction(userName, receiver, amount);
	historyOfTransaction.push(t);
	users[receiver].GetTransaction().push(t);
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

//requests
bool User::requestTransaction(map<string, User>& users, string requestReceiver, double amount)
{
	if (status == Status::Suspend)
	{
		cout << "Can not make transaction!\nReason: Account is suspended\n\n";
		return false;
	}
	if (users.find(requestReceiver) == users.end())
	{
		cout << "Can not make transaction!\nReason: Sender not found\n\n";
		return false;
	}
	if (users[requestReceiver].getStatus() == Suspend)
	{
		cout << "Can not make transaction!\nReason: Sender is suspended\n\n";
		return false;
	}
	addRequest(users, requestReceiver, amount);

}
void User::addRequest(map<string, User>& users, string requestReceiver, double amount)
{
	Transaction t(requestReceiver, userName, amount);
	users[requestReceiver].transactionQueue.push(t);
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

//edit password
int User::EditPassword() {

	string oldPassword, newPassword;

	cout << "Enter your old password: \n"; cin >> oldPassword;

	int i = 2;


	while (oldPassword != password && i > 0) {

		cout << "Old password is incorrect.\nEnter password again : " << endl;

		cin >> oldPassword;

		i--;

	}

	if (i == 0 && oldPassword != password)

	{

		cout << "You have been reached maxium attempets." << endl;

		return 0;
	}

	cout << "Enter a new password (at least 8 characters long): ";


	do {


		cin >> newPassword;

		if (newPassword.length() < 8)

			cout << "Password must be at least 8 characters long try again." << endl;



	} while (newPassword.length() < 8);


	password = newPassword;

	cout << "Password updated successfully!" << endl;

}
void User::displayUserInfo() 
{
	cout << "Username: " << User::userName << '\n' << "Password:" << User::password << endl;
}

//getters and setters
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

//dest.
User::~User()
{

}