# To-do list
A simple CLI To-do List written in C for Linux.

## Compilation
Simply use the Makefile
```sh
make
./todolist
```
An internet connexion is required to download sqlite3 the first time.

## Usage
To add an element to the list:
```sh
./todolist "A text to add"
./todolist "A second text to add"
```

You can then see the content of the list with:
```sh
./todolist
```

Finally you can delete an entry by entering it's number:
```sh
./todolist 2
```
