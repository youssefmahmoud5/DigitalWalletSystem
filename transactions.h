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
	transactions();
	transactions(string type1, string senderFirstName, string recieverFirstName, double amount1, string DateAndTime1);
	transactions(string type1,string recieverFirstName, double amount1, string DateAndTime1);
};


