// Задание 7. Почти «Майнкрафт» (дополнительное задание). Нам предстоит сделать некое подобие «Майнкрафта». Миллионов не обещаю, но это интересная задача на пространственное мышление. У нас есть небольшой квадратный ландшафт, размером 5 × 5 секторов. В каждом секторе располагается блок (столбик) ландшафта, максимальная высота которого — 10 блоков. Текущая высота каждого такого блока задаётся пользователем в начале программы. Итоговая задача: используя трёхмерный массив, вывести в стандартный вывод горизонтальное сечение (или горизонтальный срез) нашего небольшого мира. Сам мир как раз должен быть представлен в виде трёхмерного массива. Его горизонтальный срез — это двумерный массив, который надо отобразить в виде единиц и нулей. 0 — это отсутствие элемента на данном уровне в данной точке, 1 — элемент есть. Уровень среза от 0 до 9 включительно также задаётся в стандартном вводе. Пример выполнения.
/*input matrix of heights:
  5 5 5 5
  4 4 4 4
  3 2 2 3
  1 1 1 1
input slice: 4
  1 1 1 1
  1 1 1 1
  0 0 0 0
  0 0 0 0
input slice: 3
  1 1 1 1
  1 1 1 1
  1 0 0 1
  0 0 0 0*/
// Что оценивается. Использован трёхмерный массив. Пользователь задаёт срез ландшафта, который хочет увидеть (от 0 до 9). Выводится срез размером 5 × 5, состоящий из 0 и 1. Советы и рекомендации. При печати потребуется проверять содержимое трёхмерного массива. При уже известном значении уровня level проверка выглядит так:
/*if (world[i][j][level]) 
{ 
//печатаем 1 
} 
else 
{ 
//печатаем 0 
}*/

#include <iostream>
#include <limits>
#include <string>

int input_val()
{
    while(true)
    {
        int val;
        std::cin >> val;
                
        if (std::cin.fail())
        {
            std::cerr << "Integer input expected.\n";
            std::cin.clear();
            while(std::cin.peek() != ' ' && std::cin.peek() != '\n') std::cin.ignore();
            continue;
        }

        return val;
    }
}

void initialize_matrix(int matrix[][5][10])
{
    int height;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            height = input_val();
            while (height < 0 || height > 10) 
            {
                std::cout << "The value is out of bounds.\n";
                height = input_val();
            }
        
            for (int k = 0; k < 10; k++)
            {
                if (k < height)
                {
                    matrix[i][j][k] = 1;
                }
                else
                {
                    matrix[i][j][k] = 0;
                }
            }
        }
    }
}

void print_matrix(int matrix[][5][10], int k)
{
    std::cout << std::endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            std::cout << matrix[i][j][k] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    int world[5][5][10];
    std::cout << "Input matrix of heights:\n";
    initialize_matrix(world);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int level = 0;
    while (level != -1)
    {
        std::cout << "Input slice: ";
        level = input_val();
        while (level < -1 || level > 9) 
        {
            std::cout << "The value is out of bounds.\n";
            level = input_val();
        }

        if (level != -1) 
        {
            print_matrix(world, level);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}