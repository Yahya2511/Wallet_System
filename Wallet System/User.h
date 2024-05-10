#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <queue>
#include <conio.h>
#include <string>
#include "Transaction.h"

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
	queue <Transaction> transactionQueue;

	//methodes
public:
	User();
	User(string, string, double);

	void static userRegister(unordered_map<string, User>&);
	string static login(unordered_map<string, User>& users, class Admin admin);

	//make a transactoin
	void makeTransaction(unordered_map<string, User>& users, stack<Transaction>& sysHistory);

	//transactions history
	void addToHistory(unordered_map<string, User>& users, stack<Transaction>& sysHistory, string userName, double balance);
	void viewHistory();

	//requests
	void requestTransaction(unordered_map<string, User>& users);
	void addRequest(unordered_map<string, User>& users, string request_reciever, double amount);
	void viewRequest(unordered_map<string, User>& users, stack<Transaction>& sysHistory);

	//edit password
	void editPassword();
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

	//password hashing
	string static inputPassword(void);
	void static passwordHashingForRegister(unordered_map<string, User>& users, string userName, string pass);
	string passwordHashing(string pass);
	bool static checkPassword(unordered_map<string, User>& users, string userName);

	//dest.
	~User();
};
