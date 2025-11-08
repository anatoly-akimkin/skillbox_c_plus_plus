// Задача 2. Что нужно сделать. Кролик сидит на нулевой ступеньке большой лестницы. Он может прыгать на одну или более ступенек вверх, но не далее чем на k. Кролик хочет допрыгать до n-й ступеньки, но может сделать это большим количеством способов. Напишите рекурсивную функцию, которая принимает число n типа int и число k — максимальную длину прыжка, а возвращает количество способов, которым кролик может доскакать до n-й ступеньки. В функции для аргумента “максимальная длина прыжка” задать значение, по умолчанию равное 3. Пример:
// Ввод: 3, 2
// Вывод: 3 
// Пояснение: (1,2), (2,1), (1,1,1)
// Чек-лист для проверки задачи. Функция принимает корректные типы данных, тип возвращаемого значения —  int. Функция не использует библиотек кроме <iostream>. Функция рекурсивная. Функция содержит значение по умолчанию.

#include <iostream>
#include <string>
#include <sstream>

int combinations_count(int n, const int& k = 3)
{
    // std::cout << &k << std::endl;
    int counter = 0;
    for (int i = 1; i <= k; ++i)
    {
        if (n-i > 0) 
        {
            // std::cout << i << " ";
            counter += combinations_count((n-i), k);
        }
        else if ((n-i) == 0)
        {
            // std::cout << i << std::endl;
            ++counter;
        }
        else
        {
            break;
        }
    }
    return counter;
}

int main()
{
    int n; // The last step
    int k; // Maximum jump length

    std::cout << "Enter the number of the last step and the maximum jump length.\n";
    
    bool bad_val = true;
    while (bad_val)
    {
        std::string s;
        std::cout << "---> ";
        std::getline(std::cin, s);
        std::stringstream ss(s);
        ss >> n;
        bad_val = ss.fail() || n < 1;
        ss >> k; // if ss.fail() ---> k = 0;
        if (bad_val)
        {
            std::cerr << "Bad input.\n";
            // ss.str("");
            // ss.clear();
        }
    }
    
    std::cout << "Number of available combinations: " << (k > 0? combinations_count(n, k) : combinations_count(n));
}