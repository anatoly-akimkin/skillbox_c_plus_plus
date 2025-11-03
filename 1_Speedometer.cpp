// Задание 1. Спидометр. Что нужно сделать. Реализуйте цифровой спидометр автомобиля. Сама модель автомобиля, которую нужно будет воссоздать, весьма проста. Начальная скорость — 0 км/ч. Пользователь вводит в стандартный ввод разницу (дельту) в скорости, и результирующая скорость показывается на спидометре в стандартный вывод. Так происходит до той поры, пока машина снова не остановится, то есть пока скорость не станет меньше или равна нулю (сравнение должно происходить с дельтой в 0,01). Диапазон возможных значений скорости машины от 0 до 150 км/ч. Сам показатель спидометра вместе с единицами измерения требуется записывать в отдельную строку-буфер, которая потом и будет показываться на экране. Точность отображения скорости — до 0,1 км/ч. Пример работы программы:
/*Speed delta:30
Speed: 30.0
Speed delta:20.2
Speed: 50.2
Speed delta:100
Speed: 150.0
Speed delta:-22.24
Speed: 127.8*/
// Рекомендации. Используйте цикл do while для организации постоянного опроса пользователя. Для отображения числа с нужной точностью воспользуйтесь функцией std::sprintf(speed_str, "%.1f", speed_value); где speed_str — строка, в которую функция sprintf «печатает» значение скорости (speed_value) с одним знаком после десятичной точки (%.1f). 

#include <iostream>

void print(double val)
{
    char speed_str[6];
    std::sprintf(speed_str, "%5.1f", val);
    std::cout << "Speed: " << speed_str << std::endl;
}

double str_to_double(std::string str)
{
    try 
    {
        return stod(str);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << ": invalid argument exception.\n";
        return 0;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << e.what() << ": out of range exception.\n";
        return 0;
    }
}

int main() 
{
    double speed_value = 0;
    std::string speed_delta;
    
    do
    {
        print(speed_value);
        std::cout << "Speed delta: ";
        std::cin >> speed_delta;
        speed_value += str_to_double(speed_delta);
        if (speed_value - 150.0 > 0.01)
        {
            speed_value = 150.0;
            // std::cout << "Maximum speed!\n";
        }
    } while (speed_value > 0.01);

    print(0);
}