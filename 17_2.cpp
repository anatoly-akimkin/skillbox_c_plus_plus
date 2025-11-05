// Задача 2. Что нужно сделать. Напишите функцию, принимающую указатель на тип int, по которому размещены десять переменных типа int. Функция ничего не возвращает, но по тому же указателю элементы должны располагаться в обратном порядке.
// Чек-лист для проверки задачи. Функция принимает корректные типы данных, тип возвращаемого значения — void. Функция не использует библиотеки, кроме <iostream>. По переданному указателю переменные располагаются в обратном порядке.

#include <iostream>

void swap(int* pa, int* pb)
{
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void reverse(int* ptr)
{
    for (int i = 0; i < 5; ++i)
    {
        swap((ptr + i), (ptr + 9 - i));
    }
}

void print_arr(int* arr)
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << *(arr + i) << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int arr[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << "Before: ";
    print_arr(arr);
    reverse(arr);
    std::cout << "After: ";
    print_arr(arr);
}