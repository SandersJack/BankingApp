#include "Account.hh"

Account *Account::fInstance = nullptr;

Account::Account(){
    Accountname = "Jack";
};

Account *Account::GetInstance() {
  if(!fInstance)
    fInstance = new Account();
  return fInstance;
};