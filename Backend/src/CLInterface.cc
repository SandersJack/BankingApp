#include "CLInterface.hh"

#include "Accountdb.hh"
#include "Account.hh"

#include "CurrentAccountdb.hh"
#include "CurrentAccount.hh"

#include <stdlib.h>
#include <iostream>

CLInterface::CLInterface()
{
    
}

CLInterface *CLInterface::fInstance = nullptr;

CLInterface *CLInterface::GetInstance() {
  if(!fInstance)
    fInstance = new CLInterface();
  return fInstance;
}

void CLInterface::runInterface(){
  bool loop = true;
  while(loop){
    int mainresponse = mainMenu();
    int sreponse;
    std::cout << mainresponse << std::endl;
    switch (mainresponse)
    {
    case 0:
      loop = false;
      break;
    case 1:
      sreponse = addAccountPage(); 
      break;
    case 2:
      sreponse = viewModifyPage();
      break;
    case 3:
      sreponse = viewAccountPage();
      break;  
    case 4:
      sreponse = loginAccountPage();
      break;
    case 99:
      sreponse = adminToolsPage();
      break;
    default:
      break;
  }
  }
}


int CLInterface::mainMenu(){
  system("clear");

  int res;

  cout << "***************************** Main Menu *****************************" << endl;
  cout << "**                       (1) Add New Account                       **" << endl;
  cout << "**                       (2) Modify  Account                       **" << endl;
  cout << "**                       (3) View    Accounts                      **" << endl;
  cout << "**                       (4) Login to Account                      **" << endl;
  cout << "**                                                                 **" << endl;
  cout << "**                       (99) Admin Tools                          **" << endl;
  cout << "**                       (0) Exit Program                          **" << endl;
  cout << "*********************************************************************" << endl;
  cin >> res;

  return res;
}

int CLInterface::addAccountPage(){
  
  bool loop = true;
  int dob;
  string pass;
  string ques;
  string name;
  string email;


    system("clear");
    cout << "************************* New Account Page **************************" << endl;
    cout << "**                    (0) Return to Main Menu                      **" << endl;
    cout << "*********************************************************************" << endl;
    Account *nAccount = new Account();
    nAccount->GenerateID();
    cout << "Creating account with ID: " << nAccount->GetAccountID() << endl;
    cout << "Account Name: ";
    cin >> name;
    if(name == "0")
      return 0;
    nAccount->SetName(name);
    cout << "Email: ";
    cin >> email;
    if(email == "0")
      return 0;
    nAccount->SetEmail(email);  
    cout << "DOB: ";
    cin >> dob;
    if(dob == 0)
      return 0;
    nAccount->SetDOB(dob);
    cout << "Set a Password: ";
    cin >> pass;
    if(pass == "0")
      return 0;
    nAccount->SetPassword(pass);
    cout << "Security Question. What was the name of your first pet? ";
    cin >> ques;
    if(ques == "0")
      return 0;
    nAccount->SetQuestion(ques);

    cout << "Do you want to save this new Account to the Database? [Y/N]" << endl;
    string ans;
    cin >> ans;
    if(ans == "Y"){
      Accountdb::GetInstance()->saveEntry(nAccount);
      int slowDown;
      cin >> slowDown;
    } else if (ans == "N"){
      return 0;
    }

    return 0;
}

int CLInterface::viewModifyPage(){
  system("clear");
  int res;
  int id;
  cout << "***************************** Modify Page ***************************" << endl;
  cout << "**                    (1) Delete Account                           **" << endl;
  cout << "**                                                                 **" << endl;
  cout << "**                    (0) Return to Main Menu                      **" << endl;
  cout << "*********************************************************************" << endl;
  cin >> res;
  switch(res){
    case 1:
      cout << "Enter ID: ";
      cin >> id;
      Accountdb::GetInstance()->deleteAccount(id);
      break;
    case 0:
      return 0;
  }
  return 0;
}

int CLInterface::viewAccountPage(){
  system("clear");
  int res;
  cout << "***************************** Account Page **************************" << endl;
  cout << "**                    (1) View All Accounts                        **" << endl;
  cout << "**                    (2) View Account By ID                       **" << endl;
  cout << "**                                                                 **" << endl;
  cout << "**                    (0) Return to Main Menu                      **" << endl;
  cout << "*********************************************************************" << endl;

  cin >> res;
  cout << res << endl;
  switch(res){
    case 1:
      Accountdb::GetInstance()->printAllEntry();
      break;
    case 2:
      int id;
      cout << "Query ID: ";
      cin >> id;
      Accountdb::GetInstance()->printEntry(id);
      break;
    case 0:
      return 0;

  }
  return 0;
}

int CLInterface::loginAccountPage(){
  
  int res;
  int id;
  while(true){
    system("clear");
    cout << "**********************  Login Account Page **************************" << endl;
    cout << "**                                                                 **" << endl;
    cout << "**                    (0) Return to Main Menu                      **" << endl;
    cout << "*********************************************************************" << endl;
    cout << "Please enter Account ID: ";
    cin >> id;
    if(id == 0)
      return 0;

    Account *loginAccount = Accountdb::GetInstance()->getAccount(id);
    std::cout << "Account Loaded" << std::endl;
    int seqRes = loginAccount->securityCheck();
    if(seqRes == 50){
      cin >> res;
      continue;
    } else if(seqRes == 0){
      accountPage(loginAccount);
    }
  }
  cin >> res;
  return 0;
}

int CLInterface::accountPage(Account *loginAccount){
  system("clear");
  int res;
  cout << "************************* Account Page ******************************" << endl;
  cout << "**                        ID = " << loginAccount->GetAccountID() << "                             **" << endl;
  cout << "**                    (0) Logout of account                        **" << endl;
  cout << "*********************************************************************" << endl; 
  cin >> res;
  return 0;
}

int CLInterface::adminToolsPage(){
  system("clear");
  bool loop;
  int res;

  
  cout << "***************************** Admin Page ****************************" << endl;
  cout << "**                    (1) Create Account Table to DB               **" << endl;
  cout << "**                    (2) Create CurrentAccount Table to DB        **" << endl;
  cout << "**                                                                 **" << endl;
  cout << "**                    (0) Return to Main Menu                      **" << endl;
  cout << "*********************************************************************" << endl;
  while(loop){
    cin >> res;

    switch (res)
    {
    case 0:
      return 0;
    case 1:
      Accountdb::GetInstance()->createTable();
      break;
    case 2:
      CurrentAccountdb::GetInstance()->createTable();
      break;
    default:
      cout << "Invalid Option" << endl;
    }
  }
  
  return 0;
}