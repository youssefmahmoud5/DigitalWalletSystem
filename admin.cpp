#include "admin.h"
#include "DigitalWalletSystem.h"
#include <unordered_map>
using namespace std;

const string admin::username = "admin";
const string admin::password = "admin";

admin::admin()
{
	const string username = "admin";
	const string password = "admin";
}

void admin::AdminMenu()
{
	int choice;
	bool repeat;
	do {
		cout << "1. Edit Accounts" << endl;
		cout << "2. View Transactions" << endl;
		cout << "3. View Users" << endl;
		cout << "4. Add Users" << endl;
		cout << "5. Change Suspendation Status" << endl;
		cout << "6. Delete Account" << endl;
		cout << "0. logout" << endl;
		cout << "Enter your choice: ";
		do {
			repeat = false;
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a valid integer. " << endl;
				repeat = true;
			}
		} while (repeat);
		switch (choice) {
		case 1:
			editAccounts();
			break;
		case 2:
			viewTransactions();
			break;
		case 3:
			viewUsers();
			break;
		case 4:
			AddUsers();
			break;
		case 5:
			SuspendationStatus();
			break;
		case 6:
			deleteAccount();
			break;
		case 0:
			cout << "Exiting admin menu..." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0);
}

void admin::viewUsers()
{
    if (DigitalWalletSystem::mapOfUsers.empty()) {
        cout << "No users in the system." << endl;
        return;
    }

    cout << "All Users:" << endl;
	cout << "Press 1 to View Activated Users" << endl;
	cout << "Press 2 to View Suspended Users" << endl;
	cout << "Press 3 to View Deleted Users" << endl;
	int choice;
	bool repeat;
	do {
		repeat = false;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid integer. " << endl;
			repeat = true;
		}
		else if (choice < 1 || choice >3) {
			cout << "Invalid input. Please enter a valid integer. " << endl;
			repeat = true;
		}
	} while (repeat);
    for (const auto& pair : DigitalWalletSystem::mapOfUsers) {
		
		if (choice == 1) {
			if (pair.second.isDeleted == false && pair.second.isSuspended == false) {
				cout << "Username: " << pair.first << endl;
				cout << "Name: " << pair.second.Firstname << " " << pair.second.Lastname << endl;
				cout << "PhoneNUmber: " << pair.second.phonenumber << endl;
				if (!pair.second.isDeleted) {
					cout << "Not Deleted" << endl;
				}
				else {
					cout << "Deleted" << endl;
				}
				if (!pair.second.isSuspended) {
					cout << "Not Suspended" << endl;
				}
				else {
					cout << "Suspended" << endl;
				}
				DigitalWalletSystem::mapOfUsers[pair.first].TransactionsHistory();
			}
		}else if (choice == 2) {
			if (pair.second.isSuspended == true) {
				cout << "Username: " << pair.first << endl;
				cout << "Name: " << pair.second.Firstname << " " << pair.second.Lastname << endl;
				cout << "PhoneNUmber: " << pair.second.phonenumber << endl;
				if (!pair.second.isDeleted) {
					cout << "Not Deleted" << endl;
				}
				else {
					cout << "Deleted" << endl;
				}
				if (!pair.second.isSuspended) {
					cout << "Not Suspended" << endl;
				}
				else {
					cout << "Suspended" << endl;
				}
				DigitalWalletSystem::mapOfUsers[pair.first].TransactionsHistory();
			}
		}
		else if (choice == 3) {
			if (pair.second.isDeleted == true) {
				cout << "Username: " << pair.first << endl;
				cout << "Name: " << pair.second.Firstname << " " << pair.second.Lastname << endl;
				cout << "PhoneNUmber: " << pair.second.phonenumber << endl;
				if (!pair.second.isDeleted) {
					cout << "Not Deleted" << endl;
				}
				else {
					cout << "Deleted" << endl;
				}
				if (!pair.second.isSuspended) {
					cout << "Not Suspended" << endl;
				}
				else {
					cout << "Suspended" << endl;
				}
				DigitalWalletSystem::mapOfUsers[pair.first].TransactionsHistory();
			}
		}
    }
}

void admin::viewTransactions()
{
	stack<transactions>transactionstack1;
	if (DigitalWalletSystem::SystemTransactions.empty()) {
		cout << "There isn't any transactions yet\n";
		return;
	}
	int size = DigitalWalletSystem::SystemTransactions.size();
	for (int i = 0; i < size; i++) {
		transactions t = DigitalWalletSystem::SystemTransactions.top();
		cout << "Transaction " << i + 1 << ":" << endl;
		cout << "Transaction Type : " << t.type << endl;
		cout << "Paid: " << t.amount << endl;
		if (t.type != "Deposite") {
			cout << "To: " << t.reciever << endl;
		}
		cout << "Date and Time: " << t.DateAndTime << endl;
		DigitalWalletSystem::SystemTransactions.pop();
		transactionstack1.push(t);
	}
	for (int i = 0; i < size; i++)
	{
		DigitalWalletSystem::SystemTransactions.push(transactionstack1.top());
		transactionstack1.pop();
	}
	return;
}

void admin::SuspendationStatus()
{
	string uname;
	cout << "Enter username to edit: ";
	cin >> uname;

	auto it = DigitalWalletSystem::mapOfUsers.find(uname);
	if (it == DigitalWalletSystem::mapOfUsers.end()) {
		cout << "User not found." << endl;
		return;
	}
	if (DigitalWalletSystem::mapOfUsers[uname].isSuspended) {
		cout << "The account is suspended...Do you want to reactivate the account" << endl;
		cout << "Press Y to reactivate or any another Letter to exit: ";
		char c;
		cin >> c;
		if (c == 'Y' || c == 'y') {
			DigitalWalletSystem::mapOfUsers[uname].isSuspended = false;
		}
	}
	else {
		cout << "The account is Activated...Do you want to suspend the account" << endl;
		cout << "Press Y to suspend or any another Letter to exit: ";
		char c;
		cin >> c;
		if (c == 'Y' || c == 'y') {
			DigitalWalletSystem::mapOfUsers[uname].isSuspended = true;
			cout << "The Account is Suspended" << endl;
		}
	}
}

void admin::deleteAccount()
{
	string uname;
	cout << "Enter username to edit: ";
	cin >> uname;

	auto it = DigitalWalletSystem::mapOfUsers.find(uname);
	if (it == DigitalWalletSystem::mapOfUsers.end()) {
		cout << "User not found." << endl;
		return;
	}
	if (DigitalWalletSystem::mapOfUsers[uname].isDeleted) {
		cout << "The account was already deleted..." << endl;
	}
	else {
		cout << "The account is Activated...Do you want to Delete the account" << endl;
		cout << "Press Y to delete or any another Letter to exit: ";
		char c;
		cin >> c;
		if (c == 'Y' || c == 'y') {
			DigitalWalletSystem::mapOfUsers[uname].isDeleted = true;
			cout << "The Account is deleted" << endl;
		}
	}
}
void admin::editAccounts()
{
	string uname;
	string newname;
	string ltname;
	bool repeat;
	cout << "Enter username to edit: ";
	cin >> uname;

	auto it = DigitalWalletSystem::mapOfUsers.find(uname);
	if (it == DigitalWalletSystem::mapOfUsers.end()) {
		cout << "User not found." << endl;
		return;
	}
	int choice1;
	cout << "Press 1 To edit the Name " << endl;
	cout << "Press 2 To edit the Password " << endl;
	cout << "Press 3 To edit the Phone Number " << endl;
	cout << "Press 4 adjust Balance" << endl;
	cout << "Press 5 to exit" << endl;

	do {
		repeat = false;
		cin >> choice1;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid integer. " << endl;
			repeat = true;
		}
		else if (choice1 < 1 || choice1 >5) {
			cout << "Invalid input. Please enter a valid integer. " << endl;
			repeat = true;
		}
	} while (repeat);
	switch (choice1) {
	case 1:
		cout << "Enter new Firstname: ";
		cin >> newname;
		DigitalWalletSystem::mapOfUsers[uname].Firstname = newname;
		cout << "Enter new Lastname: ";
		cin >> ltname;
		DigitalWalletSystem::mapOfUsers[uname].Lastname = ltname;
		cout << "The name has successefully changed" << endl;
		break;
	case 2:
		cout << "Enter new password: ";
		DigitalWalletSystem::mapOfUsers[uname].password = DigitalWalletSystem::hashing(DigitalWalletSystem::checkPassword());
		cout << "The password has successefully changed" << endl;
		break;
	case 3:
		cout << "Enter new phone number : ";
		DigitalWalletSystem::mapOfUsers[uname].phonenumber = DigitalWalletSystem::checkPhoneNUmber();
		cout << "The phone number has successefully changed" << endl;
		break;
	case 4:
		cout << "Enter the Adjusted Balance: ";
		int balance1;
		cin >> balance1;
		DigitalWalletSystem::mapOfUsers[uname].balance = balance1;
		break;
	case 5:
		return;
	}
}
void admin::AddUsers()
{
	DigitalWalletSystem::SignUp();
}
