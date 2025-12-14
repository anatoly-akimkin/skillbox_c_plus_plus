// Задание 1. Телефонный справочник. Что нужно сделать. Напишите программу «Телефонный справочник». На вход программе поступают запросы трёх типов:
/* 69-70-30 Ivanov — добавить телефон и фамилию абонента в справочник
69-70-30 — узнать фамилию абонента по номеру телефона
Ivanov — узнать телефон абонента по фамилии */
// Необходимо выводить в консоль ответ на запросы 2 и 3. Обратите внимание, что абоненты по разным номерам могут иметь одинаковые фамилии. В таком случае на запрос 3 необходимо выдать все номера через пробелы. Операции запросов должны работать за O(logn) или O(logn × количество номеров с этой фамилией).
// Чек-лист для проверки задачи. Программа корректно выводит фамилии и списки номеров. Программа использует только заголовочные файлы <iostream>, <string>, <map> и, возможно, вектор.

#include <iostream>
#include <string>
#include <vector>
#include <map>

enum Commands
{
    kInvalid,
    kFindPhoneNumber,
    kFindName,
    kAddToDirectory,
    kExitProgram
};

bool IsValidChar (char c) 
{
    // Letter, ''', '(', ')', ',', '-', '.' or ' '.
    return  (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122) ||
            (c >= 39 && c <= 41) ||
            (c >= 44 && c <= 46) ||
            c == ' '; 
}

bool IsValidName(const std::string &kName)
{
    bool has_only_spaces = true;

    for (int i = 0; i < kName.length(); ++i) { 
        if (!IsValidChar(kName[i])) return false;
        if (kName[i] != ' ') has_only_spaces = false;
    }

    return !has_only_spaces;
}

bool IsValidPhoneNumber(const std::string &kPhone)
{
    int len = kPhone.length();
    for (int i = 0; i < len; ++i)
    {
        if ((kPhone[i] < 48 || kPhone[i] > 57) &&
            kPhone[i] != '#' && kPhone[i] != '-' &&
            (kPhone[i] < 40 || kPhone[i] > 43)) {
            return false;
        }
        // Digit, '#', '-', '*', '+', '(' or ')'.
    }
    return len;
}

Commands GetCommand(const std::string &kInput,
                    std::string &rPhoneNumber, std::string &rName)
{
    if (kInput == "") return Commands::kExitProgram;

    int delimiter = kInput.length();
    for (int i = 0; i < delimiter; ++i)
    {
        if (kInput[i] == ' ') delimiter = i;
    }

    if (delimiter != kInput.length())
    {
        rPhoneNumber = kInput.substr(0, delimiter);
        rName = kInput.substr(delimiter+1, kInput.length()-1-delimiter);
        if (IsValidPhoneNumber(rPhoneNumber) && IsValidName(rName)) return Commands::kAddToDirectory;
    }
    if (IsValidPhoneNumber(kInput)) 
    {
        rPhoneNumber = kInput;
        return Commands::kFindPhoneNumber;
    }
    if (IsValidName(kInput))
    {
        rName = kInput;
        return Commands::kFindName;
    }
    return Commands::kInvalid;
}

int main() 
{
    std::map<std::string, std::string> phone_name_directory;
    std::map<std::string, std::vector<std::string>> name_phone_directory;
    
    while (true)
    {
        std::string input = "", phone_number = "", name = "";
        std::cout << "---> ";
        std::getline(std::cin, input);

        Commands command = GetCommand(input, phone_number, name);
        if (command == Commands::kAddToDirectory)
        {
            std::map<std::string, std::string>::iterator it = phone_name_directory.find(phone_number);
            if (it != phone_name_directory.end())
            {
                std::map<std::string, std::vector<std::string>>::iterator it = name_phone_directory.find(name);
                it->second.push_back(phone_number);
            }
            else
            {
                phone_name_directory[phone_number] = name;
                name_phone_directory[name].push_back(phone_number);
            }
        }
        else if (command == Commands::kFindName)
        {
            std::map<std::string, std::vector<std::string>>::iterator it = name_phone_directory.find(name);
            if (it != name_phone_directory.end())
            {
                for (int i = 0; i < it->second.size(); ++i)
                    std::cout << it->second[i] << std::endl;
            }
            else
            {
                std::cerr << "Not found.\n";
            }
        }
        else if (command == Commands::kFindPhoneNumber)
        {
            std::map<std::string, std::string>::iterator it = phone_name_directory.find(phone_number);
            if (it != phone_name_directory.end())
            {
                std::cout << it->second << std::endl;
            }
            else
            {
                std::cerr << "Not found.\n";
            }
        }
        else if (command == Commands::kExitProgram)
        {
            return 0;
        }
        else if (command == Commands::kInvalid)
        {
            std::cerr << "Invalid input.\nPhone number: use digits and ( ) - * # +\n"
                      << "Name: use uppercase and lowercase Latin letters, spaces, and ( ) . , ' -\n";
        }
    }
}