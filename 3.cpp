// Задача 3. Что нужно сделать. С клавиатуры вводятся числа. Когда пользователь вводит «−1», необходимо выводить на экран пятое по возрастанию число среди введённых. Когда пользователь вводит «−2», программа завершает работу. Пример:
// Ввод: 7 5 3 1 2 4 6 −1
// Вывод: 5 (в отсортированном виде введённые числа выглядят так: {1, 2, 3, 4, 5, 6, 7})
// Ввод: 1 1 1 −1
// Вывод: 2 (в отсортированном виде введённые числа выглядят так: {1, 1, 1, 1, 2, 3, 4, 5, 6, 7})
// Ввод: −2
// Завершение программы
// Важная часть задания — оптимальное использование ресурсов. Для решения этой задачи достаточно хранить в векторе только пять наименьших элементов. Например, если мы храним массив [1,3,5,7,9] и вводим число 15 — его можно отбросить, так как оно уже никогда не будет пятым в ряду введённых чисел. А если вводится число 8, массив должен поменяться на [1,3,5,7,8], и теперь всё, что больше 8, можно игнорировать.
// Рекомендация. Удостоверьтесь, что требуемое число можно вывести (может быть меньше пяти чисел).

#include <iostream>
#include <utility>

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
    int smallest[] {-4, -4, -4, -4, -4};
    std::cout << "Enter a number: ";
    int val = input_int();

    while (val != -2)
    {
        if (val >= 0)
        {
            for (int i = 0; i < 5; i++)
            {
                if (smallest[i] == -4)
                {
                    smallest[i] = val;
                    break;
                }
                else if (val < smallest[i])
                {
                    std::swap(smallest[i], val);
                }
            }
        }
        else if (val == -1)
        {
            if (smallest[4] == -4)
            {
                std::cout << "Please enter more numbers.\n";
            }
            else
            {
                std::cout << "The fifth largest number: " << smallest[4] << std::endl;
            }
        }
        else if (val == -3)
        {
            for (int i = 0; i < 5; i++) std::cout << smallest[i] << " ";
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Please enter a positive number, -1, -3 or -2.\n";
        }

        val = input_int();
    }
}