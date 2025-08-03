#include <iostream>
#include <string>
#include "LinkedList.hpp"

void counter(std::string encryptText)
{
    LinkedList list;
    char mostUsedLetter;
    // criando a lista ligada

    for (char c : encryptText)
    {
        list.insertNode(c);
    }

    list.findLetter(mostUsedLetter);

    std::cout << "Letra mais usada " << mostUsedLetter << std::endl;
}
