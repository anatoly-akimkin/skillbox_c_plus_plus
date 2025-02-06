#include <iostream>
#include <string>

// Задание 1. Многоквартирный дом. Что нужно сделать. На вход программе поступают десять фамилий в формате строк. Это фамилии жильцов квартир с первой по десятую. Необходимо прочитать эти фамилии и записать в одномерный массив. Далее пользователь вводит три номера квартир. Необходимо вывести в консоль фамилию жильца, проживающего в этой квартире. Если пользователь введёт некорректный номер квартиры, необходимо сообщить ему об этом. Пример

/*← SidorovA 
← IvanovA 
← PetrovA 
← SidorovB 
← IvanovB 
← PetrovB 
← SidorovC 
← IvanovC 
← PetrovC 
← SidorovD 
←10 
→SidorovD 
←1 
→SidorovA 
←5 
→IvanovB*/

// Что оценивается. Используется массив строк для хранения данных. В коде не используются библиотеки, кроме <iostream> и <string>. Программа проверяет доступность элемента по индексу и выдаёт корректный результат.

int main() 
{
    std::string residents[10];
    std::cout << "Enter 10 residents' names: \n";

    for (int i = 0; i < 10; i++)
    {
        std::cin >> residents[i];
    }

    std::cout << "Enter 3 apartment numbers: \n";
    
    for (int i = 0; i < 3; i++)
    {
        int num;
        std::cin >> num;

        if (num > 0 && num <= 10) 
        {
            std::cout << residents[num-1] << std::endl;
        }
        else 
        {
            std::cout << "There is no apartment with this number.\n";
        }
    } 
}