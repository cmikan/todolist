#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sqlite_utils.h"

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        fprintf(stderr, "Too many arguments.\n");
        return -1;
    }

    sqlite3 *db;
    const char *db_filename = "todolist.db";

// Check if db already exist
    if (init_db(&db, db_filename) != 0)
    {
        return -1;
    }
    
    callback_p callback_function;
    char *insert_stm;
    char *callback_message;

    if (argc == 1) // View mode
    {
        printf("Notes in the list:\n");
        insert_stm = sqlite3_mprintf("SELECT id, note FROM notes");
        callback_function = &callback;
        callback_message = "";
    }
    else if (argc == 2)
    {
        if (atoi(argv[1])) // Delete mode
        {
            insert_stm = sqlite3_mprintf("DELETE FROM notes WHERE id = %q", argv[1]);
            callback_function = 0;
            callback_message = "Notes successfully deleted\n";
        }
        else // Insert mod
        {
            insert_stm = sqlite3_mprintf("INSERT INTO notes (note) VALUES ('%q');", argv[1]);
            callback_function = 0;
            callback_message = "Notes added successfully\n";
        }
    }

    if (process_stm(db, insert_stm, callback_function, callback_message) != 0)
    {
        return -1;
    }

    sqlite3_close(db);
    return 0;
}