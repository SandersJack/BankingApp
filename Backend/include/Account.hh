#ifndef Account_H
#define Account_H 


#include <iostream>

using namespace std;

class Account {

public:
    Account();
    Account(int accountID, string accountName, string email);
    string GetAccountName(){ return fAccountName;};

private:
    int fAccountID;
    string fAccountName;
    string fEmail;
};

#endif