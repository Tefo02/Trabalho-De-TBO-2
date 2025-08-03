#include <iostream>
#include "TokenizeAlphabet.hpp"
#include <string>
#include <cctype>

void OrganizeKeys(std::string key, std::string &grupoKey, std::string &elementKey)
{
    grupoKey.clear();
    elementKey.clear();

    int index = 0;
    while (key[index] != '-' && key[index] != '\0')
    {
        grupoKey += key[index];
        index++;
    }
    int i = 6;
    int size = key.size();
    while (i < size)
    {
        elementKey += key[i];
        i++;
    }
}
bool caractereException(char caractere, std::string &encryptText)
{
    if (caractere == ' ')
    {
        encryptText += ' ';
        return true;
    }
    if (caractere == 'z' || caractere == 'Z')
    {
        encryptText += 'Z';
        return true;
    }
    bool signalException = writeSignal(caractere);

    if (signalException)
    {
        encryptText += caractere;
        return true;
    }
    return false;
}
void encrypt(std::string const grupoKey, std::string const elementKey, std::string dataBase, std::string &encryptText)
{
    char letter, targetGrup;
    int posLetterGrup, posTargetGrup, posMappedLetter;
    std::string vectorGrup;
    bool caractere_Exception;

    for (int index = 0; dataBase[index] != '\0'; index++)
    {
        caractere_Exception = caractereException(dataBase[index], encryptText);
        if (caractere_Exception)
            continue;

        // extraio a letra da base de dados
        letter = std::toupper(dataBase[index]);
        // std::cout << "letra: " << letter << std::endl;
        //  encontro o grupo que esta letra faz parte
        posLetterGrup = chooseFixedGrup(letter);
        // std::cout << "o grupo que a letra faz parte: " << posLetterGrup << std::endl;
        //   encontro para qual grupo esta letra foi mapeada
        targetGrup = grupoKey[posLetterGrup - 1];
        posTargetGrup = targetGrup - '0';
        // std::cout << "o grupo que a letra foi mapeada: " << posTargetGrup << std::endl;
        //   extrai o grupo escolhido
        vectorGrup = chooseGrup(posTargetGrup);
        // std::cout << "O vetor que contem o grupo mapeado :" << posTargetGrup << std::endl;
        //   encontro a posição da letra mapeada dentro do grupo
        posMappedLetter = chooseLetter(letter);
        // std::cout << "A letra escolhido do grupo mapeada: " << posMappedLetter << std::endl;
        //   gravo a letra encriptada
        char aux = elementKey[posMappedLetter - 1];
        int indice = aux - '0';
        // std::cout << "Indice" << indice << std::endl;
        encryptText += vectorGrup[indice - 1];
    }
}