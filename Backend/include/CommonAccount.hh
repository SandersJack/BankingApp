#ifndef CommonAccount_H
#define CommonAccount_H 

#include <ctime>
#include <iostream>

using namespace std;

class CommonAccount {

public:
    CommonAccount();
    CommonAccount(int accountID, double value, double intrestrate);
    
    string GetProductName(){return fProductName;}
    int GetAccountID(){ return fAccountID;}
    double GetValue(){ return fValue;}
    double GetIntrestrate(){ return fIntrestRate;}

    void SetProductName(string val){fProductName = val;}
    void SetAccountID(int val) {fAccountID = val;}
    void SetValue(double val){ fValue = val;}
    void SetIntrestRate(double val){ fIntrestRate = val;}

    void _toValue(double val){ fValue += val;}

    int transferTo(CommonAccount *to_account, double value);


    
public:
    string fProductName;
    int fAccountID;
    double fValue;
    double fIntrestRate;
};

#endif