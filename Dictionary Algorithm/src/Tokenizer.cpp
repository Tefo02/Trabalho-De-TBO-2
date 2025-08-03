#include "../include/Tokenizer.hpp"
#include <sstream>
#include <algorithm> // std::transform
#include <cctype>    // std::tolower

std::vector<std::string> Tokenizer::tokenize() {
    std::vector<std::string> tokens;
    std::string token;

    reset();

    while (position < text.size()) {
        char current = text[position];

        if (std::isspace(current)) {
            if (!token.empty()) {
                // Converte token para minúsculo
                std::transform(token.begin(), token.end(), token.begin(),
                               [](unsigned char c) { return std::tolower(c); });
                tokens.push_back(token);
                token.clear();
            }
            position++;
        } else if (isSeparator(current)) {
            if (!token.empty()) {
                std::transform(token.begin(), token.end(), token.begin(),
                               [](unsigned char c) { return std::tolower(c); });
                tokens.push_back(token);
                token.clear();
            }
            // NÃO adiciona pontuação como token
            position++;
        } else {
            token += current;
            position++;
        }
    }

    if (!token.empty()) {
        std::transform(token.begin(), token.end(), token.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        tokens.push_back(token);
    }

    return tokens;
}


bool Tokenizer::isSeparator(char c) const {
    return std::isspace(c) || isPunctuation(c) || isBracket(c);
}

bool Tokenizer::isPunctuation(char c) const {
    return c == ',' || c == '.' || c == ';' || c == ':' || c == '!' || c == '?';
}

bool Tokenizer::isBracket(char c) const {
    return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
}

void Tokenizer::setText(const std::string& newText) {
    text = newText;
    reset();
}

void Tokenizer::reset() {
    position = 0; // Reinicia a posição para o início do texto
}