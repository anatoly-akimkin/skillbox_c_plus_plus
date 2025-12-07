// 3. Математический вектор. Что нужно сделать. Реализуйте структуру двумерного математического вектора и основные операции над ним. Обе координаты вектора (x и y) должны быть вещественными числами. Начиная работу с программой, пользователь вводит команду. Затем в зависимости от команды пользователь вводит аргументы. Это могут быть как векторы, так и обычные скалярные значения. Результат помещается в стандартный вывод. Это тоже может быть или вектор, или скаляр. Реализуйте в виде отдельных функций операции:
/* сложение двух векторов — команда add;
вычитание двух векторов — команда subtract;
умножение вектора на скаляр — команда scale;
нахождение длины вектора — команда length;
нормализация вектора — команда normalize. */
// Советы и рекомендации. Для выбора команды используйте конструкцию вида if (operation == "add"). Тут так и напрашиваются отдельные функции для каждой операции.

#include <iostream>
#include <limits>
#include <string>
#include <cmath>

struct MathVector
{
    double x = 0;
    double y = 0;
};

MathVector Add(const MathVector &kFirstVec, const MathVector &kSecondVec)
{
    MathVector new_vector;
    new_vector.x = kFirstVec.x + kSecondVec.x;
    new_vector.y = kFirstVec.y + kSecondVec.y;
    return new_vector;
}

MathVector Subtract(const MathVector &kFirstVec, const MathVector &kSecondVec)
{
    MathVector new_vector;
    new_vector.x = kFirstVec.x - kSecondVec.x;
    new_vector.y = kFirstVec.y - kSecondVec.y;
    return new_vector;
}

MathVector Scale(const MathVector &kVector, double scalar)
{
    MathVector new_vector;
    new_vector.x = kVector.x * scalar;
    new_vector.y = kVector.y * scalar;
    return new_vector;
}

double Length(const MathVector &kVector)
{
    return sqrt(pow(kVector.x, 2) + pow(kVector.y, 2));
}

MathVector Normalize(const MathVector &kVector)
{
    MathVector normalized_v;
    double vector_len = Length(kVector);
    normalized_v.x = kVector.x / vector_len;
    normalized_v.y = kVector.y / vector_len;
    return normalized_v;
}

double GetDouble()
{
    double val;
    std::cin >> val;
    while (std::cin.fail())
    {
        std::cerr << "Invalid value.\n---> ";
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> val;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

MathVector GetMathVector()
{
    double x;
    double y;
    std::cin >> x >> y;
    while (std::cin.fail())
    {
        std::cerr << "Invalid value.\n---> ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> x >> y;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    MathVector vector;
    vector.x = x;
    vector.y = y;
    return vector;
}

void PrintResult(const MathVector &kVector)
{
    std::cout << "Result: ";
    printf("(%.2f, %.2f)", kVector.x, kVector.y);
    std::cout << std::endl;
}

int main()
{
    std::cout << "Operation (add, subtract, scale, length, normalize): ";
    std::string operation;
    std::getline(std::cin, operation);

    if (operation == "add")
    {
        std::cout << "Enter the coordinates of vector 1: ";
        MathVector vec1 = GetMathVector();
        std::cout << "Enter the coordinates of vector 2: ";
        MathVector vec2 = GetMathVector();
        MathVector res_vec = Add(vec1, vec2);
        PrintResult(res_vec);
    }
    else if (operation == "subtract")
    {
        std::cout << "Enter the coordinates of vector 1: ";
        MathVector vec1 = GetMathVector();
        std::cout << "Enter the coordinates of vector 2: ";
        MathVector vec2 = GetMathVector();
        MathVector res_vec = Subtract(vec1, vec2);
        PrintResult(res_vec);
    }
    else if (operation == "scale")
    {
        std::cout << "Enter the coordinates of vector: ";
        MathVector vec = GetMathVector();
        std::cout << "Enter the scalar value: ";
        double val = GetDouble();
        MathVector res_vec = Scale(vec, val);
        PrintResult(res_vec);
    }
    else if (operation == "length")
    {
        std::cout << "Enter the coordinates of vector: ";
        MathVector vec = GetMathVector();
        double res = Length(vec);
        std::cout << "Result: " << res << std::endl;
    }
    else if (operation == "normalize")
    {
        std::cout << "Enter the coordinates of vector: ";
        MathVector vec = GetMathVector();
        MathVector res_vec = Normalize(vec);
        PrintResult(res_vec);
    }
    else
    {
        std::cerr << "Invalid operation.\n";
        return 1;
    }
}
