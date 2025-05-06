#pragma once
#include <string>
#include <iostream>
#include "user.h"
#include <ctime>
#include <stack>
#include "DigitalWalletSystem.h"
#include "transactions.h"
#include "Request.h"
#include "admin.h"
using namespace std;
class Files
{
public:
	void loadUsersFromFile(unordered_map<string, user>& users);
	void saveUsersToFile(const unordered_map<string, user>& users);

	void loadSystemTransactionsFromFile();
	void saveSystemTransactionsToFile();

};

