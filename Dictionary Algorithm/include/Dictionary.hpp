#pragma once

#include "HashTable.hpp"
#include "BinarySearch.hpp"
#include "MergeSort.hpp"
#include "BKTree.hpp"
#include <vector>
#include <algorithm>

class Dictionary {
public:
    Dictionary(const std::string& filepath);

    bool loadFromFile();
    bool containsInHashTable(const std::string& key) const;
    bool containsInVector(const std::string& key) const;
    bool containsInBKTree(const std::string& key, size_t distance) const;

private:

    HashTable<std::string, bool> hashTable;
    std::vector<std::string> vector;
    BKTree bkTree;
    std::string cleanLine(const std::string& line) const;
    std::string filepath;
};
