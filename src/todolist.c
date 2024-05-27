#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName);

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
        rv = sqlite3_exec(db, "CREATE TABLE \"notes\" (\"id\" INTEGER NOT NULL UNIQUE, \"note\" TEXT NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT));", 0, 0, &err_msg);
        if (rv != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return -1;
        }
    }

    if (argc == 1) // View mode
    {
        printf("Notes in the list:\n");
        char *insert_stm = sqlite3_mprintf("SELECT id, note FROM notes");
        rv = sqlite3_exec(db, insert_stm, callback, 0, &err_msg);
        if (rv != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return -1;
        }
    }
    else if (argc == 2)
    {
        if (atoi(argv[1])) // Delete mode
        {
            return 0;
        }
        else // Insert mod
        {
            char *insert_stm = sqlite3_mprintf("INSERT INTO notes (note) VALUES ('%q');", argv[1]);
            char *err_msg = 0;
            int rc = sqlite3_exec(db, insert_stm, 0, 0, &err_msg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", err_msg);
                sqlite3_free(err_msg);
            } else {
                printf("Note added successfully.\n");
            }

            sqlite3_free(insert_stm);
        }
    }

    sqlite3_close(db);
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    printf("%s. %s\n", argv[0], argv[1]);
    return 0;
}