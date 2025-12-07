// 1. Ведомость учёта. Что нужно сделать. Вы уже создавали программу чтения и записи ведомости. Теперь её нужно обобщить и дополнить использованием структур. Формат ведомости прежний:
/* сначала — имя и фамилия получателя денег;
далее — дата выдачи в формате ДД.ММ.ГГГГ;
затем — сумма выплаты в рублях. */
// Данные разделяются пробелами. В конце каждой записи должен быть перевод строки. Структура данных должна соответствовать этому формату. При старте программы пользователь отправляет команду: list или add. Команда list осуществляет чтение из файла ведомости, как и прежде, только уже в структуре данных, и отображает их на экране. Команда add добавляет новую запись в конец ведомости.
// Советы и рекомендации. Чтобы определить, где заканчивается файл, используйте функцию file.eof(). Из-за завершающего переноса строки при чтении данных из файла стоит отдельно прочитать имя получателя денег. Если после чтения имени получателя денег признак file.eof() принял значение true — значит, файл закончился. Используйте вектор структур. Для выбора команды потребуется подобная конструкция:
/* if (command == "list")
{
…
} */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct Entry
{
    std::string name = "";
    std::string date = "";
    long long int sum = 0;
};

bool IsValidChar (char c)
{
    return  (c >= 65 && c <= 90) ||  // uppercase letter
            (c >= 97 && c <= 122) || // lowercase letter
            (c >= 39 && c <= 41) ||  // ' ( )
            (c >= 44 && c <= 46) ||  // , - .
            c == ' '; 
}

bool IsValidName(const std::string &kName)
{
    bool is_empty = true;

    for (int i = 0; i < kName.length(); ++i) { 
        if (!IsValidChar(kName[i])) return false;
        if (kName[i] != ' ') is_empty = false;
    }

    return !is_empty;
}

bool IsValidDate(const std::string &kDate)
{
    if (kDate.length() != 10) return false;
    for (int i = 0; i < 10; ++i)
    {
        if ((i != 2 && i != 5 && (kDate[i] < 48 || kDate[i] > 57))
            || ((i == 2 || i == 5) && kDate[i]  != '.')) return false;
    }
    
    int month = std::stoi(kDate.substr(3, 2));
    if (month < 1 || month > 12) return false;

    int day = std::stoi(kDate.substr(0, 2));
    int days_max;
    if (month == 2)
    {
        int year = std::stoi(kDate.substr(6, 4));
        days_max = (year % 4 == 0)? 29 : 28;
    }
    else
    {
        if (month % 2 == (month > 7)? 0 : 1)
        {
            days_max = 31;
        }
        else 
        {
            days_max = 30;
        }
    }
    if (day < 1 || day > days_max) return false;

    return true;
}

bool IsValidSum(const std::string &kSum)
{
    for (int i = 0; i < kSum.length(); ++i)
    {
        if (kSum[i] < 48 || kSum[i] > 57) 
        {
            return false;
        }
    }
    return true;
}

bool ReadFromFile(std::ifstream &rFile, std::vector<Entry> &rStatement)
{
    Entry entry_i;
    std::string buffer;
    while (std::getline(rFile, buffer))
    {
        if (buffer == "") return false;
        int name_len = 0;
        while (buffer[name_len+1] < 48 || buffer[name_len+1] > 57) {
            ++name_len;
        }
        entry_i.name = buffer.substr(0, name_len);

        std::stringstream ss(buffer.substr(name_len));
        ss >> entry_i.date >> entry_i.sum;
        if (name_len == 0 || ss.fail()) return false;

        rStatement.push_back(entry_i);
    }
    return true;
}

void GetString(std::string &rBuffer, const std::string &kStrToPrint = "")
{
    std::cout << kStrToPrint;
    std::getline(std::cin, rBuffer);
}

bool HandleError(const std::string &kStrToPrint)
{
    std::cerr << kStrToPrint;
    return 1;
}

int main()
{
    std::string command;
    std::cout << "Command (list or add):\n---> ";
    std::getline(std::cin, command);
    if (command == "") return 0;
    int dash_num = 50;
    std::cout << std::string(dash_num, '-') << std::endl;

    std::string path = "accounting_statement.txt";
    if (command == "list")
    {

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open a file.\n";
            return 1;
        }

        std::vector<Entry> statement;
        if (!ReadFromFile(file, statement)) { 
            std::cerr << "Failed to read file.\n";
            return 1;
        }
        file.close();

        Entry max_entry;
        int total_sum = 0;
        for (int i = 0; i < statement.size(); ++i)
        {
            std::cout << statement[i].name << " " << statement[i].date 
                      << " " << statement[i].sum << std::endl;
            total_sum += statement[i].sum;
            if (max_entry.sum < statement[i].sum) max_entry = statement[i];
        }
        std::cout << std::string(dash_num, '-') << std::endl;

        std::cout << "The total amount of payments: " << total_sum << std::endl 
                  << "The largest recipient of funds: " 
                  << max_entry.name << " (" << max_entry.sum << ")" << std::endl << std::endl;
    }
    else if (command == "add")
    {
        std::string input;
        Entry buffer;

        GetString(input, "Recipient's full name:\n---> ");
        if (input == "") return 0;
        if (!IsValidName(input)) return HandleError("Invalid name.\nUse uppercase and lowercase Latin letters, spaces, and ().,'-\n");
        buffer.name = input;

        GetString(input, "Date of issue (DD.MM.YYYY format):\n---> ");
        if (input == "") return 0;
        if (!IsValidDate(input)) return HandleError("Invalid date format\n");
        buffer.date = input;

        GetString(input, "Payment amount (RUB):\n---> ");
        if (input == "") return 0;
        if (!IsValidSum(input)) return HandleError("Invalid argument\n");
        buffer.sum = std::stoll(input);

        std::ofstream file(path, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Failed to open a file.";
            return 1;
        }
        file << buffer.name << " " << buffer.date << " " << buffer.sum << std::endl;
        file.close();
        std::cout << std::string(dash_num, '-') << std::endl << "The entry has been added.\n\n";
    } 
    else
    {
        std::cerr << "Invalid command received.\n";
        return 1;
    }
}