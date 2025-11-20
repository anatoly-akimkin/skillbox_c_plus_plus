// Задание 1. Разработка программы поиска слов в файле. Что нужно сделать. Составьте небольшой текстовый файл «words.txt», в котором последовательно, через пробелы и переносы строк расположены различные слова. Можете использовать любые англоязычные слова. Разработайте программу, которая искала бы среди этих слов нужное пользователю и выводила бы общее количество повторений этого слова. 0 — если слово вообще не присутствует в файле.
// Что оценивается. Корректность работы программы на созданных вами вводных данных. Число найденных слов должно соответствовать.

#include <iostream>
#include <fstream>

int word_count(std::ifstream &text, const std::string &word)
{
    int counter = 0;
    std::string current_word;
    while (text >> current_word) if (word == current_word) ++counter;
    return counter;
}

int main()
{
    std::string path;
    std::cout << "Enter the path to the file.\n--> "; // C:\code\module19\words.txt
    std::getline(std::cin, path);

    std::ifstream text;
    text.open(path);
    if (!text.is_open())
    {
        std::cerr << "Failed to open a file.\n";
        return 1;
    }

    std::string word;
    std::cout << "Enter the word.\n---> ";
    std::cin >> word;

    std::cout << "The word appears " << word_count(text, word) << " times in the text.";

    text.close();
}