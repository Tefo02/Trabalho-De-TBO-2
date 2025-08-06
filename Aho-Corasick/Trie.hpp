#pragma once

#include <vector>
#include <string>

const short MAX_SYMBOLS = 256; // Número máximo de símbolos ASCII

class Trie {
public:
    struct TrieNode {
        int next[MAX_SYMBOLS]; // Índices dos filhos
        int fail = 0;       // Índice do nó de falha
        std::vector<int> out = {}; // Posições de saída (palavras completas terminadas nesse nó)

        TrieNode() {
            for(int i = 0; i < MAX_SYMBOLS; ++i) {
                next[i] = -1; // Inicializa os filhos como -1 (nenhum filho)
            }
        }
    };
    
    std::vector<TrieNode> nodes; // Vetor de nós da Trie

    Trie() {
        nodes.push_back(TrieNode()); // Adiciona o nó raiz
    }

    void insert(const std::string& word, int patternIndex) {
        int currentNode = 0;
        for (char c : word) {
            int charIndex = static_cast<unsigned char> (c); // Converte o caractere para índice
            if (nodes[currentNode].next[charIndex] == -1) {
                nodes[currentNode].next[charIndex] = nodes.size(); // Cria um novo nó
                nodes.push_back(TrieNode());
            }
            currentNode = nodes[currentNode].next[charIndex]; // Move para o próximo nó
        }
        nodes[currentNode].out.push_back(patternIndex); // Adiciona o índice do padrão ao nó final
    }

    int size() const {
        return nodes.size();
    }
};

