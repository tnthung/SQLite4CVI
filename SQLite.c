#include <stdio.h>
#include <stdlib.h>
#include "SQLite.h"


int openDB(
  SqlDB       *db, 
  char        *basePath, 
  char        *dbName, 
  SqlCallback  callback)
{
  int  hasPath;
  char tmpPath[256];

  if (db->inited)
    return 0;

  hasPath = basePath != NULL && dbName != NULL;

  if (hasPath) 
    sprintf(
      db->path, 
      "%s\\%s", 
      basePath, 
      dbName);

  return sqlite3_open(hasPath ? db->path : 0, &(db->db));
}


int closeDB(SqlDB *db)
{
  if (!db->inited)
    return 0;

  sqlite3_close(db->db);
  db->inited = 0;
  return 0;
}


int queryDB(
  SqlDB       *db, 
  char        *query,
  SqlCallback  callback)
{
  if (!db->inited)
    return -1;

  return sqlite3_exec(
    db->db, query,
    callback
      ? callback
      : db->callback,
    0, 0);
}
