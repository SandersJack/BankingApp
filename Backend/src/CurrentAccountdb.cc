#include "CurrentAccountdb.hh"
#include "Commondb.hh"
#include <cstring>

struct currentAccountRecord{
    vector<int> ID;
    vector<double> Value;
    vector<double> IntrestRate;
};

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
    cout << "**    "<< argv[0] <<"    **      "<< argv[1] << "     **     "<<argv[3]<<"      **" << endl;
    printf("\n");
    return(0);
}

static int select_callback(void *p_data, int num_fields, char **argv, char **szColName)
{
    currentAccountRecord* aRecord = static_cast<currentAccountRecord*>(p_data);
    for(int i = 0; i < num_fields; i++)
        {
            if (strcmp(szColName[i], "ID") == 0)
            {
                aRecord->ID.push_back(atoi(argv[i]));
            } 
            else if (strcmp(szColName[i], "VALUE") == 0)
            {
                aRecord->Value.push_back(atof(argv[i]));
            } 
            else if (strcmp(szColName[i], "INTREST") == 0)
            {
                aRecord->IntrestRate.push_back(atof(argv[i]));
            }
        }
    return 0;
}

CurrentAccountdb::CurrentAccountdb(): Vdb()
{
    fCommondb = Commondb::GetInstance();
}

CurrentAccountdb *CurrentAccountdb::fInstance = nullptr;

CurrentAccountdb *CurrentAccountdb::GetInstance() {
  if(!fInstance)
    fInstance = new CurrentAccountdb();
  return fInstance;
}

int CurrentAccountdb::createTable(){
    string sql;
    int rc;
    char *zErrMsg = 0;

    // Create SQL Table //

    sql = "CREATE TABLE CurrentAccounts(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "VALUE          FLOAT    NOT NULL," \
        "INTRESTRATE    FLOAT    NOT NULL);";

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

int CurrentAccountdb::printEntry(int id) {
    char *iErrMsg = 0;
    const char* data = "";
    int rc;
    int res;

    string sql = "SELECT * from Accounts WHERE ID=" + to_string(id);
    cout << "*********************************************************************" << endl;
    cout << "**      ID       **      Value     **     IntrestRate              **" << endl;
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

int CurrentAccountdb::saveEntry(CurrentAccount *entry){

    int rc;
    char *iErrMsg = 0;

    string sql = "INSERT INTO CurrentAccounts (ID,VALUE,INTRESTRATE) " \
        "VALUES (" + to_string(entry->GetAccountID()) + ", '" + to_string(entry->GetValue()) + "', '" \
        + to_string(entry->GetIntrestrate()) + "' );";

    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), callback, 0, &iErrMsg);

    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
    } else {
      fprintf(stdout, "Records created successfully\n");
    }

    return(0);
}

int CurrentAccountdb::deleteAccount(int id){

    int rc;
    int res;    
    char *iErrMsg = 0;

    string sql = "DELETE FROM CurrentAccounts WHERE ID="+ to_string(id);

    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), callback, 0, &iErrMsg);
    
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
    } else {
      fprintf(stdout, "CurrentAccount deleted successfully \n");
    }
    cin >> res;
    return(0);
}

CurrentAccount *CurrentAccountdb::getCurrentAccount(int id){
    int rc;
    char *iErrMsg = 0;

    CurrentAccount *outAccount = new CurrentAccount();

    currentAccountRecord record;
    string sql = "SELECT * from Accounts WHERE ID=" + to_string(id);


    //rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), select_callback, &record, &iErrMsg);
    rc = executeSQLQuery(fCommondb->GetDatabase(),sql.c_str(), select_callback, &record);

    if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    outAccount->SetAccountID(record.ID[0]);
    outAccount->SetValue(record.Value[0]);
    outAccount->SetIntrestRate(record.IntrestRate[0]);
    return outAccount; //2678857
}