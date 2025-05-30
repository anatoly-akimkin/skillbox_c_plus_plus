// 8. Морской бой (дополнительное задание). Требуется реализовать упрощённую игру в морской бой. Игровое поле размером 10 на 10 клеток. Участвуют два игрока. В арсенале каждого из них 4 маленьких кораблика размером в одну клетку, 3 небольших корабля размером в две клетки, 2 средних корабля размером в три клетки и один большой корабль размером в четыре клетки. Для простоты клетки поля пронумерованы по вертикали от 0 до 9 и по горизонтали от 0 до 9. Мы не будем использовать классические наименования клеток, такие как B4, C6, а просто два индекса. Вначале игроки по очереди расставляют корабли, начиная с самых маленьких и заканчивая большими. Маленькие корабли в одну клетку расставляются с помощью указания одной клетки-точки на поле, к примеру 2,1. Корабли размерностью от двух клеток и выше расставляются с помощью координат их начала и конца, к примеру: 0,1–0,3. Корабли могут быть установлены только строго вертикально или горизонтально. Установка корабля по диагонали недопустима, об этом тоже надо сообщить пользователю. Если корабль не может быть размещён на заданных клетках из-за того, что он столкнётся с другим кораблём (окажется на его клетках) или выйдет за пределы поля, то игроку должно быть сделано предупреждение, после которого он должен переставить корабль на новые валидные координаты. В нашем упрощённом варианте игры мы не будем обсчитывать соприкосновения кораблей друг с другом, а потому корабли вполне можно будет размещать друг к другу вплотную, борт к борту. После того как все корабли расставлены, начинается игра. Игроки по очереди атакуют друг друга, называя координаты выстрела. После выстрела в консоль выводится информация о его результате: попал или мимо. Если выстрел успешен, клетка, на которой был корабль (или его фрагмент), затирается и становится пустой. Игра заканчивается тогда, когда все корабли одной из сторон будут полностью уничтожены. Как только это произойдёт, в консоль выводится информация с номером игрока, который победил.
// Советы и рекомендации. Действия игроков практически одинаковые, их можно объединить в функции. В программе достаточно иметь два поля, по одному на каждого игрока. Лучше создать три отдельные функции: одну для размещения одного корабля, еще одну как обёртку над первой (она будет размещать все корабли), а третью для удара по координате. Также вам потребуются два глобальных массива для двух отдельных участков моря:
/*bool field_1[10][10]; 
bool field_2[10][10];*/
// Что оценивается. Корабли расставляются правильно. Есть возможность выиграть. Реализован понятный и удобный для пользователя интерфейс игры.

/*4 1 5 3 8 2 9 9 1 1 1 0 4 8 3 8 6 8 6 9 0 9 2 9 6 5 4 5 8 4 8 7
9 0 1 1 3 7 5 7 7 1 7 0 7 4 6 4 8 6 8 5 1 4 1 6 1 9 3 9 4 3 4 6
4 1 5 3 8 2 9 9 1 1 1 0 4 8 3 8 6 8 6 9 0 9 2 9 6 5 4 5 8 4 8 7 9 0 1 1 3 7 5 7 7 1 7 0 7 4 6 4 8 6 8 5 1 4 1 6 1 9 3 9 4 3 4 6 as ds 56 95 fgh 5fgh 5 4 1 5 3 8 2 9 9 1 1 1 0 4 8 3 8 6 8 6 9 0 9 2 9 6 5 4 5 8 4 8 7 9 0 1 1 3 7 5 7 7 1 7 0 7 4 6 4 8 6 8 5 1 4 1 6 1 9 3 9 4 3 4 6 as ds 56 95 fgh 5fgh 5*/

#include <iostream>
#include <limits>

void initialize_matrix(int matrix[][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void print_matrix(int matrix[][10])
{
    std::cout << std::endl;
    for (int i = -1; i < 11; i++)
    {
        for (int j = -1; j < 11; j++)
        {
            if (i > -1 && i < 10)
            {
                if (j > -1 && j < 10)
                {
                    switch (matrix[i][j])
                    {
                        case -1:
                        {
                            std::cout << "O ";
                            break;
                        }
                        case -2:
                        {
                            std::cout << "X ";
                            break;
                        }
                        // case 0:
                        // {
                        //     std::cout << "~ ";
                        //     break;
                        // }
                        // case 1:
                        // {
                        //     std::cout << "@ ";
                        //     break;
                        // }
                        default:
                            std::cout << "~ ";
                            break;
                    }
                }
                else
                {
                    std::cout << i << " ";
                }
            } 
            else
            {
                if (j > -1 && j < 10)
                {
                    std::cout << j << " ";
                }
                else
                {
                    std::cout << "  ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

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

        if (val >= 0 && val < 10) return val;
        std::cout << "The value is out of bounds.\n";
    }
}

bool valid_point(int matrix[][10], int x, int y)
{
    if (matrix[y][x] == 0) 
    {
        return true;
    }
    else
    {
        std::cout << "The place is occupied. Try other coordinates.\n";
        return false;
    }
}

bool valid_line(int matrix[][10], int a1, int a2, int b1, int b2, int length)
{
    if (a1 == a2 ^ b1 == b2)
    {
        if ((b2 - b1 + 1) == length)
        {
            bool free_space = true;
            for (int i = 0; free_space && i < length; i++) 
            {
                if (not valid_point(matrix, (a1), b1+i)) free_space = false;
            }
            if (free_space) 
            {
                for (int i = 0; i < length; i++) matrix[b1+i][a1] = 1;
                return true;
            }
            else 
            {
                return false;
            }
        }
        else if ((a2 - a1 + 1) == length)
        {
            bool free_space = true;
            for (int i = 0; free_space && i < length; i++) 
            {
                if (not valid_point(matrix, (a1+i), b1)) free_space = false;
            }
            if (free_space) 
            {
                for (int i = 0; i < length; i++) matrix[b1][a1+i] = 1;
                return true;
            }
            else 
            {
                return false;
            }
        }
        else
        {
            std::cout << "Invalid ship length.\n";
            return false;
        }
    }
    else
    {
        std::cout << "The ship cannot be placed diagonally.\n";
        return false;
    }
}

void place(int matrix[][10], int length)
{
    if (length == 1)
    {
        std::cout << "Enter the coordinates of the ship.\n";
        while (true)
        {
            
            int x = input_val();
            int y = input_val();
            //while(std::cin.peek() != '\n') std::cin.ignore();

            if (valid_point(matrix, x, y)) 
            {
                matrix[y][x] = 1;
                break;
            }
        }
    }
    else
    {
        std::cout << "Enter the coordinates of the ship's bow and stern.\n";
        int x1, x2, y1, y2;
        while (true)
        {
            x1 = input_val();
            y1 = input_val();
            x2 = input_val();
            y2 = input_val();
            //while(std::cin.peek() != '\n') std::cin.ignore();
            if (x2 < x1) std::swap(x1, x2);
            if (y2 < y1) std::swap(y1, y2);

            if (valid_line(matrix, x1, x2, y1, y2, length)) break;
        }
    }
}

void arrange(int matrix[][10])
{
    print_matrix(matrix);
    for (int i = 4; i > 0; i--)
    {
        std::cout << "Place " << i << " single-deck ships.\n";
        place(matrix, 1);
        // print_matrix(matrix);
    }
    for (int i = 3; i > 0; i--)
    {
        std::cout << "Place " << i << " double-deck ships.\n";
        place(matrix, 2);
        // print_matrix(matrix);
    }
    for (int i = 2; i > 0; i--)
    {
        std::cout << "Place " << i << " three-deck ships.\n";
        place(matrix, 3);
        // print_matrix(matrix);
    }
    std::cout << "Place a four-deck ship.\n";
    place(matrix, 4);
    // print_matrix(matrix);
}

void shoot(int matrix[][10], int target, int health[])
{
    std::cout << "Enter the shot coordinates.\n";
    print_matrix(matrix);
    while (true)
    {
        int x = input_val();
        int y = input_val();
        // while(std::cin.peek() != '\n') std::cin.ignore();

        if (matrix[y][x] == 0)
        {
            std::cout << "You missed!\n";
            matrix[y][x] = -1;
            break;
        }
        else if (matrix[y][x] == 1)
        {
            std::cout << "You hit the target!\n";
            matrix[y][x] = -2;
            health[target]--;
            break;
        }
        else
        {
            std::cout << "Try another place.\n";
        }
    }
}

int main()
{
    int field_1[10][10]; 
    initialize_matrix(field_1);
    std::cout << "__________________________________\n";
    std::cout << "\n>> PLAYER 1 <<\n";
    arrange(field_1);

    int field_2[10][10];
    initialize_matrix(field_2);
    std::cout << "__________________________________\n";
    std::cout << "\n>> PLAYER 2 <<\n";
    arrange(field_2);

    int player = 0;
    int player_health[] {20, 20};
    for (int i = 0; player_health[player] > 0 && i < 199; i++)
    {
        std::cout << "__________________________________\n";
        std::cout << "\n>> PLAYER " << player+1 << " <<  |  Your HP: " << player_health[player] << std::endl;
        player = (player == 0)? 1 : 0;
        std::cout << "                |  Target's HP: " << player_health[player] << std::endl;
        std::cout << "__________________________________\n\n";
        shoot(((player == 0)? field_1 : field_2), player, player_health);
    }

    print_matrix((player == 0)? field_1 : field_2);
    std::cout << "All ships of PLAYER " << player+1 << " sank!\n" << 
                "Congratulations, PLAYER " << ((player == 0)? 1 : 0) + 1 << "!\n";
}