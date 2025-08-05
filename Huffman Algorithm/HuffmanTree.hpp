#pragma once

#include "../Dictionary Algorithm/include/HashTable.hpp"
#include "MinHeap.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Huffmantree {
public:
  // A struct do nó da árvore
  struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *right;
    HuffmanNode *left;

    HuffmanNode(char c, int freq)
        : character(c), frequency(freq), right(nullptr), left(nullptr) {}
  };

private:
  HuffmanNode *root;
  HashTable<char, std::string> huffmanCodes;

  void deleteTree(HuffmanNode *node) {
    if (node == nullptr)
      return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

  // Função auxiliar recursiva para gerar os códigos
  void generateCodesRecursive(HuffmanNode *node,
                              const std::string &currentCode) {
    if (node == nullptr) {
      return;
    }

    if (node->character != '\0') {
      // Caso especial para árvore com um único nó
      huffmanCodes[node->character] = currentCode.empty() ? "0" : currentCode;
    }

    generateCodesRecursive(node->left, currentCode + "0");
    generateCodesRecursive(node->right, currentCode + "1");
  }

public:
  Huffmantree() : root(nullptr) {}

  ~Huffmantree() { deleteTree(root); }

  // Constrói a árvore a partir das frequências
  void buildTree(const std::vector<std::pair<char, int>> &frequencies) {
    auto comparator = [](HuffmanNode *a, HuffmanNode *b) {
      return a->frequency > b->frequency;
    };
    MinHeap<HuffmanNode *, decltype(comparator)> minHeap(comparator);

    for (const auto &pair : frequencies) {
      minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
      HuffmanNode *left = minHeap.getTop(); // Usando top() como no padrão
      minHeap.pop();
      HuffmanNode *right = minHeap.getTop();
      minHeap.pop();

      int sumFreq = left->frequency + right->frequency;
      HuffmanNode *parent = new HuffmanNode('\0', sumFreq);
      parent->left = left;
      parent->right = right;

      minHeap.push(parent);
    }

    if (!minHeap.empty()) {
      root = minHeap.getTop();
    }
  }

  // Retorna a raiz da árvore
  HuffmanNode *getRoot() const { return this->root; }

  // Retorna a tabela de códigos (gera se ainda não foi gerada)
  const HashTable<char, std::string> &getHuffmanCodes() {
    if (huffmanCodes.empty() && root != nullptr) {
      generateCodesRecursive(root, "");
    }
    return huffmanCodes;
  }
};