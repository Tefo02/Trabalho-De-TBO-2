#include "../include/Dictionary.hpp"
#include <fstream>
#include <sstream>

bool Dictionary::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false; // Erro ao abrir o arquivo
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string cleanedLine = cleanLine(line);
        if (!cleanedLine.empty()) {
            data.insert(cleanedLine, true); // Insera a palavra no dicionário
        }
    }

    file.close();
    return true; 
}

bool Dictionary::contains(const std::string& key) const {
    bool value;
    return data.find(key, value);
}

std::string Dictionary::cleanLine(const std::string& line) const {
    std::string cleaned = line;

    size_t slash = cleaned.find('/');
    if (slash != std::string::npos)
        cleaned = cleaned.substr(0, slash);

    return cleaned;
}