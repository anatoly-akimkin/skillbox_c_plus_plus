#include <iostream>

// Задание 2. Сортировка. Что нужно сделать. Пользователь вводит в консоль 15 дробных чисел. Необходимо прочитать их и вывести в консоль в порядке от большего к меньшему. По возможности используйте минимум дополнительной памяти и проходов по массиву. Пример:

/*Ввод: 1.2 2.3 1.11 3.4 5.5 5.4 5.3 5.1 1.5 1.25 5.41 5.31 5.11 1.51 1.251 
Вывод: 5.5 5.41 5.4 5.31 5.3 5.11 5.1 3.4 2.3 1.51 1.5 1.251 1.25 1.2 1.11*/

// Рекомендации по выполнению. Воспользуйтесь дополнительными материалами. Что оценивается. Используется массив чисел с плавающей точкой для хранения данных. В коде не используются библиотеки, кроме <iostream>. Программа корректно использует обращения по индексам и выдаёт правильный ответ. Асимптотическая сложность алгоритма не более O(n^2). Числа выводятся от большего к меньшему.

void initializeArray(int size, float nums[])
{
    std::cout << "Enter " << size << " numbers: \n";

    for (int i = 0; i < size; i++) 
    {
        std::cin >> nums[i];
    }
}

void insertionSort(int size, float nums[])
{
    for (int i = 1; i < size; i++)
    {
        int current_element = i;
        while (current_element > 0 && nums[current_element] > nums[current_element-1])
        {
            nums[current_element] += nums[current_element-1];
            nums[current_element-1] = nums[current_element] - nums[current_element-1];
            nums[current_element] -= nums[current_element-1];
            current_element--;
        }
    }
}

void printArray(int size, float nums[])
{
    for (int i = 0; i < size; i++)
    {
        std::cout << nums[i] << " ";
    }
}

int main() 
{
    float nums[15]; // = {1.2,2.3,1.11,3.4,5.5,5.4,5.3,5.1,1.5,1.25,5.41,5.31,5.11,1.51,1.251};
    int size = sizeof(nums)/sizeof(nums[0]);

    initializeArray(size, nums);

    insertionSort(size, nums);

    printArray(size, nums);
}