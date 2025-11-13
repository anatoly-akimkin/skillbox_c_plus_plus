// Задание 5. Реализация игры «Что? Где? Когда?» Что нужно сделать. Реализуйте простую версию интеллектуальной игры «Что? Где? Когда?». 
// Как происходит игра. В начале каждого хода игроки вращают волчок, то есть выбирают сектор на столе, который сейчас играет. Всего таких секторов 13. Сектор выбирается так: с клавиатуры вводится офсет (смещение) относительно текущего сектора на барабане. Исходя из этого офсета вычисляется новый активный сектор, который и будет играть в этом ходе. Если выпавший сектор уже играл, выбирает следующий неигравший за ним. В начале всей игры стрелка установлена на первом секторе. Как только играет какой-то из секторов, с него берётся письмо с вопросом — то есть считывается из файла данного сектора. Вопрос показывается на экране. После того как вопрос показан, от игрока ожидается ответ на него. Игрок вводит этот ответ с помощью стандартного ввода. То, что он ввёл, сравнивается с ответом, который хранится во втором файле, ассоциированном с активным сектором. Данный файл должен содержать лишь одно слово-ответ. Если ответ знатока-игрока был правильным, ему начисляется один балл. Если неверен, то балл уходит телезрителям. Игра продолжается до тех пор, пока или игрок, или зрители не наберут шесть баллов. После этого называется победитель и программа заканчивает работу.
// Что оценивается. Игра должна корректно работать от первого хода до последнего. В результате обязательно должен выявляться победитель.

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

bool str_to_int(std::string &str, int &val)
{
    try 
    {
        val = stoi(str);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << ": integer input expected.\n--> ";
        return 0;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << e.what() << ": value out of range.\n--> ";
        return 0;
    }
    return 1;
}

bool get_from_file(std::ifstream &file, const std::string &path, std::string &buffer)
{
    file.open(path);
    bool open = file.is_open();
    if (!open) std::cerr << "Failed to open a file.\n";
    std::getline(file, buffer);
    file.close();
    return open;
}

int main()
{
    std::cout << "\t>> WHAT? WHERE? WHEN? <<\n\n\t    WELCOME, PLAYER!\n\n";
    std::ifstream file;
    std::string path = "C:\\code\\module19\\";
    int p_points = 0; // Player's points
    int a_points = 0; // Audience points

    int pos = 0, offset;
    short int sectors = 0; // Flags
    std::string buffer, answer;

    while (p_points < 6 && a_points < 6)
    {
        std::cout << "The player spins the top.\nThe top's arrow has moved by --> ";
        do
        {
            std::cin >> answer;
        } while (!str_to_int(answer, offset));

        pos = (pos + offset) % 13;
        if (pos < 0) pos += 13; 
        while(sectors & (1 << pos)) pos = (++pos) % 13;
        sectors |= (1 << pos);
        std::cout << "\nSector " << pos+1 << " is playing.\nQuestion:\n";

        if ( !get_from_file(file, (path + "q\\q" + std::to_string(pos) + ".txt"), buffer) ) return 1;
        std::string str = std::string(buffer.size(), '-');
        std::cout << str << std::endl << buffer << std::endl << str << std::endl;

        std::cout << "\nAnswer --> ";
        std::string answer;
        std::getline((std::cin >> std::ws), answer);

        if ( !get_from_file(file, (path + "a\\a" + std::to_string(pos) + ".txt"), buffer) ) return 1;
        
        (answer == buffer)? ++p_points : ++a_points;
        
        str = std::string(30, '-');
        std::cout << str << std::endl << "Player: " << p_points << "\tAudience: " 
                  << a_points << std::endl << str << std::endl;
    }

    if (p_points == 6)
    {
        std::cout << std::endl << std::string(33, '#') << "\nThe player wins. Congratulations!\n"
                  << std::string(33, '#') << std::endl;
    }
    else
    {
        std::cout << std::endl << std::string(70, '#') 
                  << "\nIn today's game, the victory goes to the viewers. Good luck next time!\n"
                  << std::string(70, '#') << std::endl;
    }
}