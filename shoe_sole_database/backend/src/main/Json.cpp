#include "../include/Json.hpp"
#include "../include/Query.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <print>

Filter JSONFile::loadFilter(const std::string& fileName) {
    nlohmann::json input;
    Filter filter;

    //std::cout << fileName << std::endl;

    std::ifstream file(fileName);

    if(!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file.");
    }

    file >> input;

    filter.brands = input.value("brands", std::vector<std::string>{});
    filter.models = input.value("models", std::vector<std::string>{});
    filter.yearOperationSign = input.value("yearOperationSign", "=");
    filter.year = input.value("year", 0);
    filter.patterns = input.value("patterns", std::vector<std::string>{});
    filter.patternMatch = input.value("patternMatch", "ANY");

    return filter;
}

void JSONFile::exportResults(std::size_t rows, PGresult*& result) {
    nlohmann::json output;
    Query q;

    output["results"] = nlohmann::json::array();

    for(std::size_t i{}; i < rows; ++i) {
        nlohmann::json shoe;
        shoe["brands"].push_back(PQgetvalue(result, i, q.indexHelper(fieldValues::brandField)));
        shoe["models"].push_back(PQgetvalue(result, i, q.indexHelper(fieldValues::modelField)));
        shoe["year"] = std::stoi(PQgetvalue(result, i, q.indexHelper(fieldValues::yearField)));
        shoe["patterns"].push_back(PQgetvalue(result, i, q.indexHelper(fieldValues::patternField)));
        output["results"].push_back(shoe);
    }

    std::string path = "/home/xxxx/Documents/sql/shoe_sole_database/JSON/Data-Output.json";

    std::ofstream file(path);

    if(!file.is_open()) {
        std::cout << "Failed to open" << path;
    }

    file << output.dump(4);

    file.close();
}