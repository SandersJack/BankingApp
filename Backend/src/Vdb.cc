#include "Vdb.hh"

Vdb::Vdb()
{
}

void Vdb::printColumnValue(sqlite3_stmt* stmt, int col) {

  int colType = sqlite3_column_type(stmt, col);

  switch(colType) {

    case SQLITE_INTEGER:
         printf("  %3d   ", sqlite3_column_int(stmt, col));
         break;

    case SQLITE_FLOAT:
         printf("  %5.2f", sqlite3_column_double(stmt, col));
         break;

    case SQLITE_TEXT:
         printf("  %-5s", sqlite3_column_text(stmt, col));
         break;

    case SQLITE_NULL:
         printf("  null");
         break;

    case SQLITE_BLOB:
         printf("  blob");
         break;     
    }

}

int Vdb::executeSQLQuery(sqlite3 *db,               
                            const char *zSql, int (*function)(void *, int , char **, char **), void *p_data){
    

     sqlite3_stmt *stmt;
     if (sqlite3_prepare_v2(db, zSql, -1, &stmt, NULL)) {
          printf("Error executing sql statement\n");
     }

     int stat = sqlite3_step(stmt);
     if(stat == SQLITE_ROW){
          while (stat != SQLITE_DONE) {
               char *colName[sqlite3_data_count(stmt)];
               char *argv[sqlite3_data_count(stmt)];
               for (int col=0; col<sqlite3_data_count(stmt); col++) {
                    //printColumnValue(stmt, col);
                    colName[col] = (char *)sqlite3_column_name(stmt,col);
                    argv[col] = (char *)sqlite3_column_text(stmt, col);
               }
               function(p_data, sqlite3_data_count(stmt), argv, colName);
               stat = sqlite3_step(stmt);
          }
     } else {
          std::cout << "RESULT NOT FOUND" << std::endl;
          return 420;
     }

    return sqlite3_finalize(stmt);
 
}