#pragma once
#include "transactions.h"
#include "Request.h"
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

class user
{

public:
	string username;
	string Firstname;
	string Lastname;
	string password;
	double balance;
	string phonenumber;
	bool isDeleted;
	bool isSuspended;
	stack<transactions>transactionstack;
	queue<Request>RequestsQueue;
	user();
	user(string username1,string Firstname1, string Lastname1,string password1, string phonenumber1,bool isDeleted1,bool isSuspended1);
	string getCurrentDateTime();
	double getbalance();
	string getpassword();
	void ViewBalance();
	void Deposite();
	void SendMoney();
	void Requestapproval();
	void RequestMoney();
	void TransactionsHistory();
	void EditProfile();
	void Usermenu();

};

