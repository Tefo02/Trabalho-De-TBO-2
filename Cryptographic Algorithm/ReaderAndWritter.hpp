#pragma once

#include <fstream>
#include <iostream>

// Iremos utilizar um algoritmo de substituição
void fread(char dataBase[], char fileName[])
{
    std::ifstream input;
    char temp;
    int index = 0;

    input.open(fileName);

    while (!input.eof())
    {
        input.get(temp);
        dataBase[index++] = temp;
    }

    dataBase[index - 1] = '\0';
    input.close();
}

void fwrite(char dataBase[], char fileName[])
{
    std::ofstream output;
    int index = 0;
    output.open(fileName);

    while (dataBase[index] != '\0')
        output.put(dataBase[index++]);

    output.close();
}
