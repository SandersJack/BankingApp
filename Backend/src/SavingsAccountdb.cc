#include "SavingsAccountdb.hh"
#include "Commondb.hh"
#include <cstring>

struct SavingsAccountRecord{
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
    cout << "** Savings Account  **      "<< argv[1] << "             **     "<<argv[2]<<"             **" << endl;
    printf("\n");
    return(0);
}

static int select_callback(void *p_data, int num_fields, char **argv, char **szColName)
{
    SavingsAccountRecord* aRecord = static_cast<SavingsAccountRecord*>(p_data);
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

SavingsAccountdb::SavingsAccountdb(): Vdb()
{
    fCommondb = Commondb::GetInstance();
}

SavingsAccountdb *SavingsAccountdb::fInstance = nullptr;

SavingsAccountdb *SavingsAccountdb::GetInstance() {
  if(!fInstance)
    fInstance = new SavingsAccountdb();
  return fInstance;
}

int SavingsAccountdb::createTable(){
    string sql;
    int rc;
    char *zErrMsg = 0;

    // Create SQL Table //

    sql = "CREATE TABLE SavingsAccounts(" \
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

int SavingsAccountdb::printEntry(int id) {
    char *iErrMsg = 0;
    const char* data = "";
    int rc;
    int res;

    string sql = "SELECT * from SavingsAccounts WHERE ID=" + to_string(id);
    //rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), tablecallback, (void*)data, &iErrMsg);
    rc = executeSQLQuery(fCommondb->GetDatabase(),sql.c_str(), tablecallback, 0);
    if(rc == 420){
        return 0;
    } else {
        return 1;
    }
}

int SavingsAccountdb::saveEntry(SavingsAccount *entry){

    int rc;
    char *iErrMsg = 0;

    string sql = "INSERT INTO SavingsAccounts (ID,VALUE,INTRESTRATE) " \
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

int SavingsAccountdb::deleteEntry(int id){

    int rc;
    int res;    
    char *iErrMsg = 0;

    cout << to_string(id) << endl;
    string sql = "DELETE FROM SavingsAccounts WHERE ID="+ to_string(id);

    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), callback, 0, &iErrMsg);
    
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
    } else {
      fprintf(stdout, "SavingsAccount deleted successfully \n");
    }
    cin >> res;
    return(0);
}

SavingsAccount *SavingsAccountdb::getSavingsAccount(int id){
    int rc;
    char *iErrMsg = 0;

    SavingsAccount *outAccount = new SavingsAccount();

    SavingsAccountRecord record;
    string sql = "SELECT * from SavingsAccounts WHERE ID=" + to_string(id);


    //rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), select_callback, &record, &iErrMsg);
    rc = executeSQLQuery(fCommondb->GetDatabase(),sql.c_str(), select_callback, &record);

    if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
      return nullptr;
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    outAccount->SetProductName("SavingsAccounts");
    outAccount->SetAccountID(record.ID[0]);
    outAccount->SetValue(record.Value[0]);
    outAccount->SetIntrestRate(record.IntrestRate[0]);

    return outAccount; //2678857
}