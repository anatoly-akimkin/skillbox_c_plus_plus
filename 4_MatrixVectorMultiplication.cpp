// Задание 4. Умножение матрицы на вектор. Реализуйте частный случай умножения матрицы на матрицу, а именно умножение вектора на матрицу. Эта операция распространена в компьютерной индустрии в целом и в компьютерной графике в частности, поэтому это будет хорошим упражнением. Итак, у нас есть четырёхкомпонентный вектор b, представленный с помощью массива, и матрица a размером 4 × 4, представленная в виде двумерного массива. Их произведением будет новый четырёхэлементный вектор c. Его компоненты будут суммой произведений элемента вектора b на строку матрицы a. Индекс столбца при этом равен индексу соответствующей компоненты вектора b, который мы и рассчитываем. Все входные данные, матрица a и вектор b вносятся из пользовательского ввода.  Итоговый вектор c надо вывести в консоль (std::cout). Тип данных элементов — всегда float. Желательно реализовать этот алгоритм с помощью вложенного цикла на умножение колонки.
// Советы и рекомендации. Во внутреннем цикле потребуется аккумулятор, накапливающий значение очередной ячейки результирующего вектора. Каждый раз не забывайте его обнулять до начала расчётов.
// Что оценивается. Программа вычисляет результирующий вектор в соответствии с формулой перемножения матрицы на вектор.

#include <iostream>
#include <limits>

void initialize_matrix(float matrix[][4])
{
    float val;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cin >> val;
            while(std::cin.fail())
            {
                std::cerr << "Integer input expected.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
                std::cin >> val;
            }
            matrix[i][j] = val;
        }
    }
}

void initialize_vector(float vector[])
{
    float val;
    for (int i = 0; i < 4; i++)
    {
        std::cin >> val;
        while(std::cin.fail())
        {
            std::cerr << "Integer input expected.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            std::cin >> val;
        }
        vector[i] = val;
    }
}

void print_matrix(float matrix[][4])
{
    std::cout << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_vector(float vector[])
{
    std::cout << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << vector[i];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() 
{
    float a[4][4], b[4], c[4];

    std::cout << "Enter the values ​​of matrix a:\n";
    initialize_matrix(a);
    print_matrix(a);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the values ​​of vector b:\n";
    initialize_vector(b);
    print_vector(b);

    // Matrix-vector multiplication
    for (int i = 0; i < 4; i++)
    {
        float sum = 0;
        for (int j = 0; j < 4; j++)
        {
            sum += a[i][j] * b[i];
        }
        c[i] = sum;
    }

    std::cout << "The result of multiplying matrix a by vector b:\n";
    print_vector(c);
}