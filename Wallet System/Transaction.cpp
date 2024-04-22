#include "Transaction.h"

Transaction::Transaction()
{

}

Transaction::Transaction(string s,string r,double amt)
{
	sender = s;
	reciever = r;
	amount = amt;
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