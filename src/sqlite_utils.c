#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include "sqlite_utils.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    printf("%s. %s\n", argv[0], argv[1]);
    return 0;
}

int init_db(sqlite3 **db, const char *db_name)
{
    int rv;
    int init_db = 0;
    char *err_msg = 0;

    if (access(db_name, F_OK) == -1)
    {
        init_db = 1;
    }

    rv = sqlite3_open(db_name, db);

    if (rv != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return -1;
    }

    if (init_db)
    {
        rv = sqlite3_exec(*db, "CREATE TABLE \"notes\" (\"id\" INTEGER NOT NULL UNIQUE, \"note\" TEXT NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT));", 0, 0, &err_msg);
        if (rv != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(*db);
            return -1;
        }
    }
    return 0;
}

int process_stm(sqlite3 *db, char *insert_stm, callback_p callback_function, char *callback_message)
{
    char *err_msg = 0;
    int rv;
    
    rv = sqlite3_exec(db, insert_stm, callback_function, 0, &err_msg);
    if (rv == SQLITE_OK)
    {
        printf("%s", callback_message);
    }
    else
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return -1;
    }

    return 0;
}