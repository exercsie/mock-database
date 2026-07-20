#pragma once

#include <libpq-fe.h>

class Database {
public:
    PGconn* connectToDatabase();


private:
    
};