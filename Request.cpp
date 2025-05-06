#include "Request.h"

Request::Request()
{
}

Request::Request(string FirstName1, string LastName1, string phonenumber1, double amount1, string DateAndTime1)
{
	FirstName = FirstName1;
	LastName = LastName1;
	amount = amount1;
	DateAndTime = DateAndTime1;
	phonenumber = phonenumber1;

}
