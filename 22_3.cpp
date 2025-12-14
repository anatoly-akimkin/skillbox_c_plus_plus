// Задание 3. Анаграммы. Что нужно сделать. Напишите функцию, которая принимает две строки и возвращает true, если первая строка является анаграммой второй (то есть можно получить первую строку из второй путём перестановки букв местами), и false иначе. Для достижения хорошей асимптотики решения рекомендуется использовать std::map. Пример анаграммы: лекарство — стекловар
// Чек-лист для проверки задачи. Функция принимает корректные типы данных, тип возвращаемого значения — bool. Функция не использует библиотек, кроме <iostream>, <map>, <string>. Функция корректно определяет, являются ли строки анаграммами.

#include <iostream>
#include <map>
#include <string>

void StringToMap(const std::string &kStr, std::map<char, int> &rMap)
{
    for (int i = 0; i < kStr.length(); ++i) {
        std::map<char, int>::iterator it = rMap.find(kStr[i]);
        if (it == rMap.end()) {
            rMap[kStr[i]] = 1;
        }
        else {
            ++(it->second);
        }
    }
}

bool AreAnagrams(const std::string &kWord1, const std::string &kWord2)
{
    std::map<char, int> map1, map2;
    StringToMap(kWord1, map1);
    StringToMap(kWord2, map2);
    std::map<char, int>::iterator it1 = map1.begin(), it2 = map2.begin();
    while (it1 != map1.end() && it2 != map2.end()) {
        if (it1->first != it2->first || 
            it1->second != it2->second) {
            return false;
        }
        ++it1;
        ++it2;
    }
    if (it1 == map1.end() && it2 == map2.end()) return true;
    return false;
}

int main()
{
    std::string word1, word2;
    std::cout << "Word 1: ";
    std::cin >> word1;
    std::cout << "Word 2: ";
    std::cin >> word2;
    std::cout << std::boolalpha << AreAnagrams(word1, word2) << std::endl;
}