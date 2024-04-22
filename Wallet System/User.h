#pragma once
#include <iostream>
#include "Transaction.h"
#include <vector>
#include <stack>
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
	User(string, string, double);

	bool makeTransaction(vector<User> &users,string userName, double balance);

	~User();

	string getUserName();
	//void setUserName(string s);

	void viewHistory();
	void addToHistory(vector<User>& users, string userName, double balance, int userPosition);

	stack<Transaction> GetTransaction();

	string getPassword();
	void setPassword(string s);

	double getBalance();
	void addToBalance(double amount);
	void setBalance(double d);

};