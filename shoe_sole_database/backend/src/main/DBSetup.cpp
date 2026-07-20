#include "../include/Data.hpp"
#include "../include/DBSetup.hpp"

#include <libpq-fe.h>
#include <print>
#include <string>

PGconn* Database::connectToDatabase() {
    
    // dbName is located in Data.h
    PGconn* connect = PQconnectdb(dbName);

    if(PQstatus(connect) != CONNECTION_OK) {
        std::println(stderr, "Connection failed! {}", PQerrorMessage(connect));

        PQfinish(connect);
        exit(1);
    }

    std::println("Connection to database successful!");
    return connect;
}