// Задание 1. Запись в ведомость учёта. Что нужно сделать. В одном из прошлых заданий вы уже создавали программу для чтения и анализа ведомости выплат. Теперь попробуйте создать простую программу для записи в эту ведомость. Формат ведомости прежний: 
// Сначала идёт имя и фамилия получателя денежных средств, далее — дата выдачи в формате ДД.ММ.ГГГГ. Запись завершает сумма выплаты в рублях. Данные разделяются между собой пробелами. В конце каждой записи должен быть расположен перевод строки. При старте программы пользователь последовательно вводит данные для новой записи, которые затем записываются в файл в текстовом режиме. Программа должна добавлять новые записи в конец файла, не удаляя его текущее содержимое.
// Рекомендации. Валидируйте введённые файлы перед записью, хотя бы минимально. Для валидации даты в указанном формате можно использовать функции std::stoi и std::subtr с корректно указанным диапазоном символов в дате. К примеру, вызов std::stoi(date.substr(3, 2)) вычленит из строковой даты целочисленный месяц для последующего анализа.

#include <iostream>
#include <fstream>
#include <string>

bool valid_name(const std::string &n)
{
    for (int i = 0; i < n.length(); ++i)
    {
        if (n[i] < 32 || (n[i] > 32 && n[i] < 39)
            || (n[i] > 41 && n[i] < 44) || (n[i] > 46 && n[i] < 65) 
            || (n[i] > 90 && n[i] < 97) || n[i] > 122)
        {
            std::cerr << "Invalid name.\nUse uppercase and lowercase Latin letters, spaces, and ().,'-\n--> ";
            return false;
        }
    }
    return true;
}

bool bad_date()
{
    std::cerr << "Invalid date format\n--> ";
    return 0;
}

bool valid_date(const std::string &date)
{

    if (date == "") return true;
    if (date.length() != 10) return bad_date();
    for (int i = 0; i < 10; ++i)
    {
        if ((i != 2 && i != 5 && (date[i] < 48 || date[i] > 57))
            || ((i == 2 || i == 5) && date[i]  != '.')) return bad_date();
    }
    
    int m = std::stoi(date.substr(3, 2));
    if (m < 1 || m > 12) return bad_date();

    int d = std::stoi(date.substr(0, 2));
    int d_max;
    if (m == 2)
    {
        int y = std::stoi(date.substr(6, 4));
        d_max = (y % 4 == 0)? 29 : 28;
    }
    else
    {
        if (m % 2 == (m > 7)? 0 : 1)
        {
            d_max = 31;
        }
        else 
        {
            d_max = 30;
        }
    }
    if (d < 1 || d > d_max) return bad_date();

    return true;
}

bool valid_ll_int(std::string &n)
{
    if (n == "") return true;
    bool is_zero = true;
    for (int i = 0; i < n.length(); ++i)
    {
        if (n[i] < 48 || n[i] > 57) 
        {
            std::cerr << "Invalid argument\n--> ";
            return false;
        }
        if (n[i] != '0') is_zero = false;
    }
    if (is_zero) std::cerr << "Invalid value: 0\n--> ";
    return !is_zero;
}

int main()
{
    while (true)
    {
        std::string input = "";
        std::string buffer = "";

        std::cout << "Recipient's full name (or leave blank to exit):\n--> ";
        do
        {
            std::getline(std::cin, input);
        } while (!valid_name(input));
        if (input == "") return 0;
        buffer += input + " ";

        std::cout << "Date of issue (DD.MM.YYYY format):\n--> ";
        do
        {
            std::getline(std::cin, input);
        } while (!valid_date(input));
        if (input == "") continue;
        buffer += input + " ";

        std::cout << "Payment amount (RUB):\n--> ";
        do
        {
            std::getline(std::cin, input);
        } while (!valid_ll_int(input));
        if (input == "") continue;
        long long int p_sum = std::stoll(input);

        std::string path = "statement.txt";
        // std::cout << "File path:\n--> "; // C:\\code\\module20\\statement.txt
        // std::cin >> path;
        std::ofstream file(path, std::ios::app);
        if (file.is_open())
        {
            file << buffer << p_sum << std::endl;
            file.close();
            std::cout << "The entry has been added.\n\n";
        }
        else
        {
            std::cerr << "Failed to open a file.\n";
            return 1;
        }
    } 
}