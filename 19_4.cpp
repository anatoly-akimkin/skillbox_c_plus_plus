// Задание 4. Разработка детектора PNG-файла. Что нужно сделать. Разработайте программу, которая получает на вход, в стандартный ввод, путь к файлу. На выходе программа должна определить, является ли данный файл PNG-изображением. Данная процедура не просто должна смотреть на расширение файла, но и произвести минимальный анализ его внутренностей, в бинарном режиме. Внутренности валидного бинарного файла начинаются со специального 8-байтового заголовка. Нас будут интересовать первые четыре байта. Первый байт всегда имеет значение −119 (число со знаком минус), а следующие — это просто символы ‘P’, ‘N’, ‘G’, расположенные друг за другом. Обратите внимание, что все они в верхнем регистре. По результатам проверки пути и внутренностей требуется сообщить пользователю о результате проверки в стандартный вывод.
// Советы и рекомендации. Чтобы определить расширение файла, используйте функцию substr, которая получает офсет и длину подстроки и возвращает её.
// Что оценивается. Для произвольных путей файлов, введённых пользователем, требуется выдавать корректный результат — являются ли они PNG-файлами или нет.

#include <iostream>
#include <fstream>

bool open_file(std::ifstream &file_stream, const std::string &path)
{
    file_stream.open(path, std::ios::binary);
    bool open = file_stream.is_open();
    if (!open) std::cerr << "File not found.\nCheck the path.\n";
    return open;
}

int main() 
{
    std::ifstream png_file;
    std::string path;

    std::cout << "Enter the path to the file.\n--> ";
    std::getline(std::cin, path);
    // std::cout << path << std::endl;
    if (!open_file(png_file, path)) return 1;
    
    
    std::string f_extension = path.substr(path.size()-4, 4);
    bool png = f_extension == ".png";
    if (png)
    {
        char valid_file_header[] { -119, 'P', 'N', 'G' };
        char file_header[4];
        png_file.read(file_header, 4);

        for (int i = 0; i < 4; ++i) 
        {
            if (file_header[i] != valid_file_header[i]) 
            {
                png = 0;
                break;
            }
        }
    }

    png_file.close();

    std::cout << "This is " << (png? "" : "not ") << "a PNG file" << std::endl;
    
}