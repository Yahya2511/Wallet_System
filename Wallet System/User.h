#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <conio.h>
#include <string>
#include <ctime> 
#include <cstdlib>
#include <fstream>
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
	string gmail;
	double balance = 0;
	Status status;

	stack <Transaction> historyOfTransaction;
	vector <Transaction> transactionVector;

	//methodes
public:
	User();
	User(string, string, double);
	User(string, string, double, string);

	void viewBalance();

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
	void addTransactionToVector(Transaction t);

	vector<Transaction>& getVector();

	//password hashing
	string static inputPassword(void);
	string static passwordHashing(string pass);
	bool static checkPassword(string);

	//for forget password
	static string gen_random();
	string getGmail();

	int static getIntger();

	//dest.
	~User();
};
