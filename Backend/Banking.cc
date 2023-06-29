#include "Account.hh"
#include "Commondb.hh"

#include <iostream>
#include <stdio.h>
#include <sqlite3.h> 

int main() {
    Commondb *cDB = Commondb::GetInstance();

    cDB->OpenDatabase("Bank_v1.db");

    return 0;
}