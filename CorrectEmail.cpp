#include <iostream>

// Задание 2. Проверка корректности email-адреса. Что нужно сделать. Напишите программу, которая проверяет корректность email-адреса, введённого пользователем. Согласно международным требованиям, корректный email-адрес должен состоять из двух частей, разделённых знаком @. Первая часть должна иметь длину не менее одного и не более 64 символов, вторая часть — не менее одного и не более 63 символов. Из символов допускаются только английские буквы, цифры и знак «-» (дефис), а также точка. Точка не может быть первым или последним символом, две точки не могут идти подряд. В первой части (перед символом @), кроме вышеперечисленных, разрешены ещё следующие символы: !#$%&'*+-/=?^_`{|}~
// Пользователь вводит строку, задающую email-адрес. Программа должна вывести слово Yes, если адрес корректен, а в противном случае — слово No.

/*Корректные адреса:
simple@example.com
very.common@example.com
disposable.style.email.with+symbol@example.com
other.email-with-hyphen@example.com
fully-qualified-domain@example.com
user.name+tag+sorting@example.com (может на самом деле быть перенаправлен на user.name@example.com в зависимости от почтового сервиса)
x@example.com (однобуквенная локальная часть)
example-indeed@strange-example.com
admin@mailserver1
example@s.example
mailhost!username@example.org
user%example.com@example.org

Некорректные адреса:
John..Doe@example.com (две точки не могут идти подряд)
Abc.example.com (нет символа @)
A@b@c@example.com (символ @ должен быть только один)
a"b(c)d,e:f;g<h>i[j\k]l@example.com (есть недопустимые символы)
1234567890123456789012345678901234567890123456789012345678901234+x@example.com (первая часть длиннее 64 символов)
i_like_underscore@but_its_not_allow_in _this_part.example.com (во второй части есть недопустимый символ «_»)*/

// Рекомендации. Активно используйте оператор индексации строки str[i], но помните, что индексы начинаются с нуля, а не с единицы. Создайте отдельные функции, которые выдают первую и вторую части адреса для их последующего анализа. Для валидации отдельных символов внутри части используйте дополнительные строки-словари, состоящие из всех корректных символов для соответствующей части. При разработке вспомогательных функций получения первой и второй части адреса воспользуйтесь циклом, который проверяет текущий символ. Если символ равен ‘@’, значит мы нашли границу между частями адреса. В функции нахождения первой части в этом месте надо остановиться и вернуть все символы, что были раньше (их можно накапливать в std::string при помощи оператора +=). Во второй функции все символы после ‘@’ тем же оператором добавляются к результату. Строка-словарь — это строка, которая в нашем случае содержит весь английский алфавит и символы. Каждый символ адреса надо сравнить с каждым символом из этого списка «допустимых символов» в цикле. В этом задании очень важно разбить код на отдельные функции, каждая из которых делает небольшую часть работы. Что оценивается. Корректные результаты валидации адресов электронной почты. Должны устанавливаться как валидные адреса, так и невалидные.

std::string local_part(std::string email)
{
    std::string first_part = "";
    for (int i = 0; i < email.length(); i++)
    {
        if (email[i] == '@') break;
        
        first_part += email[i];
    }
    return first_part;
}

bool local_part_check(std::string first_part)
{
    std::string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-.!#$%&'*+-/=?^_`{|}~";

    if (first_part.length() < 1 || first_part.length() > 64 || first_part[0] == '.')
        return false;
    
    for (int i = 0; i < first_part.length(); i++)
    {
        bool is_allowed = false;

        for (int c = 0; c < allowed_chars.length(); c++)
        {
            if (first_part[i] == allowed_chars[c]) 
            {
                is_allowed = true;
                break;
            }
        }
        if (!is_allowed) return is_allowed;

        if (i > 0 && first_part[i] == '.' && first_part[i-1] == '.')
            return false;
    }

    return true;
}

std::string domain_part(std::string email)
{
    std::string second_part = "";
    bool d_part = false;
    for (int i = 0; i < email.length(); i++)
    {
        if (d_part) second_part += email[i];
        if (email[i] == '@') d_part = true;
    }
    return second_part;
}

bool domain_part_check(std::string second_part)
{
    std::string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-.";

    if (second_part.length() < 1 || second_part.length() > 63 || second_part[-1] == '.')
        return false;
    
    for (int i = 0; i < second_part.length(); i++)
    {
        bool is_allowed = false;

        for (int c = 0; c < allowed_chars.length(); c++)
        {
            if (second_part[i] == allowed_chars[c]) is_allowed = true;
        }
        if (!is_allowed) return is_allowed;
        
        if ((i > 1) && second_part[i] == '.' && second_part[i-1] == '.')
            return false;
    }

    return true;
}

int main() 
{
    std::string email;
    while(true)
    {
        email = "";
        std::cout << "Enter email address: ";
        std::getline(std::cin, email);
        
        if (email == "") 
        {
            std::cout << "See you again!" << std::endl;
            return 0;
        }

        std::cout << ((local_part_check(local_part(email)) && domain_part_check(domain_part(email)))? "Yes" : "No") 
            << std::endl;
    }
}