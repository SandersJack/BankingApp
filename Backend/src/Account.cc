#include "Account.hh"

Account::Account(): fAccountID(0), fAccountName(""), fEmail(""), fAge(0)
{
}

Account::Account(int accountID, string accountName, string email, int age): 
    fAccountID(accountID), fAccountName(accountName), fEmail(email), fAge(age)
{
}
