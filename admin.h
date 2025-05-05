#pragma once
#include <string>
using namespace std;
class admin
{
public:
	static const string username;
	static const string password;
	admin();
	void AdminMenu();
	void viewUsers();
	void editAccounts();
	void viewTransactions();

};

