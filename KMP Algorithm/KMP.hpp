#pragma once
#include <iostream>
#include <vector>

int countSymbols(const std::string &standard)
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
void failureFuction(int **matrix, const std::string &standard, int const symbols, const std::vector<int> &symbolIndex)
{
    for (int c = 0; c < symbols; c++)
        matrix[c][0] = 0;

    int aux = symbolIndex[standard[0]];
    matrix[aux][0] = 1;
    int x = 0;

    int currentStandardIndex;
    for (int i = 1; i < standard.size(); i++)
    {
        if (standard[i] == '*')
        {
            for (int c = 0; c < symbols; c++)
            {
                matrix[c][i] = i + 1;
            }
        }
        else
        {
            for (int c = 0; c < symbols; c++)
                matrix[c][i] = matrix[c][x];
        }
        currentStandardIndex = symbolIndex[standard[i]];
        matrix[currentStandardIndex][i] = i + 1;
        x = matrix[currentStandardIndex][x];
    }
}
void display(int **matrix, int symbols, const std::string &standard)
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

std::vector<int> KMP(const std::string &standard, const std::string &text)
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

    std::vector<int> result;

    for (int i = 0; i < text.size(); i++)
    {
        // Lógica para tratar o curinga do padrão
        while (j < standard.size() && standard[j] == '*')
        {
            j++;
        }

        if (j < standard.size())
        {
            int textCharIndex = symbolIndex[text[i]];

            if (textCharIndex != -1)
            {
                j = matrix[textCharIndex][j];
            }
            else
            {
                j = 0;
            }
        }

        if (j == standard.size())
        {
            result.push_back(i - j + 1);

            // Regressão do j corrigida:
            int prevCharIndex = -1;
            if (standard[j - 1] != '*')
            {
                prevCharIndex = symbolIndex[standard[j - 1]];
            }

            if (prevCharIndex != -1)
            {
                j = matrix[prevCharIndex][j - 1];
            }
            else
            {
                j = 0;
            }
        }
    }

    return result;
}