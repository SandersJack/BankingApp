#ifndef CurrentAccount_H
#define CurrentAccount_H 

#include "CommonAccount.hh"

#include <ctime>
#include <iostream>

using namespace std;

class CurrentAccount: public CommonAccount {

public:
    CurrentAccount();
    CurrentAccount(int accountID, double value, double intrestrate);


    
private:

};

#endif