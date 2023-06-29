#include "CLInterface.hh"
#include "Accountdb.hh"

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

  int mainresponse = mainMenu();
  int sreponse;
  
  switch (mainresponse)
  {
  case 1:
    addAccountPage(); 
  case 99:
    sreponse = adminToolsPage();
    break;
  default:
    break;
  }
}


int CLInterface::mainMenu(){
  system("clear");

  int res;

  cout << "***************************** Main Menu *****************************" << endl;
  cout << "**                       (1) Add New Account                       **" << endl;
  cout << "**                       (2) Modify  Account                       **" << endl;
  cout << "**                                                                 **" << endl;
  cout << "**                       (99) Admin Tools                          **" << endl;
  cout << "*********************************************************************" << endl;
  cin >> res;

  return res;
}

void CLInterface::addAccountPage(){
  system("clear");
  cout << "***************************** +++++ Page ****************************" << endl;
}

int CLInterface::adminToolsPage(){
  system("clear");

  int res;

  cout << "***************************** Admin Page ****************************" << endl;
  cout << "**                    (1) Create Account Table to DB               **" << endl;
  cout << "**                                                                 **" << endl;
  cout << "**                    (0) Return to Main Menu                      **" << endl;
  cout << "*********************************************************************" << endl;

  cin >> res;

  switch (res)
  {
  case 0:
    return 0;
  case 1:
    Accountdb::GetInstance()->createTable();
    return 1;
  
  default:
    return 1;
  }
}