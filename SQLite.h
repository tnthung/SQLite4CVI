#ifndef INLCUDED_SQLITE3_H
  #define INLCUDED_SQLITE3_H
  #include "sqlite3.h"
#endif


typedef int (* SqlCallback)(
  void*,      // the fourth argument of sqlite3_exec() will be passed here 
  int,        // number of columns in the result set
  void**,     // array of strings representing fields in the row
  void**);    // array of strings representing column names


typedef struct SqlDB
{
  sqlite3 *db;          // the database handle
  SqlCallback callback; // the callback function

  int  inited;          // 1 if the database is open
  char path[256];       // the path to the database file

} SqlDB;


/* 
  Opens a database file
    If one of basePath and dbName is NULL, the database will be opened 
    as an in-memory database. If both are not NULL, it will try to open
    with the path: basePath\\dbName. If the database is opened successfully,
    the function returns 0. Otherwise, it returns the error code returned
    by sqlite3_open().
*/
int openDB(
  SqlDB       *db, 
  char        *basePath, 
  char        *dbName, 
  SqlCallback  callback);


/* 
  Closes a database file
    If the database is not open, it will return 0. Otherwise, it will
    close the database and return 0.
*/
int closeDB(SqlDB *db);


/* 
  Executes a SQL statement
    If the database is not open, it will return -1. Otherwise, it will
    execute the SQL statement and pass the result to the specified
    call back. If the call back is NULL, it will use the default call
    back of the database. Finally, it will return the result of the
    sqlite3_exec() function.
*/
int queryDB(
  SqlDB       *db, 
  char        *query,
  SqlCallback  callback);
