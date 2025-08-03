#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

int levenshteinDistance(const std::string& s1, const std::string& s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    std::vector<int> col(len2 + 1), prevCol(len2 + 1);

    for (int i = 0; i < prevCol.size(); i++) {
        prevCol[i] = i;
    }

    for (int i = 0; i < len1; i++) {
        col[0] = i + 1;
        for (int j = 0; j < len2; j++) {
            int cost = (s1[i] == s2[j]) ? 0 : 1;
            col[j + 1] = std::min({ prevCol[j + 1] + 1, col[j] + 1, prevCol[j] + cost });
        }
        prevCol = col;
    }
    return prevCol[len2];
}

struct Node {
    std::string word;
    std::vector<std::unique_ptr<Node>> children;
    
    Node(const std::string& w) : word(w) {}
};

class BKTree {
public:
    
private:
    std::unique_ptr<Node> root;

    void add_recursive(Node* currentNode, const std::string& word) {
        int dist = levenshteinDistance(currentNode->word, word);
        
        // Se a distância for 0, a palavra já existe na árvore
        if (dist == 0) return;

        // Verifica se já existe um filho a essa distância
        if (currentNode->children.size() > dist) {
            // Se sim, continua a busca a partir desse filho
            add_recursive(currentNode->children[dist].get(), word);
        } else {
            // Se não, cria um novo nó e o adiciona como filho
            currentNode->children.resize(dist + 1);
            currentNode->children[dist] = std::make_unique<Node>(word);
        }
    }

    void search_recursive(Node* currentNode, const std::string& word, int max_distance, std::vector<std::string>& results) {
        if (!currentNode) return;

        int dist = levenshteinDistance(currentNode->word, word);

        // Se a distância for aceitável, adiciona a palavra aos resultados
        if (dist <= max_distance) {
            results.push_back(currentNode->word);
        }

        // Explora apenas os filhos relevantes
        for (int d = dist - max_distance; d <= dist + max_distance; ++d) {
            if (d >= 0 && d < currentNode->children.size()) {
                search_recursive(currentNode->children.at(d).get(), word, max_distance, results);
            }
        }
    }
};