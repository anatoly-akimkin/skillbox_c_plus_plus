// Задание 2. Разработка просмотрщика текстовых файлов. Что нужно сделать. Разработайте простейший просмотрщик текстовых файлов. В начале программы пользователь вводит путь к текстовому файлу, который требуется открыть и просмотреть. Внутренности файла необходимо вывести в стандартный вывод. Программа должна работать для любых текстовых файлов в формате TXT, но вы можете создать и свой отдельный файл для теста. Главное, чтобы файл был англоязычным, дабы избежать проблем с кодировками.
// Советы и рекомендации. Для проверки того, был ли на самом деле открыт файл, используйте метод is_open. Он вернёт true, если файл был благополучно открыт, и false, если что-то пошло не так, к примеру, если путь к файлу невалидный. Файл надо считывать постепенно, отдельными фрагментами, ведь он может быть весьма большим. Для этого лучше всего пользоваться методом gcount, так как он ещё вернёт количество байт, которые были считаны по факту методом read. Сами эти фрагменты могут храниться в специальном буфере, как и в примере из лекций, но его размер и второй аргумент к функции read надо рассчитать так, чтобы выводились все символы, без обрезки последней буквы. Файл можно открыть в бинарном формате.
// Что оценивается. Показ файла на экране должен соответствовать тому, что мы наблюдаем в стандартном блокноте.

#include <fstream>
#include <iostream>

bool open_txt_file(std::ifstream &file_stream, const std::string &path)
{
    file_stream.open(path, std::ios::binary);
    if (!file_stream.is_open()) 
    {
        std::cerr << "File not found.\nCheck the path.\n";
        return false;
    }

    std::string f_extension = path.substr(path.size()-4, 4);
    if (f_extension != ".txt") 
    {
        std::cout << "Unsupported file extension.\n";
        return false;
    }

    return true;
}

void print_txt_file(std::ifstream &txt_file)
{
    char buffer[51];
    buffer[50] = 0;
    while (!txt_file.eof())
    {
        txt_file.read(buffer, 50);
        if (txt_file.gcount() < 50)
        {
            for (int i = 0; i < txt_file.gcount(); ++i)
            {
                std::cout << buffer[i];
            }
        }
        else
        {
            std::cout << buffer;
        }
    }
}

int main()
{
    std::ifstream text_file;

    std::string path;
    std::cout << "Enter the path to the file.\n--> ";
    
    std::getline(std::cin, path);
    if (!open_txt_file(text_file, path)) return 1;
    
    print_txt_file(text_file);
    
    text_file.close();
}