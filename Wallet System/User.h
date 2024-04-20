#pragma once
#include <iostream>
#include "Transaction.h"
#include <vector>
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
	
	Status status;

	//methodes
public:
	User(string, string, double);

	bool makeTransaction(vector<User> &users,string userName, double balance);

	~User();

	string getUserName();
	//void setUserName(string s);

	string getPassword();
	void setPassword(string s);

	double getBalance();
	void addToBalance(double amount);
	void setBalance(double d);

};