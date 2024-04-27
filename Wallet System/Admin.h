#pragma once
#include<iostream>
#include<vector>
using namespace std;
#include <string>
#include "User.h"
class Admin
{
private:
	string adminName;
	int adminId;
	map<string, User> users;
	Status status;
public:
	Admin();
	void AddUser(double);
	void EditusersPassword(string& userName, string& currentpassword, string& newPassword);
	void DeleteUser(string& userName);
	void SuspendUser(string& userName);
	void ReactivateUser(string& userName);
};

