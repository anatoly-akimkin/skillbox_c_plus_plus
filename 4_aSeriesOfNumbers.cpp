#include <iostream>

// Что нужно сделать. В программе инициализирован массив из 15 целых положительных чисел. Эти числа являются множеством из 14 последовательных чисел, начиная с Х (Х может быть любым), а одно число из ряда повторяется. Необходимо найти повторяющееся число и вывести его в консоль. По возможности используйте минимум дополнительной памяти и проходов по массиву. Пример.

/*int numbers[15] = {114, 111, 106, 107, 108, 105, 115, 108, 110, 109, 112, 113, 116, 117, 118} 
В данном примере Х — это 105, а повторяющееся число — 108.*/

// Рекомендации по выполнению. Это задание с подвохом. Подумайте, как его можно было бы легко решить за O(n). На всякий случай оставляем для вас подсказку. Рекомендуем воспользоваться при необходимости. Что оценивается. Используется массив int для хранения данных. В коде не используются библиотеки, кроме <iostream>. Программа корректно использует обращения по индексам и выдаёт правильный ответ. Асимптотическая сложность алгоритма менее O(n^2).

void initializeArray(int size, int nums[])
{
    std::cout << "Enter " << size << " numbers: \n";

    for (int i = 0; i < size; i++) 
    {
        std::cin >> nums[i];
    }
}

int main()
{
    int numbers[15];
    //int numbers[] = {114, 111, 106, 107, 108, 105, 115, 108, 110, 109, 112, 113, 116, 117, 118};
    int size = sizeof(numbers)/sizeof(numbers[0]);
    initializeArray(size, numbers);
    // Enter: 114 111 106 107 108 105 115 108 110 109 112 113 116 117 118

    int min = numbers[0];
    int array_sum = 0;
    int sequence_sum = 0;

    for (int i = 0; i < size; i++)
    {
        if (min > numbers[i]) min = numbers[i];
        array_sum += numbers[i];
    }

    for (int i = 0; i < size-1; i++)
    {
        sequence_sum += min;
        min++;
    }

    std::cout << "The repeating number is " << array_sum - sequence_sum << std::endl;
}