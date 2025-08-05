#include "KMP.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{

    std::string standard;
    std::string text;

    std::getline(std::cin, text);
    std::cin >> standard;

    std::vector<int> result = KMP(standard, text);

    for (int i = 0; i < result.size(); i++)
    {
        if (result[i] != -1)
            std::cout << "Padrao encontrado no indice: " << result[i] << std::endl;
        else
            std::cout << "Padrao nao encontrado";
    }
    return 0;
}