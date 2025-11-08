// Задача 3. Что нужно сделать. Напишите рекурсивную функцию, которая принимает большое число n типа long long и переменную ans, а возвращает void. После завершения работы функции в переменной ans должно оказаться количество чётных цифр в записи числа n. Пример:
/* int ans;
evendigits(9 223 372 036 854 775 806, ans); //ans == 10 */
// Чек-лист для проверки задачи. Функция принимает корректные типы данных, тип возвращаемого значения —  void. Функция не использует библиотек кроме <iostream>. Функция рекурсивная. Функция содержит параметр по ссылке.

#include <iostream>
#include <limits>

void ll_input(long long &val)
{
    std::cin >> val;
    while (std::cin.fail())
    {
        std::cerr << "Bad input.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> val;
    }
}

void evendigits(long long &n, int &ans)
{
    if (n % 2 == 0) ++ans;
    n /= 10;
    if (n > 0) evendigits(n, ans);
}

int main()
{
    std::cout << "Enter an integer: "; // 9223372036854775806
    long long n;
    ll_input(n);
    
    int ans = 0;
    evendigits(n, ans);

    std::cout << "There are " << ans << " even digits in the number.";
}