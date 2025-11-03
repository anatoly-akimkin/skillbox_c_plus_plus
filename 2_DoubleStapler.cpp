// Задание 2. Сшиватель дробных чисел. Что нужно сделать. Напишите небольшую программу. Из целой и дробной частей числа, которые в отдельности вводит пользователь, составьте новое число с плавающей точкой (типа double) и выведите это число обратно в консоль для проверки. Целая часть — это часть числа, которая находится до точки (запятой), дробная — после.
// Рекомендации. Вам потребуется функция StringToDouble — std::stod. Она принимает на вход строку, содержащую в себе число.

#include <iostream>
#include <cmath>

int main()
{
    double result;
    std::string integer;
    std::string fractional;

    std::cout << "Enter the integer part: ";
    std::cin >> integer;
    std::cout << "Enter the fractional part: .";
    std::cin >> fractional;

    try 
    {
        result = std::trunc(stod(integer)) + stod("." + fractional);
        std::cout << result << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << ": invalid argument exception.\n";
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << e.what() << ": out of range exception.\n";
    }
}