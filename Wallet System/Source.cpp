#include <iostream>
#include "User.h"
#include "Transaction.h"
#include <vector>
#include "ctime"
#include <map>

using namespace std;

int main()
{
	time_t curr_time;
	curr_time = time(NULL);

	char tm[26]; // Buffer to hold the time string
	ctime_s(tm, sizeof tm, &curr_time);
	std::cout << "Today is : " << tm;

	map<string, User> users;

	User u1 = User("user1", "password1", 500);
	User u2 = User("user2", "password2", 1000);
	User u3 = User("user3", "password3", 1500);
	
	users[u1.getUserName()] = u1;
	users[u2.getUserName()] = u2;
	users[u3.getUserName()] = u3;

	map<string, User>::iterator it;
	it = users.begin();
	while(it != users.end())
	{
		cout<<it->first<<endl;
		cout<<it->second.getUserName()<<" " << it->second.getPassword() << " " << it->second.getBalance();
		cout<<endl;
		it++;
	}
	
	users["user1"].makeTransaction(users, "user2", 300.0);
	users["user1"].makeTransaction(users, "user2", 100.0);
	users["user1"].makeTransaction(users, "user2", 350000.0);
	users["user3"].makeTransaction(users, "user1", 350.0);

	while (it != users.end())
	{
		cout << it->first << endl;
		cout << it->second.getUserName() << " " << it->second.getPassword() << " " << it->second.getBalance();
		cout << endl;
		it++;
	}

	users["user1"].viewHistory();
	users["user2"].viewHistory();
	users["user3"].viewHistory();

	return 0;
}