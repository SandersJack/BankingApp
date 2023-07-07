#include "CLInterface.hh"
#include "Accountdb.hh"
#include "Account.hh"

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
    switch (mainresponse)
    {
    case 0:
      loop = false;
      break;
    case 1:
      sreponse = addAccountPage(); 
      break;
    case 3:
      sreponse = viewAccountPage();
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
  cout << "**                                                                 **" << endl;
  cout << "**                       (99) Admin Tools                          **" << endl;
  cout << "**                       (0) Exit Program                          **" << endl;
  cout << "*********************************************************************" << endl;
  cin >> res;

  return res;
}

int CLInterface::addAccountPage(){
  
  bool loop = true;
  int age;
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
    cout << "Age: ";
    cin >> age;
    if(age == 0)
      return 0;
    nAccount->SetAge(age);

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

int CLInterface::viewAccountPage(){
  system("clear");
  int res;
  cout << "***************************** Admin Page ****************************" << endl;
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

int CLInterface::adminToolsPage(){
  system("clear");
  bool loop;
  int res;

  
  cout << "***************************** Admin Page ****************************" << endl;
  cout << "**                    (1) Create Account Table to DB               **" << endl;
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
    
    default:
      cout << "Invalid Option" << endl;
    }
  }
  
  return 0;
}