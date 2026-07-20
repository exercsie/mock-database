#pragma once

#include "Data.hpp"

#include <libpq-fe.h>

class JSONFile { 
public:
    static Filter loadFilter(const std::string& fileName);
    void exportResults(std::size_t rows, PGresult*& result);
};