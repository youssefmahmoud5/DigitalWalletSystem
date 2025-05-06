#include "transactions.h"
#include <string>
using namespace std;

transactions::transactions()
{

}

transactions::transactions(string type1, string senderFirstName, string recieverFirstName, double amount1, string DateAndTime1)
{
	sender = senderFirstName;
	reciever = recieverFirstName;
	amount = amount1;
	DateAndTime = DateAndTime1;
	type = type1;
	
}

transactions::transactions(string type1, string recieverFirstName, double amount1, string DateAndTime1)
{
	reciever = recieverFirstName;
	amount = amount1;
	DateAndTime = DateAndTime1;
	type = type1;
}



