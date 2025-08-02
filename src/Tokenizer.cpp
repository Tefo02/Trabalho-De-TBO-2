#include "../include/Tokenizer.hpp"
#include <sstream>

bool Tokenizer::isSeparator(char c) const {
    return std::isspace(c) || isPunctuation(c) || isBracket(c);
}

bool Tokenizer::isPunctuation(char c) const {
    return c == ',' || c == '.' || c == ';' || c == ':' || c == '!' || c == '?';
}

bool Tokenizer::isBracket(char c) const {
    return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
}

std::vector<std::string> Tokenizer::tokenize() {
    std::vector<std::string> tokens;
    std::string token;

    reset();

    while (position < text.size()) {

        char current = text[position];

        // Se for espaço em branco, adiciona o token atual se não estiver vazio
        if (std::isspace(current)) { 
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            position++;
        // Se for um caractere de pontuação ou símbolo, adiciona como token separado
        } else if (isSeparator(current)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, current));
            position++;
        // Se for um caractere alfanumérico, adiciona ao token atual
        } else {
            token += current;
            position++;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

void Tokenizer::setText(const std::string& newText) {
    text = newText;
    reset();
}

void Tokenizer::reset() {
    position = 0; // Reinicia a posição para o início do texto
}