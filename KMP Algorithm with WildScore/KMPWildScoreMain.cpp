#include "KMPWithWildScore.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string run_again = "s";

    while (run_again == "s")
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
            std::cout << "Ocorrencias encontradas:" << std::endl;
            for (int index : result)
            {
                // Extrai a palavra do texto usando o índice e o tamanho do padrão
                std::string matched_word = text.substr(index, standard.size());
                std::cout << "Palavra '" << matched_word << "' no indice: " << index << std::endl;
            }
        }

        std::cout << "\nExecutar outra busca? (s/n): ";
        std::getline(std::cin, run_again);
    }

    return 0;
}