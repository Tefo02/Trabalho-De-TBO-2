#pragma once

#include "Dictionary.hpp"
#include "Tokenizer.hpp"
#include <iostream>
#include <stdexcept>
#include <chrono> 

class Desafio5 {
public:
    Desafio5(const std::string& dictionaryFilePath, const std::string& text)
        : dictionary(dictionaryFilePath), tokenizer(text) {}

    void run() {
        if (!dictionary.loadFromFile()) {
            throw std::runtime_error("Failed to load dictionary from file.");
        }

        std::vector<std::string> tokens = tokenizer.tokenize();

        std::cout << "== Verificação com HashTable ==\n";
        auto startHash = std::chrono::high_resolution_clock::now();
        for (const auto& token : tokens) {
            if (!dictionary.containsInHashTable(token)) {
                std::cout << "[HashTable] Palavra não encontrada: " << token << std::endl;
            }
        }
        auto endHash = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> durationHash = endHash - startHash;
        std::cout << "Tempo (HashTable): " << durationHash.count() << " ms\n";

        std::cout << "\n== Verificação com Vector ==\n";
        auto startVector = std::chrono::high_resolution_clock::now();
        for (const auto& token : tokens) {
            if (!dictionary.containsInVector(token)) {
                std::cout << "[Vector] Palavra não encontrada: " << token << std::endl;
            }
        }
        auto endVector = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> durationVector = endVector - startVector;
        std::cout << "Tempo (Vector): " << durationVector.count() << " ms\n";

        std::cout << "\n== Verificação com BKTree ==\n";
        auto startBKTree = std::chrono::high_resolution_clock::now();
        for (const auto& token : tokens) {
            if (!dictionary.containsInBKTree(token)) {
                std::cout << "[BKTree] Palavra não encontrada: " << token << std::endl;
            }
        }
        auto endBKTree = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> durationBKTree = endBKTree - startBKTree;
        std::cout << "Tempo (BKTree): " << durationBKTree.count() << " ms\n";
    }

private:
    Dictionary dictionary;
    Tokenizer tokenizer;
};
