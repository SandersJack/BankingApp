#ifndef CurrentAccountdb_H
#define CurrentAccountdb_H 

#include "Account.hh"
#include "CurrentAccount.hh"
#include "Commondb.hh"
#include "Vdb.hh"
#include <vector>

using namespace std;

class CurrentAccountdb: public Vdb {
    public:
        CurrentAccountdb();

        static CurrentAccountdb *GetInstance();

        int createTable();
        int saveEntry(CurrentAccount *entry);
        int deleteAccount(int id);

        int printAllEntry();
        int printEntry(int id);
        CurrentAccount *getCurrentAccount(int id);

    private:

        static CurrentAccountdb *fInstance;
        Commondb *fCommondb;

        
};

#endif