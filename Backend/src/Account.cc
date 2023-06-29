#include "Account.hh"

Account::Account(): fAccountID(0), fAccountName(""), fEmail("")
{
}

Account::Account(int accountID, string accountName, string email): 
    fAccountID(accountID), fAccountName(accountName), fEmail(email)
{
}
