#pragma once

#include <vector>

// Função de busca binária
// Retorna o índice do elemento encontrado ou -1 se não encontrado
// A função assume que o vetor está ordenado
// O operador de comparação deve ser definido para o tipo T
template <typename T>
int binarySearch(const std::vector<T>& arr, const T& target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // Elemento encontrado
        }
        if (arr[mid] < target) {
            left = mid + 1; // Procurar na metade da direita
        }
        else {
            right = mid - 1; // Procurar na metade da esquerda
        }
    }
    return -1; // Elemento não encontrado
}