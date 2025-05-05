#include "transactions.h"
#include <string>
using namespace std;

transactions::transactions(string senderFirstName, string recieverFirstName, double amount1, string DateAndTime1, string type1)
{
	sender = senderFirstName;
	reciever = recieverFirstName;
	amount = amount1;
	DateAndTime = DateAndTime1;
	type = type1;
}

transactions::transactions(string recieverFirstName, double amount1, string DateAndTime1, string type1)
{
	reciever = recieverFirstName;
	amount = amount1;
	DateAndTime = DateAndTime1;
	type = type1;
}



