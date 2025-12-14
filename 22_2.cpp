// Задание 2. Регистратура. Что нужно сделать. Напишите программу «Регистратура». На вход программе приходят строки с фамилиями или строка Next. Пришедшие люди становятся в очередь, а по запросу Next необходимо вызвать в регистратуру человека с фамилией, идущей первой в лексикографическом порядке (по алфавиту), и вывести его фамилию на экран. Фамилии пациентов могут повторяться. Каждый запрос (на добавление и вывод) должен работать за O(logn). Пример:
/* ← Sidorov
← Ivanov
← Ivanov
← Petrov
← Next
→ Ivanov
← Next
→ Ivanov
← Next
→ Petrov */
// Чек-лист для проверки задачи Программа корректно выводит фамилии в лексикографическом порядке. Программа использует только заголовочные файлы <iostream>, <string>, <map>. 

#include <iostream>
#include <string>
#include <map>

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

std::string ExtractName(std::map<std::string, int> &rQueueMap)
{
    std::map<std::string, int>::iterator it = rQueueMap.begin();
    std::string name = it->first;
    if (it->second > 1)
    {
        --(it->second);
    }
    else {
        rQueueMap.erase(it);
    }
    return name;
}

int main()
{
    std::map<std::string, int> queue_map;
    std::string input_str = "";

    while(true) {
        std::cout << "--> ";
        std::getline(std::cin, input_str);

        if (input_str == "Exit" || input_str == "exit") {
            return 0;
        }
        else if (input_str == "Next" || input_str == "next") {
            if (queue_map.empty()) {
                std::cerr << "The queue is empty.\n";
            }
            else {
                std::cout << ExtractName(queue_map) << std::endl;
            }
        }
        else if (IsValidName(input_str)) {
            std::map<std::string, int>::iterator it = queue_map.find(input_str);
            if (it == queue_map.end()) {
                queue_map[input_str] = 1;
            }
            else {
                ++(it->second);
            }
        }
        else {
            std::cerr << "Invalid request.\n";
        }

    }
}