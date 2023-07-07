#ifndef Account_H
#define Account_H 

#include <ctime>
#include <iostream>

using namespace std;

static int randID()
{
    return 1 + (std::rand() % (9999999));
}

class Account {

public:
    Account();
    Account(int accountID, string accountName, string email, int age);
    
    string GetAccountName(){ return fAccountName;};
    int GetAccountID(){ return fAccountID;}
    string GetEmail(){ return fEmail;}
    int GetAge(){ return fAge;}

    void SetName(string val){fAccountName = val;}
    void SetEmail(string val){fEmail = val;}
    void SetAge(int val){fAge = val;}
    void GenerateID(){fAccountID = randID();}

    
private:
    int fAccountID;
    string fAccountName;
    string fEmail;
    int fAge;
};

#endif