#include "CurrentAccount.hh"

CurrentAccount::CurrentAccount(): fAccountID(0), fValue(0.), fIntrestRate(0.)
{
}

CurrentAccount::CurrentAccount(int accountID, double value, double intrestrate): 
    fAccountID(accountID), fValue(value), fIntrestRate(intrestrate)
{
}
