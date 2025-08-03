#include "../include/Dictionary.hpp"
#include "../include/MergeSort.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>

Dictionary::Dictionary(const std::string& filepath) : filepath(filepath), hashTable(2000000){}

bool Dictionary::loadFromFile() {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false; // Erro ao abrir o arquivo
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string cleanedLine = cleanLine(line);
        if (!cleanedLine.empty()) {
            hashTable.insert(cleanedLine, true);
            vector.push_back(cleanedLine);
            bkTree.add(cleanedLine); 
        }
    }

    std::vector<std::string> specialWords = {
        "a", "à", "á", "e", "é", "o", "ó", "u",
        "ao", "aos", "aquela", "aquelas", "aquele", "aqueles",
        "aqui", "aí", "ali", "isso"
    };

    for(const auto& word : specialWords) {
        hashTable.insert(word, true);
        vector.push_back(word);
        bkTree.add(word);
    }

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(vector, 0, vector.size() - 1); // Ordena o vetor após carregar os dados
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tempo (Merge Sort): " << duration.count() << " ms\n";

    file.close();
    return true; 
}

bool Dictionary::containsInHashTable(const std::string& key) const {
    bool value;
    return hashTable.find(key, value);
}

bool Dictionary::containsInVector(const std::string& key) const {
    return binarySearch(vector, key) != -1; // Usa busca binária para verificar se a palavra está no vetor
}

std::string Dictionary::cleanLine(const std::string& line) const {
    std::string cleaned = line;

    size_t slash = cleaned.find('/');
    if (slash != std::string::npos)
        cleaned = cleaned.substr(0, slash);

    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower); 

    return cleaned;
}

bool Dictionary::containsInBKTree(const std::string& key, size_t distance) const {
    std::vector<std::string> results = bkTree.search(key, distance);
    return !results.empty(); 
}