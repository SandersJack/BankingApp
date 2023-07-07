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

static int tablecallback(void *data, int argc, char **argv, char **azColName) {
    int i;
    cout << "**    "<< argv[0] <<"    **      "<< argv[1] << "     **     *****      **     "<<argv[3]<<"      **" << endl;
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

    sql = "CREATE TABLE Accounts(" \
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

int Accountdb::printAllEntry() {
    char *iErrMsg = 0;
    int rc;
    const char* data = "";
    int res;
    string sql = "SELECT * from Accounts";
    cout << "*********************************************************************" << endl;
    cout << "**      ID       **      Name     **     Email      **     Age     **" << endl;
    cout << "*********************************************************************" << endl;
    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), tablecallback, (void*)data, &iErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", iErrMsg);
        sqlite3_free(iErrMsg);
        cin >> res;
        return 1;
    } else {
        fprintf(stdout, "Operation done successfully\n");
        cin >> res;
    }

    return(0);
}

int Accountdb::printEntry(int id) {
    char *iErrMsg = 0;
    const char* data = "";
    int rc;
    int res;

    string sql = "SELECT * from Accounts WHERE ID=" + to_string(id);
    cout << "*********************************************************************" << endl;
    cout << "**      ID       **      Name     **     Email      **     Age     **" << endl;
    cout << "*********************************************************************" << endl;
    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), tablecallback, (void*)data, &iErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", iErrMsg);
        sqlite3_free(iErrMsg);
        cin >> res;
        return 1;
    } else {
        fprintf(stdout, "Operation done successfully\n");
        cin >> res;
    }

    return(0);
}

int Accountdb::saveEntry(Account *entry){

    int rc;
    char *iErrMsg = 0;

    string sql = "INSERT INTO Accounts (ID,NAME,EMAIL,AGE) " \
        "VALUES (" + to_string(entry->GetAccountID()) + ", '" + entry->GetAccountName() + "', '" \
        + entry->GetEmail() + "', " + to_string(entry->GetAge()) + " );";

    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), callback, 0, &iErrMsg);

    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
    } else {
      fprintf(stdout, "Records created successfully\n");
    }

    return(0);
}