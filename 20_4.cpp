// Задание 4. Симуляция работы банкомата. Что нужно сделать. Реализуйте упрощённую симуляцию работы банкомата. 
// Учтите следующее: В банкомате могут храниться только бумажные купюры номиналом 100, 200, 500, 1 000, 2 000 и 5 000 рублей. Максимально в банкомате может храниться только 1 000 купюр. Все они записываются в отдельный файл. У банкомата, как у устройства, две основных операции — снятие денег пользователем и наполнение деньгами инкассаторами банка. Состояние банкомата должно храниться в отдельном бинарном файле, автономно. Хранение в бинарном виде улучшает производительность программы и уменьшает размер данных.
// Банкомат работает следующим образом: При старте программа проверяет наличие файла .bin. Если он есть (данные по банкомату были сохранены), данные загружаются и на экран выводится информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма. Если файла нет — банкомат «пустой». При вводе «+» заполняются недостающие купюры и выводится информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма. Количество купюр рассчитывается так, чтобы банкомат был заполнен полностью. Все купюры при этом выбираются случайным образом. При вводе «−» симулируется снятие пользователем денег. Пользователь указывает сумму с точностью до 100 рублей. Считайте, что каждый клиент обладает неограниченным балансом в системе и теоретически может снять любую сумму. Выдача происходит начиная с купюр большего номинала. Если запрошенная сумма не может быть снята из-за отсутствия подходящих купюр в машине, показывается сообщение, что эта операция невозможна. После выдачи денег на экран выдаётся информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма. При выходе из программы сохраняем состояние банкомата в файл. 
// Рекомендации. Вы можете хранить массив купюр целиком, помечая отсутствующие позиции нулями. Выход из программы рекомендуется сделать по отдельной команде, а команды «+» и «−» получать в цикле.
// Что оценивается. Соблюдены все условия заданий. Программы работают корректно.

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>

bool valid_int(const std::string &n)
{
    for (int i = 0; i < n.length(); ++i)
    {
        if (n[i] < 48 || n[i] > 57) 
        {
            std::cerr << "Invalid argument\n--> ";
            return false;
        }
    }
    return true;
}

void add_note(const int &val, int &total_sum, const int *notes, const int &n_size, int *n_counter)
{
    if (val) 
    {
        total_sum += val;

        for (int i = 0; i < n_size; ++i)
        {
            if (val == notes[i])
            {
                ++n_counter[i];
                break;
            }
        }
    }
}

void read_from_file(const std::string &path, int *storage, const int &s_size, 
                    int &total_sum, const int *notes, const int &n_size, int *n_counter)
{
    std::ifstream in_file(path, std::ios::binary);
    if (in_file.is_open())
    {
        in_file.read((char*) storage, sizeof(int)*s_size);
        for (int i = 0; i < s_size; ++i) 
        {
            add_note(storage[i], total_sum, notes, n_size, n_counter);
        }
        in_file.close();
    }
    else
    {
        for (int i = 0; i < s_size; ++i) storage[i] = 0;
    }
}

bool write_to_file(const std::string &path, 
                   int *storage, const int &s_size)
{
    std::ofstream out_file(path, std::ios::binary);
    if (out_file.is_open())
    {
        out_file.write((char*) storage, sizeof(int)*s_size);
        out_file.close();
        return 1;
    }
    return 0;
}

void print_state(const int &total_sum, const int *notes, 
                 const int &n_size, const int *n_counter, const int &str_len)
{
    std::cout << std::endl << std::string(str_len, '~') << std::endl << "ATM state:\n";
    for (int i = 0; i < n_size; ++i) 
    {
        std::cout << notes[i] << " RUB: " << n_counter[i] << " notes\n";
    }
    std::cout << "Total amount: " << total_sum << std::endl 
              << std::string(str_len, '~') << std::endl << std::endl;
}

void refill(int *storage, const int &s_size, int &total_sum, 
            const int *notes, const int &n_size, int *n_counter)
{
    for (int i = 0; i < s_size; ++i)
    {
        if (storage[i] == 0)
        {
            int j = std::rand() % n_size;
            storage[i] = notes[j];
            total_sum += storage[i];
            ++n_counter[j];
        }
    }
}

bool notes_to_issue(int sum, const int *notes, const int &n_size, 
                    int *n_counter, std::vector<int> &w_counter)
{
    for (int i = 0; i < n_size;)
    {
        if ((n_counter[i] - w_counter[i] > 0) 
            && sum / notes[i] > 0)
        {
            ++w_counter[i];
            sum -= notes[i];
            if (sum == 0) break;
        }
        else
        {
            ++i;
        }
    }
    if (sum > 0) return false;
    return true;
}

void withdraw(int *storage, const int &s_size, int &total_sum, const int *notes, 
              const int &n_size, int *n_counter, std::vector<int> &w_counter)
{
    for (int i = 0, j = 0; j < n_size;)
    {
        if (w_counter[j] > 0 )
        {
            if (storage[i] == notes[j])
            {
                total_sum -= storage[i];
                storage[i] = 0;
                ++i;
                --n_counter[j];
                --w_counter[j];
            }
            else
            {
                ++i;
            }
        }
        else
        {
            ++j;
            i = 0;
        }
    }
}

int main()
{
    std::srand(std::time(nullptr));
    int notes[] { 5000, 2000, 1000, 500, 200, 100 };
    int n_size = sizeof(notes)/sizeof(int);
    int n_counter[6] = {0}; // Notes counter
    int total_sum = 0;
    int storage[1000];
    int s_size = sizeof(storage)/sizeof(int);

    std::string path = "storage.bin"; // C:\\code\\module20\\storage.bin
    read_from_file(path, storage, s_size, total_sum, notes, n_size, n_counter);

    int str_len = 45;
    while(true)
    {
        if (!total_sum)
        {
            std::cout << std::endl << std::string(str_len, '#') << std::endl 
                      << "Attention: The ATM is empty.\n" << std::string(str_len, '#') << std::endl;
        }
        else
        {
            print_state(total_sum, notes, n_size, n_counter, str_len);
            std::cout << std::string(str_len, '-') << std::endl << "To withdraw cash: -\n";
        }
        std::cout << "To refill the ATM: +\nTo turn off the ATM: q\n" 
                  << std::string(str_len, '-') << std::endl << "--> ";
        std::string input;

        bool bad_input;
        do
        {
            std::getline(std::cin, input);
            bad_input = input != "+" && input != "-" && input != "q";
            if (bad_input) std::cerr << "Invalid command\n--> ";
        } while (bad_input);
        if (input == "q") break;

        if (input == "+")
        {
            int unfilled = s_size;
            for (int i = 0; i < n_size; ++i)
            {
                unfilled -= n_counter[i];
            }
            if (unfilled)
            {
                std::cout << std::string(str_len, '-') << std::endl << "ATM filling... ";
                refill(storage, s_size, total_sum, notes, n_size, n_counter);
                std::cout << "complete!\n";
            }
            else
            {
                std::cerr << std::string(str_len, '-') << std::endl << "Error: ATM is full.\n";
            }
        }
        else if (input == "-" && total_sum)
        {
            std::cout << "The required amount (accurate to 100 RUB):\n--> ";
            int sum;
            do
            {
                std::getline(std::cin, input);
                bad_input = !valid_int(input);
                if (!bad_input && input != "")
                {
                    sum = std::stoi(input);
                    bad_input = (sum == 0 || sum % 100);
                    if (bad_input) std::cerr << "Invalid value\n--> ";
                }
            } while (bad_input);
            if (input == "") continue;

            std::vector<int> w_counter(n_size, 0); // Notes for withdrawal
            if (notes_to_issue(sum, notes, n_size, n_counter, w_counter))
            {
                std::cout << std::string(str_len, '-') << std::endl << "Withdrawal of " << sum << " RUB:\n";
                for (int i = 0; i < n_size; ++i) if (w_counter[i] > 0) 
                    std::cout << notes[i] << "x" << w_counter[i] << " ";
                std::cout << std::endl;
                withdraw(storage, s_size, total_sum, notes, n_size, n_counter, w_counter);
            }
            else
            {
                std::cerr << std::string(str_len, '-') << std::endl 
                          << "Unable to fulfill request.\nInsufficient funds in ATM\n";
            }
        }
        else
        {
            std::cout << "ERROR\n";
        }
    }

    if (write_to_file(path, storage, s_size))
    {
        std::cout << "Data saved.\n";
    }
    else
    {
        std::cerr << "Error: Failed to write data to file\n";
    }
}