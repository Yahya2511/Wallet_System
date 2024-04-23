#pragma once
#include <iostream>
#include "Transaction.h"
#include <vector>
#include <stack>
#include <map>

using namespace std;

enum Status
{
	Active,
	Suspend
};

class User
{
	//variables
	string userName;
	string password;
	double balance = 0;
	stack <Transaction> historyOfTransaction;
	
	Status status;

	//methodes
public:
	User();
	User(string, string, double);

	void static userRegister(map<string, User>&);

	bool makeTransaction(map<string, User> &users,string userName, double balance);

	~User();

	string getUserName();
	//void setUserName(string s);

	void viewHistory();
	void addToHistory(map<string, User>& users, string userName, double balance);

	stack<Transaction>& GetTransaction();

	string getPassword();
	void setPassword(string s);

	double getBalance();
	void addToBalance(double amount);
	void setBalance(double d);

};