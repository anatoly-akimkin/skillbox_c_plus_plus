// Задача 1. Что нужно сделать. Вам даётся массив целых чисел. Необходимо найти в массиве такие два индекса i и j, что сумма a[i], a[i+1], a[i+2], …, a[j] будет максимально возможной, и вывести их. Пример
// a = {−2, 1, −3, 4, −1 ,2 ,1 ,−5 ,4}
// Наибольшая сумма последовательных элементов находится между индексами 3 и 6: {4, −1 ,2 ,1}, сумма = 6. Необходимо вывести 3 и 6.

#include <iostream>
#include <vector>

int input_int()
{
    int val;
    std::cin >> val;
    while(std::cin.fail())
    {
        std::cerr << "Integer input expected.\n";
        std::cin.clear();
        while(std::cin.peek() != ' ' && std::cin.peek() != '\n') std::cin.ignore();
        std::cin >> val;
    }
    return val;
}

void print_vec(std::vector<int> &vec, int size, int i = 0)
{
    int end_i = i + size-1; 
    std::cout << "{";
    for (; i < end_i; i++)
    {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[end_i] << "}";
}

int vec_sum(std::vector<int> &vec, int size, int start_pos = 0)
{
    int sum = 0;
    for (int i = start_pos; i < (start_pos + size); i++)
    {
        sum += vec[i];
    }
    return sum;
}

int main()
{
    std::cout << "Enter the array size: ";
    int size = input_int(); // 9
    while (size <= 0)
    {
        std::cout << "The size must be greater than zero.\n";
        size = input_int();
    }

    std::vector<int> vec(size);
    std::cout << "Enter an array of integers: ";
    for (int i = 0; i < size; i++)
    {
        vec[i] = input_int(); // -2 1 -3 4 -1 2 1 -5 4
    }

    int max_sum = vec_sum(vec, size);
    int start_i = 0, end_i = size-1;

    
    int elements = size-1; // number of elements in subarray
    while (elements > 0)
    {
        // checking subarrays of a given size
        for (int i = 0; i <= size - elements; i++) 
        {
            int sum = vec_sum(vec, elements, i);
            if (sum >= max_sum)
            {
                max_sum = sum;
                start_i = i;
                end_i = i + elements-1;
            }
        }
        elements--;
    }

    std::cout << "The largest sum of consecutive elements is between indices " 
                << start_i << " and " << end_i << ": ";
    print_vec(vec, (end_i - start_i + 1), start_i);
    std::cout << ", sum = " << max_sum << ".";
}