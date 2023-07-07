#ifndef Accountdb_H
#define Accountdb_H 

#include "Account.hh"
#include "Commondb.hh"
#include "Vdb.hh"

class Accountdb: public Vdb {
    public:
        Accountdb();

        static Accountdb *GetInstance();

        int createTable();
        int saveEntry(Account *entry);
        Account *getEntry(string query);

        int printAllEntry();

    private:

        static Accountdb *fInstance;
        Commondb *fCommondb;

        
};

#endif