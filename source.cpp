#include <iostream>
#include <list>
#include "user.h"
#include "DigitalWalletSystem.h"
#include "admin.h"
using namespace std;

int main() {

    int choice;
    bool repeat;
    do {
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
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
            DigitalWalletSystem::AdminLogin();
            break;
        case 2: {
            int userChoice;
            cout << "1. Login" << endl;
            cout << "2. Signup" << endl;
            cout << "Enter your choice: ";
            do {
                repeat = false;
                cin >> userChoice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max());
                    cout << "Invalid input. Please enter a valid integer. " << endl;
                    repeat = true;
                }
            } while (repeat);
            if (userChoice == 1) {
                DigitalWalletSystem::login();
            }
            else if (userChoice == 2) {
                DigitalWalletSystem::SignUp();
            }
            else {
                cout << "Invalid user menu choice." << endl;
            }
            break;
        }
        case 0:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid main menu choice." << endl;
        }

    } while (choice != 0);
	return 0;
}