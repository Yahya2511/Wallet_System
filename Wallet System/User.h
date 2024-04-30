#pragma once
#include <iostream>
#include "Transaction.h"
#include <vector>
#include <stack>
#include <map>
#include<queue>

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

	stack <Transaction> historyOfTransaction;
	queue<Transaction> transactionQueue;

	//methodes
public:
	User();
	User(string, string, double);

	void static userRegister(map<string, User>&);
	string static login(map<string, User>& users);

	//make a transactoin
	void makeTransaction(map<string, User>& users);

	//transactions history
	void addToHistory(map<string, User>& users, string userName, double balance);
	void viewHistory();

	//requests
	bool requestTransaction(map<string, User>& users, string sender, double amount);
	void addRequest(map<string, User>& users, string request_reciever, double amount);
	void viewRequets(map<string, User>& users);

	//edit password
	int editPassword();
	void displayUserInfo();

	//getters and setters
	string getUserName();
	void setUserName(string s);

	string getPassword();
	void setPassword(string s);

	double getBalance();
	void addToBalance(double amount);
	void setBalance(double d);

	Status getStatus();
	void setStatus(Status);

	stack<Transaction>& getTransaction();
	void addTransactionToStack(Transaction t);
	void addTransactionToQueue(Transaction t);

	queue<Transaction>& getQueue();

	//dest.
	~User();
};