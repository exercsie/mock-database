#pragma once

#include "Data.hpp"

#include <iostream>
#include <string>
#include <libpq-fe.h>
#include <vector>

class Query { 
public:
    PGresult* executeQuery(PGconn* connection, const Filter& filter);

    // rows has type size_t as you cannot have negative rows
    void printQuery(std::size_t rows, PGresult*& result);

    static constexpr uint8_t indexHelper(fieldValues field) {
        return static_cast<uint8_t>(field);
    }
    
private:
    // base sql query that will be appened on by received json file
    std::string sqlQuery{ R"(
            SELECT shoe_brand_name, shoe_brand_model, shoe_brand_release_year,
            shoe_sole_img_path, 
            STRING_AGG(shoe_sole_pattern, ',') AS patterns
            FROM shoe_sole_imgs
            JOIN shoes USING(shoe_id) 
            JOIN ml_shoe_sole_patterns USING(shoe_sole_img_id)
            
            WHERE 1=1
        )"
    };

    std::string buildQuery(const Filter& filter, std::vector<std::string>& parameters);

};
