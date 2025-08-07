#include "HuffmanCompressor.hpp"
#include <chrono>
#include <iostream>

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  std::string inputFile = "data/texto.txt";
  std::string compressedFile = "data/texto.huff";
  std::string decompressedFile = "data/texto_Descomprimido.txt";

  HuffmanCompressor huffman;

  std::cout << "--- COMPRIMINDO ---" << std::endl;
  huffman.compress(inputFile, compressedFile);

  std::cout << "\n--- DESCOMPRIMINDO ---" << std::endl;
  huffman.decompress(compressedFile, decompressedFile);

  std::cout << "\nCiclo completo!" << std::endl;
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> totalDuration = end - start;
  std::cout << "Tempo total de execução: " << totalDuration.count() << " ms\n";

  return 0;
}
