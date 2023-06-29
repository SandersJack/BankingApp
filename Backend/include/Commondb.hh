#ifndef Commondb_H
#define Commondb_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <sqlite3.h> 

using namespace std;

class Commondb {
    public:
        Commondb();

        int OpenDatabase(string name);
        sqlite3 *GetDatabase() {return fDatabase;}

        static Commondb *GetInstance();

    private:
        static Commondb *fInstance;
        sqlite3 *fDatabase;


};

#endif