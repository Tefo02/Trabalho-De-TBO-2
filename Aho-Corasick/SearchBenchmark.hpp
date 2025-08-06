#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "../KMP/KMP.hpp"    
#include "AhoCorasick.hpp"

// Busca ingênua (força bruta)
std::vector<int> naiveSearch(const std::string& pattern, const std::string& text) {
    std::vector<int> matches;
    int m = static_cast<int>(pattern.size());
    int n = static_cast<int>(text.size());
    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
            j++;
        if (j == m)
            matches.push_back(i);
    }
    return matches;
}

class SearchBenchmark {
public:
    static void run(const std::string& text, const std::vector<std::string>& patterns) {
        using namespace std::chrono;

        // ---- Busca Ingênua ----
        auto start = high_resolution_clock::now();
        for (const auto& pat : patterns) {
            auto res = naiveSearch(pat, text);
            (void)res; // evitar warning
        }
        auto end = high_resolution_clock::now();
        long long naiveTime = duration_cast<microseconds>(end - start).count();

        // ---- KMP ----
        start = high_resolution_clock::now();
        for (const auto& pat : patterns) {
            auto res = KMP(pat, text);
            (void)res;
        }
        end = high_resolution_clock::now();
        long long kmpTime = duration_cast<microseconds>(end - start).count();

        // ---- Aho-Corasick ----
        AhoCorasick aho;
        for (const auto& pat : patterns) {
            aho.addPattern(pat);
        }
        aho.build();
        start = high_resolution_clock::now();
        aho.search(text);
        end = high_resolution_clock::now();
        long long ahoTime = duration_cast<microseconds>(end - start).count();

        // ---- Resultado ----
        std::cout << "Tempo de execução (em microssegundos):\n";
        std::cout << "Busca Ingênua: " << naiveTime << " us\n";
        std::cout << "KMP:           " << kmpTime << " us\n";
        std::cout << "Aho-Corasick:  " << ahoTime << " us\n";
    }
};
