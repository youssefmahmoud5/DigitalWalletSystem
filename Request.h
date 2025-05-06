#pragma once
#include <string>
#include <iostream>
using namespace std;
class Request
{
	
public:
	string username;
	string FirstName;
	string LastName;
	double amount;
	string DateAndTime;
	string phonenumber;
	Request();
	Request( string FirstName1, string LastName1,string phonenumber1, double amount1, string DateAndTime1);

};

