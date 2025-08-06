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
        if (!found) // A matriz já lida com a falha
        {
            countedSymbols += standard[i];
            counted++;
        }
    }
    return counted;
}
// Constrói a matriz de transição (tabela de falha)
void failureFuctionWithWildScore(int **matrix, const std::string &standard, int symbols, const std::vector<int> &symbolIndex)
{
    for (int c = 0; c < symbols; c++)
    {
        matrix[c][0] = 0;
    }

    if (standard[0] != '*')
    {
        int aux = symbolIndex[standard[0]];
        matrix[aux][0] = 1;
    }
    else
    {
        for (int c = 0; c < symbols; c++)
        {
            matrix[c][0] = 1;
        }
    }

    int x = 0;
    for (int i = 1; i < standard.size(); i++)
    {
        for (int c = 0; c < symbols; c++)
        {
            matrix[c][i] = matrix[c][x];
        }

        if (standard[i] != '*')
        {
            int currentStandardIndex = symbolIndex[standard[i]];
            matrix[currentStandardIndex][i] = i + 1;
            x = matrix[currentStandardIndex][x];
        }
        else
        {
            for (int c = 0; c < symbols; c++)
            {
                matrix[c][i] = i + 1;
            }

            // x = (i > 0) ? matrix[symbolIndex[standard[i - 1]]][x] : 0;
            x = i;
        }
    }
}
void display(int **matrix, const int &symbols, const std::string &standard)
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
std::vector<int> KMPWithWildScore(const std::string &standard, const std::string &text)
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
    for (char c : standard)
    {
        if (c != '*' && symbolIndex[c] == -1)
        {
            symbolIndex[c] = symbolCount++;
        }
    }

    symbols = symbolCount;

    failureFuctionWithWildScore(matrix, standard, symbols, symbolIndex);

    display(matrix, symbols, standard);

    int j = 0;

    int currentIndex = -1;

    std::vector<int> result;

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
        if (text[i] == '*')
            j++;
        if (j == standard.size())
        {
            result.push_back(i - j + 1);
            j = matrix[symbolIndex[standard[j - 1]]][j - 2];
        }
    }

    return result;
}