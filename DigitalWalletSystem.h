#pragma once
#include <unordered_map>
#include "user.h"
#include "admin.h"

using namespace std;
class DigitalWalletSystem
{
	
public:
	static unordered_map<string, user> mapOfUsers;
	static stack<transactions>SystemTransactions;
	static void SignUp();
	static void login();
	static void AdminLogin();
	static string hashing(string password1);
	static string checkPassword();
	static string checkPhoneNUmber();
};

