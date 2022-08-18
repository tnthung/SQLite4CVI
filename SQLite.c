#include <stdio.h>
#include <stdlib.h>
#include "SQLite.h"


int openDB(
  SqlDB       *db, 
  char        *basePath, 
  char        *dbName, 
  SqlCallback  callback)
{
  int  hasPath, result;
  char tmpPath[256];

  if (db->inited)
    return 0;

  hasPath = basePath != NULL && dbName != NULL;

  if (hasPath) 
    sprintf(
      db->path, 
      "%s/%s\0", 
      basePath, 
      dbName);

  result = sqlite3_open(
    hasPath ? db->path : 0, 
    &(db->db));

  if (result != SQLITE_OK && hasPath)
  {
    sprintf(
      tmpPath, 
      "mkdir \"%s\"\0", 
      basePath);

    system(tmpPath);

    result = sqlite3_open(
      db->path, 
      &(db->db));
  }

  if (result == SQLITE_OK) {
    db->inited   = 1;
    db->callback = callback;
  }

  return result;
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
