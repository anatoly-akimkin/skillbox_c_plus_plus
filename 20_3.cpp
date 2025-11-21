// Задание 3. Симуляция игры «Рыбалка». Что нужно сделать. Реализуйте простую симуляцию игры в рыбалку. В исходном текстовом файле реки (river.txt) задайте список из разных видов рыб, которые можно в ней поймать. Рыбок может быть сколько угодно, а виды могут повторяться. Как должна работать симуляция: 
// В начале программы пользователь указывает, какую именно рыбу он собирается ловить (её вид). После этого из первого файла друг за другом осуществляется чтение его содержимого, вид за видом. Если на отдельных шагах вид совпал с указанным пользователем, в выходной файл basket.txt (корзинка) записывается этот вид. В конце программы показывается, сколько было поймано рыб за текущую ловлю.  Программу можно запускать несколько раз, при этом уже пойманные рыбы должны сохраняться в файле-корзинке.
// Рекомендация. Пример содержания исходного файла:
/* sunfish
shad
carp
bass
bullhead
carp
walleye
catfish
carp */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>

void print_ss(std::stringstream &ss)
{
    std::vector<std::string> words;
    std::vector<int> w_num;

    std::string word;
    while (ss >> word)
    {
        bool new_w = true;
        for (int i = 0; i < words.size(); ++i)
        {
            if (words[i] == word) 
            {
                ++w_num[i];
                new_w = false;
            }
        }
        if(new_w) 
        {
            words.push_back(word);
            w_num.push_back(1);
        }

    }

    for (int i = 0; i < words.size(); ++i)
    {
        std::cout << words[i] << ": " << w_num[i] << std::endl;
    }
}

int fishing(std::ifstream &river, const std::string &fish)
{
    int f_counter = 0;
    std::string ifish;
    while (!river.eof())
    {
        std::getline(river, ifish);
        if (fish == ifish) ++f_counter;
    }
    return (f_counter > 0)? (std::rand() % f_counter + 1) : 0;
}

void print_res(const std::string &fish, const int &f_num)
{
    int time = std::rand() % 26 + 5;
    if (time < 10) 
    {
        std::cout << "You're in luck! You caught a " << fish << " (" << f_num << ") in just " << time << " minutes." << std::endl;
    }
    else if (time < 20)
    {
        std::cout << "After " << time << " minutes, you've caught a " << fish << " (" << f_num << ")" << std::endl;
    }
    else 
    {
        std::cout << "Catching " << fish << " (" << f_num << ") took a full " << time << " minutes" << std::endl;
    }
}

int main()
{
    std::srand(std::time(nullptr));
    std::stringstream basket;
    
    std::string r_path = "river.txt";
    // std::cout << "River path:\n--> "; // C:\\code\\module20\\river.txt
    // std::cin >> r_path;

    std::string b_path = "basket.txt";
    // std::cout << "Basket path:\n--> "; // C:\\code\\module20\\basket.txt
    // std::cin >> b_path;

    while (true)
    {
        std::cout << std::string(50, '-') << std::endl << "What kind of fish are you trying to catch? (leave blank to exit)\n--> ";
        std::string fish;
        std::getline(std::cin, fish);
        if (fish == "") break;
        
        std::ifstream river_file(r_path);
        if (!river_file.is_open())
        {
            std::cerr << "Failed to open a file.\n";
            return 1;
        }

        int f_found = fishing(river_file, fish);
        river_file.close();

        if (!f_found)
        {
            std::cout << "More than an hour passed, but nothing was caught.\n";
        }
        else
        {
            std::ofstream basket_file(b_path, std::ios::app);
            if (!basket_file.is_open())
            {
                std::cerr << "Failed to open a file.\n";
                return 1;
            }
            for (int i = 0; i < f_found; ++i) 
            {
                basket_file << fish << std::endl;
                basket << fish << " ";
            }
            basket_file.close();
            print_res(fish, f_found);
        }
    }
    
    std::cout << "Today's catch:\n";
    print_ss(basket);
}