#pragma once
#include <vector>
#include <string>

class Tokenizer {
public:
    Tokenizer(const std::string& text) : text(text), position(0) {}

    std::vector<std::string> tokenize();
    void setText(const std::string& newText);
    void reset();
    
private:
    std::string text;
    size_t position;

    bool isSeparator(char c) const;
    bool isPunctuation(char c) const;
    bool isBracket(char c) const;
};