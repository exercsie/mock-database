#pragma once

#include <iostream>
#include <string>
#include <vector>

inline constexpr char dbName[] = "dbname=shoe_solesdb user=postgres";
inline constexpr char imgPath[] = "../../images";

enum class fieldValues : std::uint8_t {
    brandField,
    modelField,
    yearField,
    imageField,
    patternField
};

struct Filter {
    // json file could include multiple brands
    std::vector<std::string> brands;
    std::vector<std::string> models;
    std::vector<std::string> patterns;

    // json file specifies to match ALL or ANY pattern
    std::string patternMatch;

    // json file has year operation: '<', '==', '>', '!=', etc.
    std::string yearOperationSign;

    // unsigned 16 bit integer is used as year will always be positive and 4 chars long
    std::uint16_t year{};   
};
