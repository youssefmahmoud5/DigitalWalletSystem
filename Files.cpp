#include "Files.h"
#include <filesystem>
#include <fstream>


void Files::loadUsersFromFile(unordered_map<string, user>& users) {
    ifstream inFile("D:\\Simple2025\\user.txt");
    if (!inFile) {
        cerr << "Could not open file.\n";
        return;
    }

    while (!inFile.eof()) {
        user u;
        int numTransactions, numRequests;
        string line;

        getline(inFile, u.username);
        if (u.username.empty()) break; 

        getline(inFile, u.Firstname);
        getline(inFile, u.Lastname);
        getline(inFile, u.password);
        inFile >> u.balance;
        inFile.ignore();
        getline(inFile, u.phonenumber);
        inFile >> u.isDeleted >> u.isSuspended;
        inFile.ignore();

        inFile >> numTransactions;
        inFile.ignore();
        for (int i = 0; i < numTransactions; ++i) {
            transactions t;
            getline(inFile, t.type);
            if (t.type != "Deposite") {
                getline(inFile, t.sender);
            }
            getline(inFile, t.reciever);
            inFile >> t.amount;
            inFile.ignore();
            getline(inFile, t.DateAndTime);
            u.transactionstack.push(t);
        }

        inFile >> numRequests;
        inFile.ignore();
        for (int i = 0; i < numRequests; ++i) {
            Request r;
            getline(inFile, r.username);
            getline(inFile, r.FirstName);
            getline(inFile, r.LastName);
            inFile >> r.amount;
            inFile.ignore();
            getline(inFile, r.DateAndTime);
            getline(inFile, r.phonenumber);
            u.RequestsQueue.push(r);
        }

        getline(inFile, line); 
        users[u.username] = u;
    }

    inFile.close();
}
void Files::saveUsersToFile(const unordered_map<string, user>& users) {
    ofstream outFile("D:\\Simple2025\\user.txt");
    if (!outFile) {
        cerr << "Could not open file to write.\n";
        return;
    }

    for (const auto& pair : users) {
        const user& u = pair.second;
        outFile << u.username << '\n';
        outFile << u.Firstname << '\n';
        outFile << u.Lastname << '\n';
        outFile << u.password << '\n';
        outFile << u.balance << '\n';
        outFile << u.phonenumber << '\n';
        outFile << u.isDeleted << '\n' << u.isSuspended << '\n';

        stack<transactions> tempStack = u.transactionstack;
        vector<transactions> reversed;
        while (!tempStack.empty()) {
            reversed.push_back(tempStack.top());
            tempStack.pop();
        }
        outFile << reversed.size() << '\n';
        for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
            outFile << it->type << '\n';
            if (it->type != "Deposite") {
                outFile << it->sender << '\n';
            }
            outFile << it->reciever << '\n';
            outFile << it->amount << '\n';
            outFile << it->DateAndTime << '\n';
            
        }

        queue<Request> tempQueue = u.RequestsQueue;
        outFile << tempQueue.size() << '\n';
        while (!tempQueue.empty()) {
            Request r = tempQueue.front();
            tempQueue.pop();
            outFile << r.username << '\n';
            outFile << r.FirstName << '\n';
            outFile << r.LastName << '\n';
            outFile << r.amount << '\n';
            outFile << r.DateAndTime << '\n';
            outFile << r.phonenumber << '\n';
        }

        outFile << "===\n";
    }

    outFile.close();
}

void Files::loadSystemTransactionsFromFile()
{
    ifstream inFile("D:\\Simple2025\\trans.txt");
    if (!inFile) {
        cerr << "Could not open file.\n";
        return;
    }
    int numTransactions;
    string line;

    inFile >> numTransactions;
    inFile.ignore();
    for (int i = 0; i < numTransactions; ++i) {
        transactions t;
        getline(inFile, t.type);
        if (t.type != "Deposite") {
            getline(inFile, t.sender);
        }
        getline(inFile, t.reciever);
        inFile >> t.amount;
        inFile.ignore();
        getline(inFile, t.DateAndTime);
        DigitalWalletSystem::SystemTransactions.push(t);
    }

}

void Files::saveSystemTransactionsToFile()
{
    ofstream outFile("D:\\Simple2025\\trans.txt");
    if (!outFile) {
        cerr << "Could not open file to write.\n";
        return;
    }

    stack<transactions> tempStack = DigitalWalletSystem::SystemTransactions;
    vector<transactions> reversed;
    while (!tempStack.empty()) {
        reversed.push_back(tempStack.top());
        tempStack.pop();
    }
    outFile << reversed.size() << '\n';
    for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
        outFile << it->type << '\n';
        if (it->type != "Deposite") {
            outFile << it->sender << '\n';
        }
        outFile << it->reciever << '\n';
        outFile << it->amount << '\n';
        outFile << it->DateAndTime << '\n';

    }
}
