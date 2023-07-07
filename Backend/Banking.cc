#include "Account.hh"
#include "Commondb.hh"
#include "CLInterface.hh"

#include <iostream>
#include <stdio.h>
#include <sqlite3.h> 

int main() {

    std::srand(std::time(nullptr)); 
    Commondb *cDB = Commondb::GetInstance();

    cDB->OpenDatabase("Bank_v1.db");

    CLInterface *clint = CLInterface::GetInstance();
    clint->runInterface();
    
    return 0;
}