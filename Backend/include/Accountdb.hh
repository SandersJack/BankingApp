#ifndef Accountdb_H
#define Accountdb_H 

#include "Account.hh"
#include "Commondb.hh"

class Accountdb {
    public:
        Accountdb();

        static Accountdb *GetInstance();

        int createTable();
        int saveEntry(Account *entry);
        Account *getEntry(string query);

    private:

        static Accountdb *fInstance;

        
};

#endif