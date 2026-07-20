#include "../include/Data.hpp"
#include "../include/Directory.hpp"
#include "../include/DBSetup.hpp"
#include "../include/Query.hpp"
#include "../include/Json.hpp"

#include <iostream>
#include <libpq-fe.h>
#include <string>
#include <print>
#include <filesystem>

int main() {
    Database db;
    Query q;
    JSONFile json;

    Filter filter = JSONFile::loadFilter("/home/xxxx/Documents/sql/shoe_sole_database/JSON/Data-Filter-Input.json");

    // connect to database
    PGconn* databaseConnection = db.connectToDatabase();

    /*if(d.createIMGPath()) {
        std::println(stderr, "Failed to create img directory");
    }*/

    PGresult* result = q.executeQuery(databaseConnection, filter);
    std::size_t rows = PQntuples(result);
    //q.printQuery(rows, result);

    json.exportResults(rows, result);

    PQclear(result);
    PQfinish(databaseConnection);
}
