#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint> 

#include "CharacterReader.hpp"
#include "HuffmanTree.hpp"

class HuffmanCompressor
{
public:
    HuffmanCompressor() = default;

    void compress(const std::string& inputFilePath, const std::string& outputFilePath)
    {
        CharacterReader reader;
        reader.fileReading(inputFilePath);
        auto frequencies = reader.getFrequencias();
        if (frequencies.empty())
        {
            std::cout << "Arquivo de entrada vazio ou nao encontrado. Nada a fazer." << std::endl;
            return;
        }

        Huffmantree huffmanTree;
        huffmanTree.buildTree(frequencies);

        // Chamamos apenas uma vez e guardamos a referência constante
        const auto& huffmanCodes = huffmanTree.getHuffmanCodes();

        //Compressão
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        std::ofstream outputFile(outputFilePath, std::ios::binary);
        if (!inputFile.is_open() || !outputFile.is_open())
        {
            std::cerr << "Erro ao abrir arquivos de entrada/saida." << std::endl;
            return;
        }

        uint8_t paddingInfo = 0;
        outputFile.write(reinterpret_cast<const char*>(&paddingInfo), sizeof(paddingInfo));

        uint16_t uniqueChars = frequencies.size();
        outputFile.write(reinterpret_cast<const char*>(&uniqueChars), sizeof(uniqueChars));

        for (const auto& pair : frequencies)
        {
            outputFile.write(&pair.first, sizeof(pair.first));
            outputFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
        }

        // Escrever os bits
        char character;
        uint8_t byteBuffer = 0;
        int bitCount = 0;

        while (inputFile.get(character))
        {
            std::string code;
            if (huffmanCodes.find(character, code)) {
                for (char bit : code)
                {
                    byteBuffer <<= 1;
                    if (bit == '1')
                    {
                        byteBuffer |= 1;
                    }
                    bitCount++;

                    if (bitCount == 8)
                    {
                        outputFile.write(reinterpret_cast<const char*>(&byteBuffer), sizeof(byteBuffer));
                        byteBuffer = 0;
                        bitCount = 0;
                    }
                }
            }
        }

        // Escreve o último byte se houver bits restantes
        if (bitCount > 0)
        {
            byteBuffer <<= (8 - bitCount);
            outputFile.write(reinterpret_cast<const char*>(&byteBuffer), sizeof(byteBuffer));
            paddingInfo = bitCount;
        }
        else if (!frequencies.empty()) // Evita escrever em arquivos vazios
        {
            paddingInfo = 8;
        }

        // Atualiza a informação de padding no início do arquivo
        if (!frequencies.empty()) {
            outputFile.seekp(0);
            outputFile.write(reinterpret_cast<const char*>(&paddingInfo), sizeof(paddingInfo));
        }

        inputFile.close();
        outputFile.close();

        std::cout << "Arquivo comprimido com sucesso em: " << outputFilePath << std::endl;
    }

    void decompress(const std::string& inputFilePath, const std::string& outputFilePath)
    {
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        std::ofstream outputFile(outputFilePath, std::ios::binary);

        if (!inputFile.is_open() || !outputFile.is_open()) {
            std::cerr << "Erro ao abrir arquivos para descompressao." << std::endl;
            return;
        }

        // Ler o Cabeçalho e Reconstruir a Árvore
        uint8_t paddingInfo;
        inputFile.read(reinterpret_cast<char*>(&paddingInfo), sizeof(paddingInfo));

        uint16_t uniqueChars;
        inputFile.read(reinterpret_cast<char*>(&uniqueChars), sizeof(uniqueChars));
        
        // Verifica se há algo para ler 
        if (uniqueChars == 0) {
            inputFile.close();
            outputFile.close();
            std::cout << "Arquivo de entrada nao contem dados para descompressao." << std::endl;
            return;
        }

        std::vector<std::pair<char, int>> frequencies;
        for (uint16_t i = 0; i < uniqueChars; ++i) {
            char character;
            int frequency;
            inputFile.read(&character, sizeof(character));
            inputFile.read(reinterpret_cast<char*>(&frequency), sizeof(frequency));
            frequencies.push_back({character, frequency});
        }

        Huffmantree huffmanTree;
        huffmanTree.buildTree(frequencies);
        Huffmantree::HuffmanNode* root = huffmanTree.getRoot();

        if (root == nullptr) {
            std::cout << "Nao foi possivel reconstruir a arvore a partir do cabecalho." << std::endl;
            return;
        }

        //Decodificar os Dados
        Huffmantree::HuffmanNode* currentNode = root;
        char byteBuffer;
        
        // Lê todos os dados comprimidos de uma vez para um vetor
        std::vector<char> fileData(
            (std::istreambuf_iterator<char>(inputFile)),
            (std::istreambuf_iterator<char>())
        );

        for (size_t i = 0; i < fileData.size(); ++i) {
            byteBuffer = fileData[i];
            int bitsToProcess = (i == fileData.size() - 1 && paddingInfo != 8) ? paddingInfo : 8;

            for (int j = 7; j >= (8 - bitsToProcess); --j) {
                bool bitIsSet = (byteBuffer >> j) & 1;

                currentNode = bitIsSet ? currentNode->right : currentNode->left;

                if (currentNode->left == nullptr && currentNode->right == nullptr) {
                    outputFile.put(currentNode->character);
                    currentNode = root;
                }
            }
        }

        inputFile.close();
        outputFile.close();

        std::cout << "Arquivo descomprimido com sucesso em: " << outputFilePath << std::endl;
    }
};

