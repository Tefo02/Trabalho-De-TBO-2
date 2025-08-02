#include "../include/Dictionary.hpp"
#include <fstream>
#include <sstream>

Dictionary::Dictionary(const std::string& filepath) : filepath(filepath) {}

bool Dictionary::loadFromFileToHashTable() {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false; // Erro ao abrir o arquivo
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string cleanedLine = cleanLine(line);
        if (!cleanedLine.empty()) {
            hashTable.insert(cleanedLine, true); // Insera a palavra no dicionário
        }
    }

    file.close();
    return true; 
}

bool Dictionary::loadFromFileToVector() {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false; // Erro ao abrir o arquivo
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string cleanedLine = cleanLine(line);
        if (!cleanedLine.empty()) {
            vector.push_back(cleanedLine); // Insera a palavra no dicionário
        }
    }

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

    return cleaned;
}