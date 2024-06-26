#include "User.h"
#include "Transaction.h"
#include "Admin.h"

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
User::User(string name, string pass, double bal, string mail)
{
	userName = name;
	password = pass;
	gmail = mail;
	balance = bal;
	status = Status::Active;
}

//view Balance
void User::viewBalance()
{
	cout << "Enter your password: ";
	string pass = User::inputPassword();

	pass = passwordHashing(pass);

	if (pass == this->getPassword())
		cout << "Your current balance is: " << this->getBalance() << "\n\n";

	else
		cout << "Wrong password!\n\n";
}

//Login and register
void User::userRegister(unordered_map<string, User>& users)
{
	string reggmail;//register 
	string Username;
	string Password;

	bool has_upper = false;
	bool has_number = false;

	cout << "Hi! Let`s get started: ";

	//user name check
	while (true)
	{
		cout << "Please enter user name\n\n";
		getline(cin, Username);

		if (users.find(Username) != users.end())
		{
			cout << "Sorry this user name is already exist!\n\n";
			continue;
		}
		else if (Username.length() < 4 || Username.length() > 15)
		{
			cout << "Error, user name should between 4 and 15 characters.\n";
			continue;
		}
		bool has_alpha = false;
		for (char name : Username)
		{
			if (isalpha(name))
			{
				has_alpha = true;
				break;
			}
		}
		if (!has_alpha)
		{
			cout << "User name must have at least one character";
			continue;
		}
		else
		{
			break;
		}
	}

	bool doneCheck = false;
	//password check
	while (!doneCheck)
	{
		cout << "Enter password: ";
		Password = User::inputPassword();
		doneCheck = checkPassword(Password);
	}
	
	//password hashing
	Password = passwordHashing(Password);

	//gmail check
	while (true)
	{
		cout << "Enter your gmail please " << endl;
		cin >> reggmail;
		cin.ignore();
		if (reggmail.find("@gmail.com") == string::npos) //npos is number that return if value isnt found
		{
			cout << "Please enter a @gmail.com right " << endl;
			continue;
		}
		else
		{
			break;
		}
	}

	cout << "\nYour Account is created. \n\n";
	users[Username] = User(Username, Password, 1000, reggmail);

	//users[Username] = User(Username, Password, 1000);

}

string User::login(unordered_map<string, User>& users, Admin admin)
{
	string userName;
	string pass;
	int count = 0;

	cout << "Enter user name: ";
	getline(cin, userName);

	if (userName == "Admin")
	{
		cout << "Enter password: ";
		pass = User::inputPassword();
		if (admin.login(userName, pass) == true)
		{
			return userName;
		}
	}

	if (users.find(userName) == users.end())
	{
		cout << "Can not login!\nReason: User not found.\n\n";
		return "";
	}

	while (true)
	{
		cout << "Enter password: ";
		pass = User::inputPassword();

		if (count >= 2)
		{
			int choice = 0;
			cout << "\nif you want to exit enter 1 or enter 2 to change your password" << endl;
			choice = getIntger();
			if (choice == 1)
			{
				return "";
			}
			else if (choice == 2)
			{
				string enteredCode, password, confirmPassword;
				string mail = users[userName].getGmail();
				string randomCode = User::gen_random();//get the random code from the function
				fstream file;

				file.open("ForgetPassword.ps1", ios::in | ios::out);

				if (file.fail())
				{
					cout << "Error in opening file";
					return "";
				}

				string line;
				string content = "";
				int lineNumber = 1;

				while (getline(file, line))//line will go through the file
				{
					if (lineNumber == 4)
					{
						line += mail + "\"";

					}

					if (lineNumber == 6)
					{
						line += randomCode + "\"";
					}
					content += line + "\n";

					lineNumber++;
				}

				file.clear();
				file.seekp(0, ios::beg);
				file << content;
				file.close();

				system("powershell -ExecutionPolicy Bypass -File ForgetPassword.ps1");

				string newContent = "";
				string::size_type pos;
				lineNumber = 1;

				file.open("ForgetPassword.ps1", ios::in);

				while (getline(file, line))// it will remove the mail and the random code after execute the powershell code
				{
					if (lineNumber == 4)
					{
						pos = line.find(mail + "\"");
						if (pos != string::npos)
						{
							line.erase(pos, mail.size() + 1);//erase mail plus "
						}
					}
					if (lineNumber == 6) 
					{
						pos = line.find(randomCode + "\"");
						if (pos != string::npos) {
							line.erase(pos, randomCode.size() + 1);
						}
					}
					newContent += line + "\n";//so it wont delete if nothing entered

					lineNumber++;
				}
				file.close();
				file.open("ForgetPassword.ps1", ios::out);
				file << newContent;// the modified clean powershell code
				file.close();
				cout << "enter the 6-digit code or enter \"1\" to exit\n";
				cin >> enteredCode;
				cin.ignore();

				while (true) 
				{
					if (enteredCode == randomCode)
					{
						cout << "\nenter password\n";
						password = User::inputPassword();

						if (!User::checkPassword(password))
						{
							continue;
						}

						cout << "\nenter password again\n";

						confirmPassword = User::inputPassword();

						if (password == confirmPassword)
						{
							users[userName].password = passwordHashing(password);
							break;
						}
						else
						{
							cout << "\npasswords do not match\n";
						}
					}
					else if (enteredCode == "1")
					{
						break;
					}
					else
					{
						cout << "code does'nt match\n\nplease enter the 6-digit code again\n";
						cin >> enteredCode;
					}
				}
				return "";
			}
			return "";
		}
		
		pass = passwordHashing(pass);

		if (users[userName].getPassword() != pass)
		{
			cout << "\nCan not login!\nReason: Wrong password.\n\n";
			count++;
		}

		if (users[userName].getPassword() == pass)
		{
			break;
		}
	}

	cout << "\nLogged in successfully\n\n";
	return userName;
}

//make transaction
void User::makeTransaction(unordered_map<string, User>& users, stack<Transaction>& sysHistory)
{
	//check suspended accounts

	if (status == Status::Suspend)
	{
		cout << "Can not make transaction!\nReason: Account is suspended\n\n";
		return;
	}

	string receiver;
	cout << "Enter the name of the user you want to make transactoin to: ";
	getline(cin, receiver);

	if (receiver == userName)
	{
		cout << "Can not make transaction!\nReason: Sender is the same as receiver\n\n";
		return;
	}

	if (isBlocked(receiver))
	{
		cout << "Can not make transaction!\nReason: You blocked this your.\n\n";
		return;
	}

	//find the user that you want to send to

	if (users.find(receiver) == users.end())
	{
		cout << "Can not make transaction!\nReason: User not found\n\n";
		return;
	}

	
	cout << "Enter your password: ";
	string passCheck = User::inputPassword();
	passCheck = passwordHashing(passCheck);

	if (password != passCheck)
	{
		cout << "Can not make transaction!\nReason: wrong password\n\n";
		return;
	}


	int amount;
	cout << "Enter the amount of money you want to transfer: ";
	cin >> amount;
	cin.ignore();

	//check amount
	if (balance < amount)
	{
		cout << "Can not make transaction!\nReason: do not have enough money\n\n";
		return;
	}

	//make transaction
	users[receiver].addToBalance(amount);
	balance -= amount;

	cout << "successfull Transaction!\n\n";

	addToHistory(users, sysHistory, receiver, amount);

	return;
}

//transactions history
void User::addToHistory(unordered_map<string, User>& users,stack<Transaction>& sysHistory, string receiver, double amount)
{
	Transaction t = Transaction(userName, receiver, amount);
	historyOfTransaction.push(t);

	sysHistory.push(t);

	users[receiver].getTransaction().push(t);

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
		cout << "\t";
		cout << "on " << temproryStack.top().Get_date();
		cout << "\n";
		cout << "*********************************************";
		cout << "\n";
		temproryStack.pop();
	}
}

//requests
void User::requestTransaction(unordered_map<string, User>& users)
{
	if (status == Status::Suspend)
	{
		cout << "Can not make transaction!\nReason: Account is suspended\n\n";
		return;
	}
	string requestReceiver;
	cout << "Enter the name of the user you want to request transaction from : ";
	getline(cin, requestReceiver);

	if (users.find(requestReceiver) == users.end())
	{
		cout << "Can not make transaction!\nReason: Sender not found\n\n";
		return;
	}

	if (users[requestReceiver].isBlocked(this->userName))
	{
		cout << "Can not make transaction!\nReason: You are blocked.\n\n";
		return;
	}

	if (users[requestReceiver].getUserName() == this->userName)
	{
		cout << "Can not request money.\nReason: sender is the same as recever.\n";
		return;
	}

	if (users[requestReceiver].getStatus() == Suspend)
	{
		cout << "Can not make transaction!\nReason: Sender is suspended\n\n";
		return;
	}
	cout << "Enter the amount of money you want to request: ";
	double amount;
	cin >> amount;
	cin.ignore();
	addRequest(users, requestReceiver, amount);
}
void User::addRequest(unordered_map<string, User>& users, string requestReceiver, double amount)
{
	Transaction t(requestReceiver, userName, amount);
	users[requestReceiver].transactionVector.push_back(t);
}

void User::viewRequest(unordered_map<string, User>& users, stack<Transaction>& sysHistory)
{
	if (transactionVector.empty())
	{
		cout << "You have no requests.\n\n";
		return;
	}

	/*Transaction t = transactionVector.front();
	cout << "The user number " << t.Get_Reciver() << " Requests from you " << t.Get_Amount() << " dollars" << endl;*/
	int size = transactionVector.size();
	cout << "Here are the requests" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ": " << "The user number " << transactionVector[i].Get_Reciver() << " Requests from you " << transactionVector[i].Get_Amount() << " dollars" << endl;
	}

	string choice;
	int answer;
	int count = 0;
	vector<Transaction>::iterator it;
	do
	{
		cout << "Enter the requset number to you want to take action(Enter 0 or smaller number to exit)\n";
		answer = getIntger();
		if (answer <= 0)
		{
			return;
		}
		if (answer > size)
		{
			cout << "invalid number" << endl;
			count++;
			if (count > 2)
			{
				cout << "you reached the maximum number of attempts" << endl;
				break;
			}
			continue;
		}
		for (int i = 0; i < size; i++)
		{
			if (i + 1 == answer)
			{
				if (transactionVector[i].Get_Amount() > balance)
				{
					cout << "Your balance is " << balance << " and you need to send " << transactionVector[i].Get_Amount()
						<< ".\nAdd money then make the transaction.\n\n";
					return;
				}
				balance -= transactionVector[i].Get_Amount();
				users[transactionVector[i].Get_Reciver()].addToBalance(transactionVector[i].Get_Amount());
				addToHistory(users, sysHistory, transactionVector[i].Get_Reciver(), transactionVector[i].Get_Amount());
				it = transactionVector.begin() + i;
				transactionVector.erase(it);
			}
		}
		cout << "enter yes to make another transaction no otherwise" << endl;
		do
		{
			cin >> choice;
			cin.ignore();
		} while (choice != "yes" && choice != "no");
		count = 0;

	} while (choice != "no");
}
//edit password
void User::editPassword()
{
	string oldPassword, newPassword;

	cout << "Enter your old password: \n";

	oldPassword = User::inputPassword();
	oldPassword = passwordHashing(oldPassword);
	int i = 2;

	while (oldPassword != password && i > 0) {

		cout << "Old password is incorrect.\nEnter password again : " << endl;
		oldPassword = User::inputPassword();
		oldPassword = passwordHashing(oldPassword);
		i--;
	}

	if (i == 0 && oldPassword != password)
	{
		cout << "You have been reached maxium attempets." << endl;

		return;
	}
	cout << "Enter new password";	
	newPassword = inputPassword();

	if (checkPassword(newPassword))
	{
		password = passwordHashing(newPassword);
		cout << "Password updated successfully!" << endl;
		return;
	}
}

//getters and setters
string User::getUserName()
{
	return User::userName;
}
void User::setUserName(string s)
{
	userName = s;
}

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
	balance += amount;
}
void User::setBalance(double b)
{
	this->balance = b;
}

Status User::getStatus()
{
	return status;
}
void User::setStatus(Status s)
{
	status = s;
}

stack<Transaction>& User::getTransaction()
{
	return historyOfTransaction;
}

void User::addTransactionToStack(Transaction t)
{
	historyOfTransaction.push(t);
}
void User::addTransactionToVector(Transaction t)
{
	User::transactionVector.push_back(t);
}

vector<Transaction>& User::getVector()
{
	return transactionVector;
}

// Password Hashing
string User::inputPassword(void)
{
	char inputPassword[20];
	char c;
	int i = 0;
	while (true)
	{
		c = _getch();
		if (c == '\r')
		{
			break;
		}
		if (c != '\b')
		{
			inputPassword[i] = c;
			cout << '*';
			i++;
		}
		else
		{
			i--;
			if (i < 0)
			{
				i++;
			}
			else
			{
				cout << "\b \b";
			}
		}
	}
	inputPassword[i] = '\0';
	cout << endl;
	string pass = inputPassword;
	return pass;
}
string User::passwordHashing(string pass)
{
	hash<string>hashing;
	long long x = hashing(pass);
	return to_string(x);
}
bool User::checkPassword(string pass)
{
	bool has_upper = false;
	bool has_number = false;

	if (pass.length() < 8 || pass.length() > 14)
	{
		cout << "Error!\nPlease make sure your password length at least 8 and at most 14 letters.\n\n";
		return false;
	}
	for (char PassC : pass)
	{
		if (isupper(PassC))
		{
			has_upper = true;
			break;
		}
	}
	for (char PassC : pass)
	{
		if (isdigit(PassC))
		{
			has_number = true;
			break;
		}
	}
	if (has_upper != true)
	{
		cout << "Error!\nPlease make sure that you have atleast one uppercase letter.\n\n";
		return false;
	}
	if (has_number != true)
	{
		cout << "Error!\nPlease make sure that you have atleast one number\n\n";
		return false;
	}

	return true;
}

string User::gen_random()
{
	string alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string random;
	srand(time(0));

	for (int i = 0; i < 6; ++i)
	{
		random += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return random;
}
string User::getGmail()
{
	return User::gmail;
}

void User::blockUser(unordered_map<string, User>& users)
{
	string userName;

	cout << "Enter username to block: ";
	getline(cin, userName);
	if (users.find(userName) == users.end())
	{
		cout << "User " << userName << " does not exist in the Wallet system.\n\n";
		return;
	}
	set<string>::iterator it = blockedUsers.find(userName);
	if (it == blockedUsers.end())
	{
		blockedUsers.insert(userName);
		cout << "User " << userName << " has been blocked successfully.\n\n";
	}
	else
	{
		cout << "User " << userName << " is already blocked.\n\n";
	}
}
void User::unBlockUser(unordered_map<string, User>& users)
{
	string userName;

	cout << "Enter username to unblock: ";
	getline(cin, userName);
	if (users.find(userName) == users.end())
	{
		cout << "User " << userName << " does not exist in the Wallet system.\n\n";
		return;
	}

	set<string>::iterator it = blockedUsers.find(userName);
	if (it != blockedUsers.end())
	{
		blockedUsers.erase(it);
		cout << "User " << userName << " has been unblocked successfully.\n\n";
	}
	else
	{
		cout << "User " << userName << " is not blocked.\n\n";
	}
}
bool User::isBlocked(string& findBlockedUser)
{
	return (blockedUsers.find(findBlockedUser) != blockedUsers.end());
}

int User::getIntger()
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

set<string>& User::getBlockedSet()
{
	return blockedUsers;
}

//dest.
User::~User()
{

}