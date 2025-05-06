#include "user.h"
#include <ctime>
#include <stack>
#include "DigitalWalletSystem.h"
#include <unordered_map>
#include <iostream>
using namespace std;

user::user() : username(""), password(""), balance(0.0) {}

user::user(string username1, string Firstname1, string Lastname1, string password1, string phonenumber1, bool isDeleted1, bool isSuspended1) {
	username = username1;
	Firstname = Firstname1;
	Lastname = Lastname1;
	password = password1;
	balance = 0.0;
	phonenumber = phonenumber1;
	isDeleted = isDeleted1;
	isSuspended = isSuspended1;
}
double user::getbalance(){
	return balance;
}
string user::getpassword()
{
	return password;
}
void user::ViewBalance() {
	cout << "Your current balance: " << balance << endl;
}
string user::getCurrentDateTime() {
	time_t now = time(0);
	tm localtm;
	localtime_s(&localtm, &now);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localtm);
	return string(buffer);
}
void user::Deposite() {
	cout << "Enter the amount: ";
	double amount;
	cin >> amount;
	balance = balance + amount;
	transactionstack.push(transactions("Deposite",Firstname, amount, getCurrentDateTime()));
	DigitalWalletSystem::SystemTransactions.push(transactions("Deposite",Firstname, amount, getCurrentDateTime()));
}

void user::SendMoney()
{
	double amount;
	bool repeat = false;
	string un;
	do {
		repeat = false;
		cout << "Enter the username you want to send money to: ";
		cin >> un;
		auto it = DigitalWalletSystem::mapOfUsers.find(un);
		if (it == DigitalWalletSystem::mapOfUsers.end()) {
			cout << "User not found. Please Renter the username or return to the mainmenu." << endl;
			cout << "Press E to exit or press any buttom to reenter username";
			char s;
			cin >> s;
			if (s == 'E' || s == 'e') {
				return;
			}
			repeat = true;
		}
	} while (repeat);

	do {
		repeat = false;
		cout << "Enter amount to send: ";
		cin >> amount;
		if (amount <= 0) {
			cout << "Invalid amount." << endl;
			cout << "Press E to exit or press any buttom to reenter the amount";
			char s;
			cin >> s;
			if (s == 'E' || s == 'e') {
				return;
			}
			repeat = true;
			continue;
		}

		if (amount > balance) {
			cout << "Insufficient balance.";
			cout << "Press E to exit or press any buttom to reenter the amount";
			char s;
			cin >> s;
			if (s == 'E' || s == 'e') {
				return;
			}
			repeat = true;
			continue;
		}
	} while (repeat);

	balance -= amount;
	DigitalWalletSystem::mapOfUsers[un].balance += amount;
	transactionstack.push(transactions("Send",Firstname, DigitalWalletSystem::mapOfUsers[un].Firstname, amount, getCurrentDateTime()));
	DigitalWalletSystem::mapOfUsers[un].transactionstack.push(transactions("Recieve",Firstname,
		DigitalWalletSystem::mapOfUsers[un].Firstname, amount, getCurrentDateTime()));
	cout << "Money sent successfully to " << DigitalWalletSystem::mapOfUsers[un].Firstname << " " << DigitalWalletSystem::mapOfUsers[un].Lastname << ".";
	DigitalWalletSystem::SystemTransactions.push(transactions("Send",Firstname, DigitalWalletSystem::mapOfUsers[un].Firstname, amount, getCurrentDateTime()));
}

void user::Requestapproval()
{
	bool repeat = false;
	if (RequestsQueue.empty()) {
		cout << "there are no requests for you." << endl;
		return;
	}
	else {
		int choice;
		int size = RequestsQueue.size();
		for (int i = 0; i < size; i++) {
			Request r = RequestsQueue.front();
			cout << "Request from: " << r.FirstName << " " << r.LastName << endl;
			cout << "Username: " << r.username << " PhoneNumber: " << r.phonenumber << endl;
			cout << "Date and time: " << r.DateAndTime << endl;
			cout << "Requested amount:" << r.amount << endl;
			do {
				repeat = false;
					int response;
					cout << "To accept press 1, to reject press 0, to return press 2" << endl;
					cin >> response;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max());
						cout << "Invalid input. Please enter a valid integer. " << endl;
						repeat = true;
						continue;
					}
					if (response == 1) {
						if (balance >= r.amount) {
							cout << "The request is accepted." << endl;
							DigitalWalletSystem::mapOfUsers[r.username].balance += r.amount;
							RequestsQueue.pop();
							transactionstack.push(transactions("Send",Firstname, DigitalWalletSystem::mapOfUsers[r.username].Firstname, r.amount, getCurrentDateTime()));
							DigitalWalletSystem::mapOfUsers[r.username].transactionstack.push(transactions("Recieve",Firstname,
								DigitalWalletSystem::mapOfUsers[r.username].Firstname, r.amount, getCurrentDateTime()));
							cout << "Money sent successfully to " << DigitalWalletSystem::mapOfUsers[r.username].Firstname << " " << DigitalWalletSystem::mapOfUsers[r.username].Lastname << ".";
							DigitalWalletSystem::SystemTransactions.push(transactions("Send",Firstname, DigitalWalletSystem::mapOfUsers[r.username].Firstname, r.amount, getCurrentDateTime()));
						}
						else {
							cout << "Insufficient balance " << endl;
						}
					}
					else if (response == 0) {
						cout << "The request is rejected!" << endl;
						RequestsQueue.pop();
					}
					do {
						repeat = false;
						cout << "Press 1 to see another request or press 0 to exit: ";
						cin >> choice;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max());
							cout << "Invalid input. Please enter a valid integer. " << endl;
							repeat = true;
							continue;
						}
					} while (repeat);
					if (choice == 1) {
						RequestsQueue.pop();
						RequestsQueue.push(r);
					}
					else {
						return;
					}
			} while (repeat);
		}
	}
}

void user::RequestMoney()
{
	double amount;
	bool repeat = false;
	string un;
	do {
		repeat = false;
		cout << "Enter the username you want to request money from: ";
		cin >> un;
		auto it = DigitalWalletSystem::mapOfUsers.find(un);
		if (it == DigitalWalletSystem::mapOfUsers.end()) {
			cout << "User not found. Please Renter the username or return to the mainmenu." << endl;
			cout << "Press E to exit or press any buttom to reenter username";
			char s;
			cin >> s;
			if (s == 'E' || s == 'e') {
				return;
			}
			repeat = true;
		}
	} while (repeat);
	do {
		repeat = false;
		cout << "Enter amount to send: ";
		cin >> amount;
		if (amount <= 0) {
			cout << "Invalid amount." << endl;
			cout << "Press E to exit or press any buttom to reenter the amount";
			char s;
			cin >> s;
			if (s == 'E' || s == 'e') {
				return;
			}
			repeat = true;
		}
	} while (repeat);
	DigitalWalletSystem::mapOfUsers[un].RequestsQueue.push(
		Request(Firstname, Lastname, phonenumber, amount, getCurrentDateTime()));
	cout << "Request from " << un << " has been completed...Waiting for the approval." << endl;
}

void user::TransactionsHistory()
{
	stack<transactions>transactionstack1;
	if (transactionstack.empty()) {
		cout << "There isn't any transactions yet\n";
		return;
	}
	int size = transactionstack.size();
	for (int i = 0; i < size; i++) {
		transactions t = transactionstack.top();
			cout << "Transaction " << i + 1 << ":" << endl;
			cout << "Transaction Type : " << t.type << endl;
			cout << "Paid: " << t.amount << endl;
			if (t.type != "Deposite") {
				cout << "To: " << t.reciever << endl;
			}
			cout << "Date and Time: " << t.DateAndTime << endl;
			transactionstack.pop();
			transactionstack1.push(t);
	}
	for (int i = 0; i < size; i++)
	{
		transactionstack.push(transactionstack1.top());
		transactionstack1.pop();
	}
	return;
}

void user::EditProfile()
{
	int choice;
	bool repeat = false;
	string newname;
	string ltname;

	cout << "Press 1 To edit the Name " << endl;
	cout << "Press 2 To edit the Password " << endl;
	cout << "Press 3 To edit the Phone Number " << endl;
	cout << "Press 4 to return to main menu " << endl;
	
	do {
		repeat = false;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max());
			cout << "Invalid input. Please enter a valid integer. " << endl;
			repeat = true;
		}
		else if (choice < 1 || choice >4) {
			cout << "Invalid input. Please enter a valid integer. " << endl;
			repeat = true;
		}
	} while (repeat);
	switch (choice) {
	case 1:
		cout << "Enter new Firstname: ";
		cin >> newname;
		Firstname = newname;
		cout << "Enter new Lastname: ";
		cin >> ltname;
		Lastname = ltname;
		cout << "The name has successefully changed" << endl;
		break;
	case 2:
		cout << "Enter new password: ";
		password = DigitalWalletSystem::checkPassword();
		cout << "The password has successefully changed" << endl;
		break;
	case 3:
		cout << "Enter new phone number : ";
		phonenumber = DigitalWalletSystem::checkPhoneNUmber();
		cout << "The phone number has successefully changed" << endl;
		break;
	case 4:
		return;
	}


	
}

void user::Usermenu()
{
	int choice;
	do {
		cout << "1. Approve Requests" << endl;
		cout << "2. Request Money" << endl;
		cout << "3. View Balance" << endl;
		cout << "4. Deposit" << endl;
		cout << "5. Edit Profile" << endl;
		cout << "6. Send Money" << endl;
		cout << "7. View Transaction History" << endl;
		cout << "0. Logout" << endl;
		cout << "Enter your choice: ";
		bool repeat;
		do {
			repeat = false;
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max());
				cout << "Invalid input. Please enter a valid integer. " << endl;
				repeat = true;
			}
		} while (repeat);
		switch (choice) {
		case 1:
			Requestapproval();
			break;
		case 2:
			RequestMoney();
			break;
		case 3:
			ViewBalance();
			break;
		case 4:
			Deposite();
			break;
		case 5:
			EditProfile();
			break;
		case 6:
			SendMoney();
			break;
		case 7:
			TransactionsHistory();
			break;
		case 0:
			cout << "Exiting user menu..." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0);
}
