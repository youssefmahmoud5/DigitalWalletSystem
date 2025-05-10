#include "DigitalWalletSystem.h"
#include <regex>

unordered_map<string, user> DigitalWalletSystem::mapOfUsers;
stack<transactions> DigitalWalletSystem::SystemTransactions;

 void DigitalWalletSystem::SignUp()
{
	 cout << "Enter Firstname: ";
	 string firstname;
	 cin >> firstname;
	 cout << "Enter Lastname: ";
	 string lastname;
	 cin >> lastname;
	cout << "Enter username: ";
	bool repeat = false;
	string username;
	do{
		repeat = false;
		cin >> username;
		if (mapOfUsers.find(username) != mapOfUsers.end()) {
			cout << "Username already exists...Please enter another one." << endl;
			repeat = true;
		}
	} while (repeat);
	cout << "Enter password: ";
	string password = hashing(checkPassword());
	cout << "Enter phone number: ";
	string phoneNumber = checkPhoneNUmber();
	user newuser = user(username,firstname, lastname, password, phoneNumber,false,false);
	mapOfUsers[username] = newuser;
	cout << "Sign up Completed" << endl;
 }
 void DigitalWalletSystem::login() {
	 string username, password;
	 bool repeat = false;
	 do {
		 repeat = false;
		 cout << "Username: ";
		 cin >> username;
		 auto it = mapOfUsers.find(username);
		 if (it == mapOfUsers.end()) {
			 cout << "User not found. Please Renter the username or sign up first." << endl;
			 cout << "Press S to signup or press any buttom to reenter username";
			 char s;
			 cin >> s;
			 if (s == 'S' || s == 's') {
				 return;
			 }
			 repeat = true;
		 }
	 }while (repeat);
	 if (mapOfUsers[username].isDeleted) {
		 cout << "Your account have been deleted by the admin";
		 return;
	 }
	 if (mapOfUsers[username].isSuspended) {
		 cout << "Your account is currently disabled. Please contact the admin for assistance." << endl
			 << "Email:Admin22@gmail.com " << endl;
		 return;
	 }
	 do {
		 repeat = false;
		 cout << "Password: ";
		 cin >> password;
		 password = hashing(password);
		 if (!(mapOfUsers[username].getpassword() == password)) {
			 cout << "Incorrect Password" << endl;
			 cout << "Press E to exit or press any buttom to reenter Password";
			 char s;
			 cin >> s;
			 if (s == 'E' || s == 'e') {
				 return;
			 }
			 repeat = true;
		 }
	 } while (repeat);
	 mapOfUsers[username].Usermenu();
 }

 void DigitalWalletSystem::AdminLogin()
 {
	 string inputUsername, inputPassword;
	 cout << "Admin Username: ";
	 cin >> inputUsername;
	 cout << "Admin Password: ";
	 cin >> inputPassword;
	 admin obj = admin();
	 if (inputUsername == admin::username && inputPassword == admin::password) {
		 cout << "Admin login successful.\n";
		 obj.AdminMenu();
	 }
	 cout << "Incorrect credentials.\n";
	 return;
 }

 string DigitalWalletSystem::hashing(string password1)
 {
	 string hash;
	 for (char c : password1) {
		 int hashedpass = static_cast<int>(c) + 20;
		 hash += std::to_string(hashedpass);
	 }
	 return hash;
 }
 

 string DigitalWalletSystem::checkPassword()
 {
	 string inputpassword;
	 bool repeat = false;
	 do {
		 repeat = false;
		 cin >> inputpassword;
		 bool hasUpperCase = false, hasLowerCase = false, hasNumber = false;
		 if (inputpassword.length() < 8) {
			 cout << "Password must be at least 8 characters " << endl;
			 repeat = true;
		 }

		 for (char test : inputpassword) {
			 if (islower(test)) {
				 hasLowerCase = true;
			 }
			 else if (isupper(test)) {
				 hasUpperCase = true;
			 }
			 else if (isdigit(test)) {
				 hasNumber = true;
			 }
		 }

		 if (!hasUpperCase || !hasLowerCase || !hasNumber) {
			 cout << "Password must contain at least one lowercase letter";
			 cout << "one uppercase letter and one digit." << endl;
			 repeat = true;

		 }
		 if (repeat) {
			 cout << "Please try again: ";
		 }
	 } while (repeat);
	 return inputpassword;
 }

 string DigitalWalletSystem::checkPhoneNUmber()
 {
	 string phoneNumber;
	 bool repeat = false;
	 do {
		 repeat = false;
		 cin >> phoneNumber;
		 regex phoneTest(R"(01\d{9})");
		 if (!regex_match(phoneNumber, phoneTest)) {
			 cout << "Invalid phone number format. Please enter an 11-digit number starting with 01: ";
			 repeat = true;
		 }
	 } while (repeat);
	 return phoneNumber;
 }

