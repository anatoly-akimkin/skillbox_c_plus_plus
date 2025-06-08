// Задача 4. Что нужно сделать. Вам даётся массив целых чисел, отсортированных по возрастанию. Необходимо вывести его на экран отсортированным в порядке возрастания модуля чисел. Пример: 
// Массив {−100, −50, −5, 1, 10, 15}
// Вывод: 1, −5, 10, 15, −50, −100
// Рекомендация. Решение этой задачи не требует новой сортировки массива, так как массив уже отсортирован. Нужно лишь правильно организовать проход по массиву с выдачей значений по условию задачи. Подсказка: можно двигаться от первого положительного элемента влево или вправо, выбирая следующий элемент, больший по модулю.

#include <iostream>
#include <vector>
#include <cmath>

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

int main()
{
    std::cout << "Enter the array size: ";
    int size = input_int(); // 6
    while (size <= 0)
    {
        std::cout << "The size must be greater than zero.\n";
        size = input_int();
    }

    std::vector<int> vec(size);
    std::cout << "Enter an array of integers sorted in ascending order: "; // -100 -50 -5 1 10 15
    bool not_sorted;
    int start; // Index of the first positive value
    do
    {
        not_sorted = false;
        while(std::cin.peek() != '\n') std::cin.ignore();
        for (int i = 0; i < size; i++)
        {
            vec[i] = input_int();
            if (i > 0 && vec[i] < vec[i-1]) not_sorted = true;
            if (i > 0 && vec[i] >= 0 && vec[i-1] < 0 ) start = i;
        }
        if (not_sorted) std::cout << "The array is not sorted. Try again.\n";
    } while (not_sorted);

    if (vec[0] >= 0) 
    {
        start = 0;
    }
    else if (vec[size-1] < 0)
    {
        start = size-1;
    }
    
    std::cout << "Array sorted in ascending order of absolute values:\n";
    std::cout << vec[start] << " ";
    for (int r = 0, l = 0; r+l < size-1;)
    {
        if (start+r+1 < size && start-l-1 >= 0) // If there are both positive and negative values ​​to print
        {
            if (vec[start+r+1] < std::abs(vec[start-l-1]))
            {
                std::cout << vec[start+r+1] << " ";
                r++;
            }
            else
            {
                std::cout << vec[start-l-1] << " ";
                l++;
            }
        }
        else if (start+r+1 < size) // If the remaining values ​​are positive
        {
            std::cout << vec[start+r+1] << " ";
            r++;
        }
        else // If the remaining values ​​are negative
        {
            std::cout << vec[start-l-1] << " ";
            l++;
        }
    }
}
