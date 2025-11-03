// Задача 4. Что нужно сделать. Вам даётся массив целых чисел, отсортированных по возрастанию. Необходимо вывести его на экран отсортированным в порядке возрастания модуля чисел. Пример: 
// Массив {−100, −50, −5, 1, 10, 15}
// Вывод: 1, −5, 10, 15, −50, −100
// Рекомендация. Решение этой задачи не требует новой сортировки массива, так как массив уже отсортирован. Нужно лишь правильно организовать проход по массиву с выдачей значений по условию задачи. Подсказка: можно двигаться от первого положительного элемента влево или вправо, выбирая следующий элемент, больший по модулю.

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

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

int main()
{
    std::cout << "Enter the array size: ";
    int size = input_int(); // 6
    while (size <= 0)
    {
        std::cerr << "The size must be greater than zero.\n";
        size = input_int();
    }

    std::vector<int> vec(size);
    std::cout << "Enter an array of integers sorted in ascending order: "; // -100 -50 -5 1 10 15
    bool not_sorted;
    do
    {
        not_sorted = false;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        vec[0] = input_int();
        for (int i = 1; i < size; ++i)
        {
            vec[i] = input_int();
            if (vec[i] < vec[i-1]) not_sorted = true;
        }
        if (not_sorted) std::cerr << "The array is not sorted. Try again.\n";
    } while (not_sorted);

    
    int start = size-1; // Index of the first positive value

    for (int i = 0; i < size; ++i)
    {
        if (vec[i] >= 0)
        {
            start = i;
            break;
        }
    }
    
    std::cout << "Array sorted in ascending order of absolute values:\n";
    std::cout << vec[start] << " ";
    for (int r = (size-1 - start), l = start; r+l > 0;)
    {
        if (r > 0 && l > 0) // If there are both positive and negative values ​​to print
        {
            if (vec[size-r] < std::abs(vec[l-1]))
            {
                std::cout << vec[size-r] << " ";
                --r;
            }
            else
            {
                --l;
                std::cout << vec[l] << " ";
            }
        }
        else if (r > 0) // If the remaining values ​​are positive
        {
            std::cout << vec[size-r] << " ";
            --r;
        }
        else // If the remaining values ​​are negative
        {
            --l;
            std::cout << vec[l] << " ";
        }
    }
}
