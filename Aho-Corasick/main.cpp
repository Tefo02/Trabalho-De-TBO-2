#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "SearchBenchmark.hpp"

// Gera string aleatória
std::string generateRandomText(size_t n, const std::string& alphabet = "abcdefghijklmnopqrstuvwxyz") {
    std::mt19937 rng(42);
    std::uniform_int_distribution<> dist(0, alphabet.size() - 1);
    std::string text;
    text.reserve(n);
    for (size_t i = 0; i < n; ++i)
        text.push_back(alphabet[dist(rng)]);
    return text;
}

// Gera padrões aleatórios
std::vector<std::string> generateRandomPatterns(size_t count, int minLen, int maxLen,
                                               const std::string& alphabet = "abcdefghijklmnopqrstuvwxyz") {
    std::mt19937 rng(1337);
    std::uniform_int_distribution<> lenDist(minLen, maxLen);
    std::uniform_int_distribution<> charDist(0, alphabet.size() - 1);

    std::vector<std::string> patterns;
    patterns.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        int len = lenDist(rng);
        std::string pat;
        pat.reserve(len);
        for (int j = 0; j < len; ++j)
            pat.push_back(alphabet[charDist(rng)]);
        patterns.push_back(pat);
    }
    return patterns;
}

int main() {
    // Texto de 1 milhão de caracteres
    std::string text = generateRandomText(10000000);

    // ---- Cenário 1: 1 padrão longo ----
    std::cout << "\n===== Teste: 1 padrão longo (15 caracteres) =====\n";
    auto patterns1 = generateRandomPatterns(1, 4, 4);
    SearchBenchmark::run(text, patterns1);

    // ---- Cenário 2: 10 padrões longos ----
    std::cout << "\n===== Teste: 10 padrões longos (15 caracteres) =====\n";
    auto patterns2 = generateRandomPatterns(10, 4, 4);
    SearchBenchmark::run(text, patterns2);

    // ---- Cenário 3: 100 padrões curtos ----
    std::cout << "\n===== Teste: 100 padrões curtos (4 a 8 caracteres) =====\n";
    auto patterns3 = generateRandomPatterns(100, 4, 8);
    SearchBenchmark::run(text, patterns3);

    // --- Cenário 4: Padrão que favorece o KMP ---
    std::cout << "\n===== Teste : padrão adversário para ingênuo, KMP favorito =====\n";

    // Padrão: 999 'a's + 'b'
    std::string hardPattern(999, 'a');
    hardPattern += 'b';

    // Texto: 1 milhão de 'a's (sem 'b')
    std::string adversaryText(1'000'000, 'a');
    adversaryText += 'b';

    std::vector<std::string> patterns5 = {hardPattern};

    SearchBenchmark::run(adversaryText, patterns5);

    return 0;
}
