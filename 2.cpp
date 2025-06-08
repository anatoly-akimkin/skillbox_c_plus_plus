// Задача 2. Что нужно сделать. Вам даётся массив целых чисел и одно число — результат. Необходимо найти в массиве два числа, сумма которых будет давать результат, и вывести их на экран. Гарантируется, что только одна пара чисел в массиве даёт в сумме результат. Пример:
// a = {2, 7, 11, 15}. Результат = 9.
// 2 + 7 = 9, так что надо вывести числа 2 и 7.
// Рекомендация. Как только найдена первая удовлетворяющая условиям пара, можно заканчивать поиск.

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

int main()
{
    std::cout << "Enter the array size: ";
    int size = input_int();
    while (size <= 0)
    {
        std::cout << "The size must be greater than zero.\n";
        size = input_int();
    }

    std::vector<int> vec(size);
    std::cout << "Enter an array of integers: ";
    for (int i = 0; i < size; i++)
    {
        vec[i] = input_int();
    }

    std::cout << "Enter the result of adding two array values: ";
    int res = input_int();

    bool found = false;
    int val1, val2;
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (vec[i] + vec[j] == res)
            {
                found = true;
                val1 = vec[i];
                val2 = vec[j];
                break;
            }
        }
        if (found) break;
    }

    if (found)
    {
        std::cout << "You added the numbers " << val1 << " and " << val2 << ".\n";
    }
    else
    {
        std::cout << "There is no matching pair of numbers.\n";
    }

}