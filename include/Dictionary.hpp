#pragma once

#include "HashTable.hpp"

class Dictionary {
public:
    bool loadFromFile(const std::string& filepath);
    bool contains(const std::string& key) const;
private:
    HashTable<std::string, bool> data;
    std::string cleanLine(const std::string& line) const;
};
