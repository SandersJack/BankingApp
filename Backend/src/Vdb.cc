#include "Vdb.hh"

Vdb::Vdb()
{
}

int callback(void *data, int argc, char **argv, char **azColName) {
    int i;

    fprintf(stderr, "%s: ", (const char*)data);

    for( i = 0; i<argc; i++) {
        printf("%s = %s \n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return(0);
}

//int dbExec(sqlite3 db, const char* sql, 0, char *zErrMsg){
//
//}