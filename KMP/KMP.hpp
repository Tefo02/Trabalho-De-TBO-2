#pragma once
#include <iostream>
#include <vector>

int countSymbols(std::string standard)
{
    std::string countedSymbols;
    int counted = 0;

    for (int i = 0; i < standard.size(); i++)
    {
        bool found = false;
        for (int j = 0; j < countedSymbols.size(); j++)
        {
            if (standard[i] == countedSymbols[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            countedSymbols += standard[i];
            counted++;
        }
    }
    return counted;
}
void failureFuction(int **matrix, std::string standard, int symbols, std::vector<int> &symbolIndex)
{
    for (int c = 0; c < symbols; c++)
        matrix[c][0] = 0;

    int aux = symbolIndex[standard[0]];
    matrix[aux][0] = 1;
    int x = 0;

    int currentStandardIndex;
    for (int i = 1; i < standard.size(); i++)
    {
        for (int c = 0; c < symbols; c++)
            matrix[c][i] = matrix[c][x];

        currentStandardIndex = symbolIndex[standard[i]];
        matrix[currentStandardIndex][i] = i + 1;
        x = matrix[currentStandardIndex][x];
    }
}
void display(int **matrix, int symbols, std::string standard)
{
    std::cout << "Matriz de Transição (linhas = símbolos, colunas = posições do padrão)" << std::endl;

    for (int i = 0; i < symbols; i++)
    {
        for (int j = 0; j < standard.size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Padrão: " << standard << std::endl;
}

int KMP(std::string standard, std::string text)
{
    int symbols = countSymbols(standard);
    int **matrix = new int *[symbols];

    for (int i = 0; i < symbols; i++)
    {
        matrix[i] = new int[standard.size()]();
    }

    // crio um vetor com tamanho de 256 para armazenar todos os possíveis caracteres ASCII
    std::vector<int> symbolIndex(256, -1);
    int symbolCount = 0;

    for (int i = 0; i < standard.size(); i++)
    {
        if (symbolIndex[standard[i]] == -1)
            symbolIndex[standard[i]] = symbolCount++;
    }

    failureFuction(matrix, standard, symbols, symbolIndex);

    display(matrix, symbols, standard);

    int j = 0;

    int currentIndex = -1;

    for (int i = 0; i < text.size(); i++)
    {
        for (int k = 0; k < standard.size(); k++)
        {
            if (text[i] == standard[k] && symbolIndex[standard[k]] != -1)
            {
                currentIndex = symbolIndex[standard[k]];
                break;
            }
        }
        if (currentIndex != -1)
            j = matrix[currentIndex][j];

        if (j == standard.size())
            return i - j + 1;
    }
    return -1;
}

int main()
{
    std::string standard;
    std::string text;

    std::getline(std::cin, text);
    std::cin >> standard;

    int result = KMP(standard, text);

    if (result != -1)
        std::cout << "Padrao encontrado no indice: " << result << std::endl;
    else
        std::cout << "Padrao nao encontrado";

    return 0;
}