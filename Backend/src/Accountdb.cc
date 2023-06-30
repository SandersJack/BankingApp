#include "Accountdb.hh"
#include "Commondb.hh"

static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;

    fprintf(stderr, "%s: ", (const char*)data);

    for( i = 0; i<argc; i++) {
        printf("%s = %s \n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return(0);
}

Accountdb::Accountdb(): Vdb()
{
    fCommondb = Commondb::GetInstance();
}

Accountdb *Accountdb::fInstance = nullptr;

Accountdb *Accountdb::GetInstance() {
  if(!fInstance)
    fInstance = new Accountdb();
  return fInstance;
}

int Accountdb::createTable(){
    string sql;
    int rc;
    char *zErrMsg = 0;

    // Create SQL Table //

    sql = "CREATE TABLE PERSONS(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "EMAIL          TEXT    NOT NULL," \
        "AGE            INT     NOT NULL);";

    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), callback, 0, &zErrMsg);
    int res; 
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s \n", zErrMsg);
        sqlite3_free(zErrMsg);
        cin >> res;
        return 1;
    } else {
        fprintf(stderr, "Table created successfully \n");
        cin >> res;
    }

    

    return 0;
}