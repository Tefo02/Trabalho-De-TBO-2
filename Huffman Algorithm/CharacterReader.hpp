#pragma once

#include "../Dictionary Algorithm/include/HashTable.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class CharacterReader {
private:
  HashTable<char, int> frequencies;

public:
  CharacterReader() = default;
  ~CharacterReader() = default;

  // Retorna a lista de frequências
  std::vector<std::pair<char, int>> getFrequencias() const {
    return frequencies.getAll();
  }

  // Lê o arquivo e preenche a tabela de frequências
  void fileReading(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Nao foi possivel abrir o arquivo: " << fileName
                << std::endl;
      return;
    }

    char character;
    while (file.get(character)) {
      frequencies[character]++;
    }

    file.close();
  }
};