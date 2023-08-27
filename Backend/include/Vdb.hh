#ifndef Vdb_H
#define Vdb_H 

#include "CommonAccount.hh"

#include <string>
#include <iostream>
#include <stdio.h>
#include <sqlite3.h> 

class Vdb {
    public:
        Vdb();

        int executeSQLQuery(sqlite3 *db,               
                            const char *zSql, int (*function)(void *, int , char **, char **), void *p_data);

        int updateEntry(CommonAccount *entry);

    private:
    
        void printColumnValue(sqlite3_stmt* stmt, int col);

        //
};

#endif