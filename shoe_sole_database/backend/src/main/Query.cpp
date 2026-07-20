#include "../include/Query.hpp"
#include "../include/Data.hpp"

#include <iostream>
#include <string>
#include <print>
#include <cstdint>
#include <libpq-fe.h>
#include <format>
#include <limits>

PGresult* Query::executeQuery(PGconn* connection, const Filter& filter) {
    std::vector<std::string> parameters;
    std::vector<const char*> values;
    std::string sql = buildQuery(filter, parameters);

    //std::cout << "SQL STRING: " << sql << std::endl;

    for(const auto& p : parameters) {
        values.push_back(p.c_str());
    }

    PGresult* result = PQexecParams(
        connection,
        sql.c_str(),
        values.size(),
        nullptr,
        values.data(),
        nullptr,
        nullptr,
        0
    );

    if(PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::println(stderr, "{}", PQerrorMessage(connection));

        PQclear(result);
        return nullptr;
    }

    return result;
}

std::string Query::buildQuery(const Filter& filter, std::vector<std::string>& parameters) {
    if(!filter.brands.empty()) {
        // sqlQuery is base sql query
        sqlQuery += std::format(" AND shoe_brand_name IN (");

        for(const auto& brand : filter.brands) {
            parameters.push_back(brand);

            sqlQuery += std::format("${}, ", parameters.size());
        }

        // remove the ',' at the end of the query 
        sqlQuery.erase(sqlQuery.size() - 2);
        sqlQuery += ")";
    }

    if(!filter.models.empty()) {
        sqlQuery += std::format(" AND shoe_brand_model IN (");

        for(const auto& model : filter.models) {
            parameters.push_back(model);

            sqlQuery += std::format("${}, ", parameters.size());
        }

        sqlQuery.erase(sqlQuery.size() - 2);
        sqlQuery += ")";
    }

    if(filter.year != 0) {
        parameters.push_back(std::to_string(filter.year));
        sqlQuery += std::format(" AND shoe_brand_release_year {} ${}", filter.yearOperationSign, parameters.size());
    }

    bool hasPatternFilter = false;
    if(!filter.patterns.empty()) {
        sqlQuery += " AND shoe_sole_pattern IN (";

        for(const auto& pattern : filter.patterns) {
            parameters.push_back(pattern);

            sqlQuery += std::format("${}, ", parameters.size());
        }

        sqlQuery.erase(sqlQuery.size() - 2);
        sqlQuery += ")";

        hasPatternFilter = true;
    }   

    sqlQuery += R"( GROUP BY shoe_brand_name, shoe_brand_model, shoe_brand_release_year,
        shoe_sole_img_path)";

    if(hasPatternFilter && filter.patternMatch == "ALL") {
        sqlQuery += std::format(" HAVING COUNT(DISTINCT shoe_sole_pattern) = {}", filter.patterns.size());
    }

    return sqlQuery;
}

void Query::printQuery(std::size_t rows, PGresult*& result) {
    if(rows == 0) {
        std::println("No shoes found!");
        return;
    }

    std::println("Found {} entries:", rows);
    for(std::size_t i{}; i < rows; i++) {
        std::println("----------------------------");

        // cast fieldValues class into an unsigned 8 bit integer 
        std::println("Brand: {}", PQgetvalue(result, i, indexHelper(fieldValues::brandField)));
        std::println("Model: {}", PQgetvalue(result, i, indexHelper(fieldValues::modelField)));
        std::println("Year: {}", PQgetvalue(result, i, indexHelper(fieldValues::yearField)));
        std::println("Image: {}", PQgetvalue(result, i, indexHelper(fieldValues::imageField)));
        std::println("Pattern: {}", PQgetvalue(result, i, indexHelper(fieldValues::patternField)));
        std::println("----------------------------");
    }
}