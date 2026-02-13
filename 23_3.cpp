// Задание 3. Анализ заполненности вагонов в поезде* (дополнительное задание). Что нужно сделать. В поезде всего 10 вагонов. В каждом из этих вагонов может находиться до 20 пассажиров — это их оптимальное количество. Проанализируйте количество людей в каждом вагоне и сначала сообщите об излишне заполненных вагонах, далее о вагонах с пустыми пассажирскими местами. В заключение выведите общее количество пассажиров во всех вагонах. При старте программы пользователь вводит количество пассажиров в каждом вагоне. Замечания о вагонах должны выводиться в стандартную консоль. При выполнении задания пользоваться нельзя напрямую пользоваться for-циклами, только опосредованно, через макросы.
// Советы и рекомендации. С помощью макроса реализуйте модульный способ вызова функции над элементами массива. Сами функции реализуйте отдельно, в виде обычных классических функций (не макросов). Модульный способ вызова функции печати текста через макрос:
/* #define CALL(func) { func("Hello, Skillbox!"); }

void print(std::string str) {   
std::cout << str << std::endl;
}

int main() {
   CALL(print);
   return 0;
} */
// Обязательно просмотрите итоговый код после препроцессинга из CLion с помощью Shift-Shift → Preprocess current TU.
// Что оценивается. Корректность работы программы. Модульность и элегантность решения с помощью макросов.

#include <iostream>
#include <limits>
#include <vector>
#include <string>

#define FOR_I_LOOP(num_iterations, loop_body) do { \
    for (int i = 0; i < num_iterations; ++i) loop_body \
} while(0)

int GetInt(int min_val = 0, int max_val = 99)
{
    int val;
    std::cout << "---> ";
    std::cin >> val;
    while (std::cin.fail() || val < min_val || val > max_val) {
        std::cerr << "Invalid value.\n---> ";
        if (std::cin.fail()) std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> val;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

int GetValForComparison() 
{
    return 20;
}

bool MoreThan(int val1, int val2) 
{
    if (val1 > val2) return true;
    return false;
}

bool LessThan(int val1, int val2) 
{
    if (val1 < val2) return true;
    return false;
}

int main()
{
    int train[10]; 
    int train_size = 10;
    
    FOR_I_LOOP(train_size, { std::cout << i << " car "; train[i] = GetInt(); });
    std::cout << std::string(30, '-') << std::endl;

    std::vector<int> overloaded_cars;
    FOR_I_LOOP(train_size, { if (MoreThan(train[i], GetValForComparison())) overloaded_cars.push_back(i); });
    
    if (overloaded_cars.size() > 0) std::cout << "Excessively filled cars:\n";
    FOR_I_LOOP(overloaded_cars.size(), { printf("%2d car - %2d passengers\n", overloaded_cars[i], train[overloaded_cars[i]]); });
    
    std::vector<int> underloaded_cars;
    FOR_I_LOOP(train_size, { if (LessThan(train[i], GetValForComparison())) underloaded_cars.push_back(i); });

    if (underloaded_cars.size() > 0) std::cout << "Cars with empty seats:\n";
    FOR_I_LOOP(underloaded_cars.size(), { printf("%2d car - %2d passengers\n", underloaded_cars[i], train[underloaded_cars[i]]); });

    if ((overloaded_cars.size() + underloaded_cars.size()) > 0) std::cout << std::string(30, '-') << std::endl;
    int total_passengers = 0;
    FOR_I_LOOP(train_size, { total_passengers += train[i]; });
    std::cout << "Total number of passengers: " << total_passengers << std::endl;
}