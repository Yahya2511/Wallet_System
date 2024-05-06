#include "Transaction.h"

Transaction::Transaction()
{

}

Transaction::Transaction(string s,string r,double amt)
{
	sender = s;
	reciever = r;
	amount = amt;

	time_t curr_time;
	curr_time = time(NULL);
	char tm[26]; // Buffer to hold the time string
	ctime_s(tm, sizeof tm, &curr_time);
	date = tm;
}

Transaction::Transaction(string s, string r, string d, double amt)
{
	sender = s;
	reciever = r;
	amount = amt;
	date = d;
}

string Transaction::Get_Sender()
{
	return sender;
}

string Transaction::Get_Reciver()
{
	return reciever;
}

double Transaction::Get_Amount()
{
	return amount;
}
Transaction::~Transaction()
{

}

string Transaction::Get_date()
{
	return date;
}
