#include "SavingsAccount.hh"

SavingsAccount::SavingsAccount()
{
    fAccountID = 0;
    fValue = 0;
    fIntrestRate = 0;
}

SavingsAccount::SavingsAccount(int accountID, double value, double intrestrate)
{
    fAccountID = accountID;
    fValue = value;
    fIntrestRate = intrestrate;
}
