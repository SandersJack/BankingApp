#include "Accountdb.hh"

Accountdb::Accountdb()
{
    
}

Accountdb *Accountdb::fInstance = nullptr;

Accountdb *Accountdb::GetInstance() {
  if(!fInstance)
    fInstance = new Accountdb();
  return fInstance;
}
