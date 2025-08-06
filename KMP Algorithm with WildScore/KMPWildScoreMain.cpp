#include "KMPWithWildScore.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string standard;
    std::string text;

    std::cout << "Digite o texto: ";
    std::getline(std::cin, text); // Lê a linha completa para o texto

    std::cout << "Digite o padrao: ";
    std::getline(std::cin, standard); // Lê a linha completa para o padrao

    std::vector<int> result = KMPWithWildScore(standard, text);

    if (result.empty())
    {
        std::cout << "Padrao nao encontrado" << std::endl;
    }
    else
    {
        std::cout << "Ocorrencias encontradas nos indices: ";
        for (int index : result)
        {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}