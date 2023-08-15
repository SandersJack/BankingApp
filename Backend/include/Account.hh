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
    Account(int accountID, string accountName, string email, int age, string pass, string ques);
    
    string GetAccountName(){ return fAccountName;};
    int GetAccountID(){ return fAccountID;}
    string GetEmail(){ return fEmail;}
    int GetDOB(){ return fDOB;}
    string GetPassword(){ return fPassword;}
    string GetQuestion(){ return fQuestion;}

    void SetAccountID(int val){fAccountID = val;}
    void SetName(string val){fAccountName = val;}
    void SetEmail(string val){fEmail = val;}
    void SetDOB(int val){fDOB = val;}
    void SetPassword(string val){fPassword = val;}
    void SetQuestion(string val){fQuestion = val;}
    void GenerateID(){fAccountID = randID();}

    int securityCheck();

    
private:
    int fAccountID;
    string fAccountName;
    string fEmail;
    int fDOB;
    string fPassword;
    string fQuestion;
};

#endif