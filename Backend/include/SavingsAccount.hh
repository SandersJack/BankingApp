#ifndef SavingsAccount_H
#define SavingsAccount_H 

#include "CommonAccount.hh"

#include <ctime>
#include <iostream>

using namespace std;

class SavingsAccount: public CommonAccount {

public:
    SavingsAccount();
    SavingsAccount(int accountID, double value, double intrestrate);


    
private:

};

#endif