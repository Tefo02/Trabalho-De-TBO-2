#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

// Heap minimo
template <typename T, typename Comparator>

class MinHeap
{
private:
    std::vector<T> heap;
    Comparator comp;

    void swap(int index1, int index2)
{
    if (index1 >= 0 && index1 < heap.size() && index2 >= 0 && index2 < heap.size())
    {
        T aux = heap[index1];
        heap[index1] = heap[index2];
        heap[index2] = aux;
    }
}
    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return 2 * i + 1;
    }

    int right(int i)
    {
        return 2 * i + 2;
    }

    // Move o elemento no índice 'i' para cima até restaurar a propriedade do heap
    void heapifyUp(int i)
    {
        while (i > 0 && comp(heap[i], heap[parent(i)]))
        {
            swap(i, parent(i));
            i = parent(i); // Continua subindo a partir da nova posição
        }
    }

    // Move o elemento no índice 'i' para baixo até restaurar a propriedade do heap
    void heapifyDow(int i)
    {
        int index = i;
        int l = left(i);
        int r = right(i);

        if (l < size() && comp(heap[l], heap[index]))
        {
            index = l;
        }

        if (r < size() && comp(heap[r], heap[index]))
        {
            index = r;
        }

        if (i != index)
        {
            swap(i, index);
            heapifyDow(index); // Se o menor não for o nó atual,chamada recursiva para continuar o processo 
        }
    }

public:

 explicit MinHeap(const Comparator& c) : comp(c) {} 

    bool empty() const
    {
        return heap.empty();
    }

    int size() const
    {
        return heap.size();
    }

    void push(const T &value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Remove o elemento do topo
    void pop()
    {
        if (heap.empty())
        {
            throw std::out_of_range("Heap esta vazio");
        }

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
        {
            heapifyDow(0);
        }
    }

    T getTop() const
    {
        if (heap.empty())
        {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }
};
