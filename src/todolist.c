#include <sqlite3.h>

int main()
{
    sqlite3 *db;

    sqlite3_open("todolist.db", &db);
    return 0;
}