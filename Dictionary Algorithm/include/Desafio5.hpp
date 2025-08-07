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

    std::vector<std::string> run() {
        if (!dictionary.loadFromFile()) {
            throw std::runtime_error("Failed to load dictionary from file.");
        }

        std::string inputText;
        std::cout << "Digite o texto a ser verificado: ";
        std::getline(std::cin, inputText);
        tokenizer.setText(inputText);

        std::vector<std::string> tokens = tokenizer.tokenize();

        std::vector<std::string> wordsNotFound;

        std::cout << "== Verificação com HashTable ==\n";
        auto startHash = std::chrono::high_resolution_clock::now();
        for (const auto& token : tokens) {
            if (!dictionary.containsInHashTable(token)) {
                std::cout << "[HashTable] Palavra não encontrada: " << token << std::endl;
                wordsNotFound.push_back(token);
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
            if (!dictionary.containsInBKTree(token, 0)) {
                std::cout << "[BKTree] Palavra não encontrada: " << token << std::endl;
            }
        }
        auto endBKTree = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> durationBKTree = endBKTree - startBKTree;
        std::cout << "Tempo (BKTree): " << durationBKTree.count() << " ms\n";

        return wordsNotFound;
    }

    std::string getWordSuggestion(const std::string& word) const {
        if (dictionary.containsInHashTable(word)) {
            return word;
        }

        std::vector<std::string> suggestions = dictionary.getSuggestions(word, 2);
        if (!suggestions.empty()) {
            // Returns the closest suggestion by levenshtein distance
            return getClosestSuggestion(suggestions, word);
        }

        return "";
    }

    std::vector<std::string> getSuggestions(const std::string& word, size_t distance) const {
        if (dictionary.containsInHashTable(word)) {
            return { word };
        }

        return dictionary.getSuggestions(word, distance);
    }

private:
    Dictionary dictionary;
    Tokenizer tokenizer;

    std::string getClosestSuggestion(const std::vector<std::string>& suggestions, const std::string& word) const {
        if (suggestions.empty()) {
            return "";
        }

        // Assuming the first suggestion is the closest
        std::string closest = suggestions[0];
        size_t minDistance = levenshteinDistance(word, closest);

        for (const auto& suggestion : suggestions) {
            size_t distance = levenshteinDistance(word, suggestion);
            if (distance < minDistance) {
                minDistance = distance;
                closest = suggestion;
            }
        }

        return closest;
    }
};
