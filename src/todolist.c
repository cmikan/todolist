#include <sqlite3.h>

int main()
{
    sqlite3 *db;

    sqlite3_open("db.sqlite", &db);
    return 0;
}