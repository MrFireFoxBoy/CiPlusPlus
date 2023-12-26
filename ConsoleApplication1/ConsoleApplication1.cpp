#include <iostream>
#include "sqlite3.h"

// Функция обратного вызова для вывода результатов запроса
static int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    // Подключение к базе данных
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        std::cout << "Error opening the database: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }
    else {
        std::cout << "The database has been opened successfully" << std::endl;
    }

    // Создание таблицы, если она не существует
    std::string createTableQuery = "CREATE TABLE IF NOT EXISTS MyTable (Name TEXT, Age INT);";
    rc = sqlite3_exec(db, createTableQuery.c_str(), NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error creating the table: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 0;
    }
    else {
        std::cout << "The table was created successfully" << std::endl;
    }

    // Добавление данных в таблицу
    std::string insertQuery = "INSERT INTO MyTable (Name, Age) VALUES ('John Doe', 25);";
    rc = sqlite3_exec(db, insertQuery.c_str(), NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error when adding data to the table: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 0;
    }
    else {
        std::cout << "The data has been added successfully" << std::endl;
    }

    // Выполнение запроса на выборку данных
    std::string selectQuery = "SELECT * FROM MyTable;";
    rc = sqlite3_exec(db, selectQuery.c_str(), callback, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error when executing a data selection request: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 0;
    }

    // Закрытие соединения с базой данных
    sqlite3_close(db);

    return 0;
}