// Задача 1. Что нужно сделать. Вам даётся массив целых чисел. Необходимо найти в массиве такие два индекса i и j, что сумма a[i], a[i+1], a[i+2], …, a[j] будет максимально возможной, и вывести их. Пример
// a = {−2, 1, −3, 4, −1 ,2 ,1 ,−5 ,4}
// Наибольшая сумма последовательных элементов находится между индексами 3 и 6: {4, −1 ,2 ,1}, сумма = 6. Необходимо вывести 3 и 6.

#include <iostream>
#include <limits>
#include <vector>

int input_int()
{
    int val;
    std::cin >> val;
    while (std::cin.fail())
    {
        std::cerr << "Integer input expected.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

int main()
{
    std::cout << "Enter the array size: ";
    int size = input_int(); // 9
    while (size <= 0)
    {
        std::cerr << "The size must be greater than zero.\n";
        size = input_int();
    }

    std::vector<int> vec(size);
    std::cout << "Enter an array of integers: ";
    for (int i = 0; i < size; i++)
    {
        vec[i] = input_int(); // -2 1 -3 4 -1 2 1 -5 4
    }
    //std::vector<int> vec {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    int start_i = 0, subArrSize = 0, res = 0;

    int curArrSize = 0, curMaxSum = 0;
    for (int i = 0; i < size; i++) 
    {
        if (curMaxSum + vec[i] > vec[i])
        {
            curMaxSum += vec[i];
            curArrSize++;
        }
        else
        {
            curMaxSum = vec[i];
            curArrSize = 1;
        }

        if (res < curMaxSum)
        {
            start_i = i - (curArrSize-1);
            subArrSize = curArrSize;
            res = curMaxSum;
        } 
    }

    std::cout << "The largest sum of consecutive elements is between indices " 
                << start_i << " and " << (start_i + subArrSize-1) << ": ";
    print_vec(vec, subArrSize, start_i);
    std::cout << ", sum = " << res << ".";
}