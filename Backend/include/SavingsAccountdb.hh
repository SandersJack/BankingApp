#ifndef SavingsAccountdb_H
#define SavingsAccountdb_H 

#include "Account.hh"
#include "SavingsAccount.hh"
#include "Commondb.hh"
#include "Vdb.hh"
#include <vector>

using namespace std;

class SavingsAccountdb: public Vdb {
    public:
        SavingsAccountdb();

        static SavingsAccountdb *GetInstance();

        int createTable();
        int saveEntry(SavingsAccount *entry);
        int deleteEntry(int id);

        int printAllEntry();
        int printEntry(int id);
        SavingsAccount *getSavingsAccount(int id);
        
    private:

        static SavingsAccountdb *fInstance;
        Commondb *fCommondb;

        
};

#endif