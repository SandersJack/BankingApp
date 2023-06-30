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
  bool loop = true;
  while(loop){
    int mainresponse = mainMenu();
    int sreponse;
    cout << mainresponse << endl;
    switch (mainresponse)
    {
    case 0:
      loop = false;
      break;
    case 1:
      sreponse = addAccountPage(); 
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
  cout << "**                                                                 **" << endl;
  cout << "**                       (99) Admin Tools                          **" << endl;
  cout << "**                       (0) Exit Program                          **" << endl;
  cout << "*********************************************************************" << endl;
  cin >> res;

  return res;
}

int CLInterface::addAccountPage(){
  
  bool loop = true;
  int res;
  
    system("clear");
    cout << "***************************** +++++ Page ****************************" << endl;
    cout << "**                    (0) Return to Main Menu                      **" << endl;
    cout << "*********************************************************************" << endl;
  while(loop){
    cin >> res;

    switch (res)
    {
    case 0:
      return 0;
    default:
      cout << "Invalid Option" << endl;
    }
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