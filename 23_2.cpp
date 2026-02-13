// Задание 2. Вывод времени года. Что нужно сделать. Используя макросы вместе с условными директивами прекомпиляции (#if / #endif), реализуйте простую программу по выводу названия времени года в консоль. Пользователь программы, который будет иметь дело с вашим кодом, в этом случае тоже программист. С помощью определения одного из макросов (в самом коде): SPRING, SUMMER, AUTUMN или WINTER он задаёт сезон, название, которое хочет увидеть на экране. При компиляции и запуске программы на экране должно появиться название именно этого сезона и только его.
// Советы и рекомендации. Так как препроцессор работает до компиляции, то в #if/#endif-директивы вы можете обернуть всю функцию main сразу. 
// Что оценивается. Корректность работы программы при разных заданных дефинициях макросов.

#include <iostream>

// #define SPRING
#define SUMMER
// #define AUTUMN
// #define WINTER

// #if defined SPRING
// int main() { std::cout << "Spring\n"; }
// #elif defined SUMMER
// int main() { std::cout << "Summer\n"; }
// #elif defined AUTUMN
// int main() { std::cout << "Autumn\n"; }
// #elif defined WINTER
// int main() { std::cout << "Winter\n"; }
// #else
// int main() { std::cerr << "Macro of the season is not defined"; }
// #endif

int main() 
{
#if defined SPRING
    std::cout << "Spring\n";
#elif defined SUMMER
    std::cout << "Summer\n";
#elif defined AUTUMN
    std::cout << "Autumn\n";
#elif defined WINTER
    std::cout << "Winter\n";
#endif
}

