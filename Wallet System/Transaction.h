#pragma once
#include <iostream>

using namespace std;

class Transaction
{
	//variables
	
	//date
	string sender;
	string reciever;
	double amount;
	string date;


	//methodes
public:
	
	Transaction();
	Transaction(string, string, double);
	string Get_Sender();
	string Get_Reciver();
	double Get_Amount();
	string Get_date();
	~Transaction();

};

