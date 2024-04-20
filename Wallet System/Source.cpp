#include <iostream>
#include "User.h"
#include "Transaction.h"
#include <vector>

using namespace std;

int main()
{
	vector<User> users;

	User u1 = User("user1", "password1", 500);
	User u2 = User("user2", "password2", 1000);
	User u3 = User("user3", "password3", 1500);
	
	users.push_back(u1);
	users.push_back(u2);
	users.push_back(u3);

	users[0].makeTransaction(users, "user2", 300.0);

	users[2].setBalance(1.0);

	for (int i = 0; i < users.size(); i++)
	{
		cout << users[i].getUserName() << ": " << users[i].getBalance() << endl;
	}

	return 0;
}