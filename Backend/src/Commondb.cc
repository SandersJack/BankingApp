#include "Commondb.hh"

Commondb::Commondb()
{

}

Commondb *Commondb::fInstance = nullptr;

Commondb *Commondb::GetInstance() {
  if(!fInstance)
    fInstance = new Commondb();
  return fInstance;
}

int Commondb::OpenDatabase(string name){

  if (!fDatabase){
    int rc;

    rc = sqlite3_open(name.c_str(), &fDatabase);

    if(rc){
      fprintf(stderr, "Cant open database: %s\n", sqlite3_errmsg(fDatabase));
      return 0;
    } else {
      fprintf(stderr, "Opened database successfully\n");
    }

  } else {
    cout << "[Commondb] Database is already open." << endl; 
    return 10;
  }

  return 1;
}