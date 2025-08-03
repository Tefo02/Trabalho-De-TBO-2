#pragma once
#include <iostream>
#include <string.h>

int chooseFixedGrup(char letter)
{
    switch (letter)
    {
    case 'A':
        return 1;

    case 'B':
        return 1;

    case 'C':
        return 1;

    case 'D':
        return 1;

    case 'E':
        return 1;

    case 'F':
        return 2;

    case 'G':
        return 2;

    case 'H':
        return 2;

    case 'I':
        return 2;

    case 'J':
        return 2;

    case 'K':
        return 3;

    case 'L':
        return 3;

    case 'M':
        return 3;

    case 'N':
        return 3;

    case 'O':
        return 3;

    case 'P':
        return 4;

    case 'Q':
        return 4;

    case 'R':
        return 4;

    case 'S':
        return 4;

    case 'T':
        return 4;

    case 'U':
        return 5;

    case 'V':
        return 5;

    case 'W':
        return 5;

    case 'X':
        return 5;

    case 'Y':
        return 5;

    case 'Z':
        return 6;
    }
    return -1;
}
std::string chooseGrup(int value)
{
    std::string grup1 = "ABCDE";
    std::string grup2 = "FGHIJ";
    std::string grup3 = "KLMNO";
    std::string grup4 = "PQRST";
    std::string grup5 = "UVWXY";
    std::string grup6 = "Z";
    switch (value)
    {
    case 1:
        return grup1;
    case 2:
        return grup2;
    case 3:
        return grup3;
    case 4:
        return grup4;
    case 5:
        return grup5;
    case 6:
        return grup6;
    }
    return "";
}
int chooseLetter(char letter)
{
    switch (letter)
    {
    case 'A':
        return 1;

    case 'B':
        return 2;

    case 'C':
        return 3;

    case 'D':
        return 4;

    case 'E':
        return 5;

    case 'F':
        return 1;

    case 'G':
        return 2;

    case 'H':
        return 3;

    case 'I':
        return 4;

    case 'J':
        return 5;

    case 'K':
        return 1;

    case 'L':
        return 2;

    case 'M':
        return 3;

    case 'N':
        return 4;

    case 'O':
        return 5;

    case 'P':
        return 1;

    case 'Q':
        return 2;

    case 'R':
        return 3;

    case 'S':
        return 4;

    case 'T':
        return 5;

    case 'U':
        return 1;

    case 'V':
        return 2;

    case 'W':
        return 3;

    case 'X':
        return 4;

    case 'Y':
        return 5;

    case 'Z':
        return 1;
    }
    return -1;
}
bool writeSignal(char sinal)
{
    if (sinal == '.' || sinal == ',' || sinal == ':' || sinal == ';' || sinal == '-' || sinal == '!' || sinal == '?' || sinal == '"')
        return true;

    return false;
}
