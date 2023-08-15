#ifndef Accountdb_H
#define Accountdb_H 

#include "Account.hh"
#include "Commondb.hh"
#include "Vdb.hh"
#include <vector>

using namespace std;

class Accountdb: public Vdb {
    public:
        Accountdb();

        static Accountdb *GetInstance();

        int createTable();
        int saveEntry(Account *entry);
        int deleteAccount(int id);

        int printAllEntry();
        int printEntry(int id);
        Account *getAccount(int id);

    private:

        static Accountdb *fInstance;
        Commondb *fCommondb;

        
};

#endif