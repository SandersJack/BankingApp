#include "Accountdb.hh"
#include "Commondb.hh"
#include <cstring>

struct AccountRecord{
    vector<int> ID;
    vector<string> Name;
    vector<string> Email;
    vector<int> DOB;
    vector<string> Password;
    vector<string> Question;
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
    cout << "**    "<< argv[0] <<"    **      "<< argv[1] << "     **     *****      **     "<<argv[3]<<"      **" << endl;
    printf("\n");
    return(0);
}

int select_callback(void *p_data, int num_fields, char **argv, char **szColName)
{
    AccountRecord* aRecord = static_cast<AccountRecord*>(p_data);
    for(int i = 0; i < num_fields; i++)
        {
            if (strcmp(szColName[i], "ID") == 0)
            {
                aRecord->ID.push_back(atoi(argv[i]));
            } 
            else if (strcmp(szColName[i], "NAME") == 0)
            {
                aRecord->Name.push_back(argv[i]);
            } 
            else if (strcmp(szColName[i], "EMAIL") == 0)
            {
                aRecord->Email.push_back(argv[i]);
            }
            else if (strcmp(szColName[i], "DOB") == 0)
            {
                aRecord->DOB.push_back(atoi(argv[i]));
            }
            else if (strcmp(szColName[i], "PASSWORD") == 0)
            {
                aRecord->Password.push_back(argv[i]);
            }
            else if (strcmp(szColName[i], "QUESTION") == 0)
            {
                aRecord->Question.push_back(argv[i]);
            }
        }
    return 0;
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
        "DOB            INT     NOT NULL," \
        "PASSWORD       TEXT    NOT NULL,"
        "QUESTION       TEXT    NOT NULL);";

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
    cout << "**      ID       **      Name     **     Email      **     DOB     **" << endl;
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
    cout << "**      ID       **      Name     **     Email      **     DOB     **" << endl;
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

    string sql = "INSERT INTO Accounts (ID,NAME,EMAIL,DOB,PASSWORD,QUESTION) " \
        "VALUES (" + to_string(entry->GetAccountID()) + ", '" + entry->GetAccountName() + "', '" \
        + entry->GetEmail() + "', " + to_string(entry->GetDOB()) + ", '" + entry->GetPassword() 
        + "', '" + entry->GetQuestion() + "' );";

    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), callback, 0, &iErrMsg);

    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
    } else {
      fprintf(stdout, "Records created successfully\n");
    }

    return(0);
}

int Accountdb::deleteAccount(int id){

    int rc;
    int res;    
    char *iErrMsg = 0;

    string sql = "DELETE FROM Accounts WHERE ID="+ to_string(id);

    rc = sqlite3_exec(fCommondb->GetDatabase(), sql.c_str(), callback, 0, &iErrMsg);
    
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", iErrMsg);
      sqlite3_free(iErrMsg);
    } else {
      fprintf(stdout, "Account deleted successfully\n");
    }
    cin >> res;
    return(0);
}

Account *Accountdb::getAccount(int id){
    int rc;
    char *iErrMsg = 0;

    Account *outAccount = new Account();

    AccountRecord record;
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
    outAccount->SetName(record.Name[0]);
    outAccount->SetEmail(record.Email[0]);
    outAccount->SetDOB(record.DOB[0]);
    outAccount->SetPassword(record.Password[0]);
    outAccount->SetQuestion(record.Question[0]);
    return outAccount; //2678857
}