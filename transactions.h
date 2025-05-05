#pragma once
#include <string>
#include <iostream>
using namespace std;
class transactions
{

public:
	string sender;
	string reciever;
	double amount;
	string DateAndTime;
	string type;
	transactions(string senderFirstName, string recieverFirstName, double amount1, string DateAndTime1, string type1);
	transactions(string recieverFirstName, double amount1, string DateAndTime1, string type1);
};


