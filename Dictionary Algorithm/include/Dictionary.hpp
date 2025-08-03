#pragma once

#include "HashTable.hpp"
#include "BinarySearch.hpp"
#include <vector>
#include <algorithm>

class Dictionary {
public:
    Dictionary(const std::string& filepath);

    bool loadFromFile();
    bool containsInHashTable(const std::string& key) const;
    bool containsInVector(const std::string& key) const;

private:

    HashTable<std::string, bool> hashTable;
    std::vector<std::string> vector;
    std::string cleanLine(const std::string& line) const;
    std::string filepath;
};
