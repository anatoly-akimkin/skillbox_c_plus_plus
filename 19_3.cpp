// Задание 3. Реализация программы чтения ведомости. Что нужно сделать. Реализуйте программу чтения информации из ведомости по учёту выплат. Сама ведомость представляет собой следующую таблицу: 
/* имя и фамилия человека; 
количество денег, которые были выплачены лицу; 
дата выплаты в формате ДД.ММ.ГГГГ. */
// На основе данных из ведомости следует подсчитать общее количество выплаченных средств и определить человека с максимальной суммой выплат. Пример данных ведомости
/* Tom Hanks 35500 10.11.2020
Rebecca Williams 85000 1.1.2021
Sally Field 15600 15.8.2021
Michael Humphreys 29400 23.5.2020
Harold Herthum 74300 9.6.2019
George Kelly 45000 12.3.2018
Bob Penny 12500 13.5.2020
John Randall 23400 2.10.2020
Sam Anderson 6500 15.7.2020
Margo Moorer 12350 24.2.2019 */
// Что оценивается. Корректное отображение общей суммы выплат и самого крупного получателя денежных средств.

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

int main()
{
    std::ifstream statement;
    std::string path = "C:\\code\\module19\\payment accounting statement.txt";

    statement.open(path);
    if (!statement.is_open())
    {
        std::cerr << "Failed to open a file.";
        return 1;
    }

    std::string f_name, l_name, line;
    int max_sum = 0, total_sum = 0;
    for (int sum; !statement.eof();)
    {
        std::getline(statement, line);
        std::stringstream ss(line);
        //std::cout << ss.str() << std::endl;
        
        for (int i = 0; i < 2; ++i) ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        ss >> sum;
        total_sum += sum;

        if (max_sum < sum)
        {
            ss.seekg(0);
            ss >> f_name >> l_name >> max_sum;
        }
    }

    statement.close();

    std::cout << "The total amount of payments: " << total_sum << std::endl 
              << "The largest recipient of funds: " << f_name << " " << l_name 
              << " (" << max_sum << ")" << std::endl;
}