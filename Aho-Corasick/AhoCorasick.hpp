#pragma once

#include "Trie.hpp"
#include <iostream>

class AhoCorasick  {
    Trie trie; // Instância da Trie para armazenar os padrões
    std::vector<std::string> patterns; // Padrões a serem buscados

public:
    AhoCorasick() = default;
    
    void addPattern(const std::string& pattern) {
        int patternIndex = patterns.size();
        patterns.push_back(pattern);
        trie.insert(pattern, patternIndex); // Insere o padrão na Trie
    }

    void build() {
        std::vector<int> queue;
        int qFront = 0;
    
        for (int c = 0; c < MAX_SYMBOLS; ++c) {
            int next = trie.nodes[0].next[c];
            if (next != -1) {
                trie.nodes[next].fail = 0;
                queue.push_back(next);
            } else {
                trie.nodes[0].next[c] = 0;
            }
        }
    
        while (qFront < queue.size()) {
            int currentNode = queue[qFront++];
    
            for (int c = 0; c < MAX_SYMBOLS; ++c) {
                int next = trie.nodes[currentNode].next[c];
                if (next != -1) {
                    queue.push_back(next);
                    trie.nodes[next].fail = trie.nodes[trie.nodes[currentNode].fail].next[c];
                    trie.nodes[next].out.insert(
                        trie.nodes[next].out.end(),
                        trie.nodes[trie.nodes[next].fail].out.begin(),
                        trie.nodes[trie.nodes[next].fail].out.end()
                    );
                } else {
                    trie.nodes[currentNode].next[c] = trie.nodes[trie.nodes[currentNode].fail].next[c];
                }
            }
        }
    }
    

    void search(const std::string& text) {
        int currentNode = 0;
        for (int i = 0; i < text.size(); ++i) {
            int charIndex = static_cast<unsigned char>(text[i]);
            currentNode = trie.nodes[currentNode].next[charIndex];
            for (int patternIndex : trie.nodes[currentNode].out) {
                std::cout << "Padrão encontrado: " << patterns[patternIndex]
                          << " na posição " << (i - patterns[patternIndex].size() + 1)
                          << std::endl;
            }
        }
    }
    
};