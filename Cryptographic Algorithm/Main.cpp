#include <iostream>
#include "TokenizeAlphabet.hpp"
#include "Encrypt.hpp"
#include "ReaderAndWritter.hpp"
#include <string>
#include "LinkedList.hpp"
#include "Decrypt.hpp"

int main()
{
    std::string dataBase;
    std::string key;
    std::string grupoKey;
    std::string elementKey;
    std::string encryptText;

    std::getline(std::cin, dataBase);
    std::cin >> key;

    OrganizeKeys(key, grupoKey, elementKey);
    encrypt(grupoKey, elementKey, dataBase, encryptText);

    int tam = encryptText.size();

    for (int i = 0; i < tam; i++)
    {
        std::cout << encryptText[i];
    }
    // falta fazer a parte que aceita caractere especial, se dar tempo.
    std::cout << std::endl;

    counter(encryptText);
    return 0;
}