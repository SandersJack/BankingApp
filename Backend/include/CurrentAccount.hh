#ifndef CurrentAccount_H
#define CurrentAccount_H 

#include <ctime>
#include <iostream>

using namespace std;

class CurrentAccount {

public:
    CurrentAccount();
    CurrentAccount(int accountID, double value, double intrestrate);
    
    int GetAccountID(){ return fAccountID;}
    double GetValue(){ return fValue;}
    double GetIntrestrate(){ return fIntrestRate;}

    void SetAccountID(int val) {fAccountID = val;}
    void SetValue(double val){ fValue = val;}
    void SetIntrestRate(double val){ fIntrestRate = val;}

    void _toValue(double val){ fValue += val;}


    
private:
    int fAccountID;
    double fValue;
    double fIntrestRate;
};

#endif