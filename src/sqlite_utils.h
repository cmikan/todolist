#ifndef SQLITE_UTILS_H_
#define SQLITE_UTILS_H_

typedef int (*callback_p)(void *, int, char **, char **);

int callback(void *NotUsed, int argc, char **argv, char **azColName);
int init_db(sqlite3 **db, const char *db_name);
int process_stm(sqlite3 *db, char *insert_stm, callback_p callback_function, char *callback_message);

#endif // SQLITE_UTILS_H_