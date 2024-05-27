#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        fprintf(stderr, "Too many arguments.\n");
        return -1;
    }

    sqlite3 *db;
    char *err_msg = 0;
    int rv;
    const char *db_filename = "todolist.db";

// Check if db already exist
    int init_db = 0;
    if (access(db_filename, F_OK) == -1)
    {
        init_db = 1;
    }

    rv = sqlite3_open("todolist.db", &db);

    if (rv != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    if (init_db)
    {
        rv = sqlite3_exec(db, "CREATE TABLE \"\" (\"id\" INTEGER NOT NULL UNIQUE, \"note\" TEXT NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT));", 0, 0, &err_msg);
        if (rv != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 1;
        }
    }

    sqlite3_close(db);
    return 0;
}