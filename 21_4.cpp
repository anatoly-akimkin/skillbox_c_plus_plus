// 4. Пошаговая ролевая игра (дополнительная задача). Что нужно сделать. Реализуйте упрощённую версию пошаговой ролевой игры. Действие разворачивается на карте размером 20 на 20 клеток. По клеткам перемещаются игрок и его противники. После каждого хода игрока карта показывается вновь со всеми противниками на ней: игрок помечается буквой P; противники — буквой E; пустые места — точкой.
// Каждый персонаж игры представлен в виде структуры с полями: «Имя»; «Жизни»; «Броня»; «Урон». 
// Сначала создаётся пять противников в случайных клетках карты: Имена противникам задаются в формате Enemy #N, где N — порядковый номер. Уровень жизни противников задаётся случайно — от 50 до 150. Уровень брони варьируется от 0 до 50. Урон тоже выбирается случайно — от 15 до 30. Игрок конструирует своего персонажа самостоятельно. Задаёт все его параметры, включая имя. Все персонажи появляются в случайных местах карты.
// Игрок ходит с помощью команд: L, R, U, D (по первым буквам слов left, right, up, down). В зависимости от команды выбирается направление перемещения: влево, вправо, вверх, вниз. Противники перемещаются в случайном направлении.
// Если игрок перемещается в сторону, где уже кто-то находится, он наносит этому персонажу урон. Противники при этом никогда не бьют друг друга: они просто пропускают ход и остаются на своём месте. За пределы карты (20 на 20 клеток) ходить нельзя никому. Если кто-то выбрал направление за границами, ход пропускается.
// Формула расчёта урона совпадает с той, что была в материале. Жизни уменьшаются на размер урона. При этом броня тоже сокращается на приведённый урон.
// Игра заканчивается, когда умирают либо все противники, либо игрок. В первом случае на экран выводится сообщение о победе, во втором — о поражении. Если в начале хода игрок вводит команду save или load вместо направления перемещения, то игра либо сохраняет своё состояние в файл, либо загружает это состояние из файла.
// Советы и рекомендации. Для определения команды персонажа можно внутри структуры данных о нём завести флаг. Для отображения координат персонажей можно использовать структуру вектора из другой задачи, но заменить типы координат. Для сохранения параметров игры и их загрузки можно работать с текстовыми данными. Однако записать всё в двоичном формате проще, главное — соблюдать последовательность полей:
/* std::ofstream file("save.bin", std::ios::binary);
    for (int i = 0; i < 6; ++i) {

        file.write((char*)&(characters[i].position),
                   sizeof(characters[i].position));
… */
// При загрузке используйте ifstream и ту же последовательность полей. Задание необязательно сдавать на проверку. Но если хотите это сделать, куратор будет учитывать следующее:  Корректно работает сохранение и загрузка в игре. После загрузки все атрибуты игрока, включая имя, восстанавливаются из файла. После загрузки количество противников на поле соответствует количеству противников при сохранении. Все игроки после загрузки появляются в местах, где они находились при сохранении. При ходе игрока не появляются новые противники. Перед загрузкой файла сохранения проверяется, есть ли он в операционной системе.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <ctime>

enum class Сommands
{
    kMoveLeft = 0,
    kMoveRight = 1, 
    kMoveUp = 2,
    kMoveDown = 3,
    kSaveProgress = 4,
    kLoadProgress = 5
};

struct Сoordinates
{
    int x = 0;
    int y = 0;
};

enum class Relationships
{
    kPlayer,
    kEnemy,
    kNeutral
};

struct Character
{
    std::string name = "";
    Relationships relationship = Relationships::kNeutral;
    int health = 0;
    int armor = 0;
    int damage = 0;
    Сoordinates position;
};

int GetInt(int min_val = 0, int max_val = INT_MAX)
{
    int val;
    std::cin >> val;
    while (std::cin.fail() || val < min_val || val > max_val) {
        std::cerr << "Invalid value.\n---> ";
        if (std::cin.fail()) std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> val;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

void AddCharacter(std::vector<Character> &rCharacters, Character &rCharacter)
{
    // define a character's position and add the character to the vector
    bool is_free;
    do {
        is_free = true;
        rCharacter.position.x = std::rand() % 20;
        rCharacter.position.y = std::rand() % 20;
        for (int i = 0; i < rCharacters.size(); ++i) {
            if (rCharacter.position.x == rCharacters[i].position.x 
                && rCharacter.position.y == rCharacters[i].position.y) {
                is_free = false;
            }
        }
    } while (!is_free);
    rCharacters.push_back(rCharacter);
}

void CreateEnemies(std::vector<Character> &rCharacters, int num_enemies)
{
    for (int i = 0; i < num_enemies; ++i) {
        Character enemy;
        enemy.relationship = Relationships::kEnemy;
        enemy.name = "Enemy #" + std::to_string(rCharacters.size());
        enemy.health = std::rand() % 101 + 50;
        enemy.armor = std::rand() % 51;
        enemy.damage = std::rand() % 16 + 15;
        AddCharacter(rCharacters, enemy);
    }
}

void CreatePlayerCharacter(std::vector<Character> &rCharacters)
{
    Character player;
    player.relationship = Relationships::kPlayer;
    std::cout << "Player name: ";
    std::cin >> player.name;
    std::cout << "Player health (from 50 to 150): ";
    player.health = GetInt(50, 150);
    std::cout << "Player armor (from 0 to 50): ";
    player.armor = GetInt(0, 50);
    std::cout << "Player damage (from 15 to 30): ";
    player.damage = GetInt(15, 30);
    AddCharacter(rCharacters, player);
}

bool is_digit(char c)
{
    if (c >= 48 && c <= 57) return true;
    return false;
}

void PrintMap(const std::vector<Character> &kCharacters)
{
    std::vector<std::string> map;
    for (int i = 0; i < 20; ++i) map.push_back(std::string(20, '.'));

    for (int i = 0; i < kCharacters.size(); ++i) {
        if (kCharacters[i].relationship == Relationships::kEnemy) {
            map[kCharacters[i].position.y][kCharacters[i].position.x] = kCharacters[i].name.back(); // Enemy #
        }
        else {
            map[kCharacters[i].position.y][kCharacters[i].position.x] = 'P';
        }
    }

    std::cout << std::endl << "+ " << std::string(39, '-') << " +" << std::endl;
    for (int i = 0; i < 20; ++i) {
        std::cout << "| ";
        for (int k = 0; k < 20; ++k) {
            char section = map[i][k];
            if (is_digit(section)) {
                std::cout << "E" << section;
            }
            else {
                std::cout << section << " ";
            }
        }
        std::cout << "|" << std::endl;
    } 
    std::cout << "+ " << std::string(39, '-') << " +" << std::endl << std::endl;
}

bool SaveToFile(const std::string &kPath, const std::vector<Character> &kCharacters) 
{
    std::ofstream file(kPath, std::ios::binary);
    if (!file.is_open()) return 0;

    int vec_size = kCharacters.size();
    file.write((char*) &vec_size, sizeof(vec_size));
    for (int i = 0; i < vec_size; ++i) {
        int name_len = kCharacters[i].name.length();
        file.write((char*) &name_len, sizeof(name_len));
        file.write(kCharacters[i].name.c_str(), name_len);
        file.write((char*) &kCharacters[i].relationship, sizeof(kCharacters[i].relationship));
        file.write((char*) &kCharacters[i].health, sizeof(&kCharacters[i].health));
        file.write((char*) &kCharacters[i].armor, sizeof(kCharacters[i].armor));
        file.write((char*) &kCharacters[i].damage, sizeof(kCharacters[i].damage));
        file.write((char*) &kCharacters[i].position.x, sizeof(kCharacters[i].position.x));
        file.write((char*) &kCharacters[i].position.y, sizeof(kCharacters[i].position.y));
    }
    return 1;
}

bool LoadFromFile(const std::string &kPath, std::vector<Character> &rCharacters)
{
    std::ifstream file(kPath, std::ios::binary);
    if (!file.is_open()) return 0;

    int vec_size;
    file.read((char*) &vec_size, sizeof(vec_size));
    rCharacters.clear();
    for (int i = 0; i < vec_size; ++i) {
        Character c;
        int name_len;
        file.read((char*) &name_len, sizeof(name_len));
        c.name.resize(name_len);
        file.read((char*) c.name.c_str(), name_len);
        file.read((char*) &c.relationship, sizeof(c.relationship));
        file.read((char*) &c.health, sizeof(&c.health));
        file.read((char*) &c.armor, sizeof(c.armor));
        file.read((char*) &c.damage, sizeof(c.damage));
        file.read((char*) &c.position.x, sizeof(c.position.x));
        file.read((char*) &c.position.y, sizeof(c.position.y));
        rCharacters.push_back(c);
    }
    return 1;
}

Сommands GetCommand(const Character &kCharacter)
{
    if (kCharacter.relationship == Relationships::kEnemy) {
        return Сommands(std::rand()%4);
    }
    std::string command = "";
    do {
        std::cout << "---> ";
        std::cin >> command;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (command == "save") return Сommands::kSaveProgress;
        if (command == "load") return Сommands::kLoadProgress;
        if (command == "l" || command == "L") return Сommands::kMoveLeft;
        if (command == "r" || command == "R") return Сommands::kMoveRight;
        if (command == "u" || command == "U") return Сommands::kMoveUp;
        if (command == "d" || command == "D") return Сommands::kMoveDown;
    } while (true);
}

int CheckPosition(const std::vector<Character> &kCharacters, Сoordinates position)
{
    for (int i = 0; i < kCharacters.size(); ++i) {
        if (kCharacters[i].position.x == position.x && kCharacters[i].position.y == position.y) return i;
    }
    return -1;
}

std::string CommandToStr(Сommands command)
{
    switch (command) {
    case Сommands::kMoveLeft:
        return "left";
    case Сommands::kMoveRight:
        return "right";
    case Сommands::kMoveUp:
        return "up";
    case Сommands::kMoveDown:
        return "down";
    default:
        return "???";
    }
}

bool DealDamage(Character &rDealer, Character &rTaker)
{
    std::cout << rDealer.name << " is attacking!\n" 
              << rTaker.name << " takes " << rDealer.damage << " damage.\n";
    rTaker.armor -= rDealer.damage;
    if (rTaker.armor < 0) {
        rTaker.health += rTaker.armor;
        rTaker.armor = 0;
        if (rTaker.health <= 0) {
            std::cout << rTaker.name << " dies!\n";
            return 1;
        } 
    }
    return 0;
}

int ExecuteСommand(std::vector<Character> &rCharacters, Character &rCharacter, Сommands command)
{
    Сoordinates new_pos;
    new_pos.x = rCharacter.position.x;
    new_pos.y = rCharacter.position.y;

    switch (command) {
    case Сommands::kMoveLeft:
        --new_pos.x;
        break;
    case Сommands::kMoveRight:
        ++new_pos.x;
        break;
    case Сommands::kMoveUp:
        --new_pos.y;
        break;
    case Сommands::kMoveDown:
        ++new_pos.y;
        break;
    }

    if (new_pos.x < 0 || new_pos.x >= 20 || new_pos.y < 0 || new_pos.y >= 20) {
        std::cout << rCharacter.name << ": skips a turn\n";
    }
    else {
        int i = CheckPosition(rCharacters, new_pos);
        if (i < 0) {
            rCharacter.position.x = new_pos.x;
            rCharacter.position.y = new_pos.y;
            std::cout << rCharacter.name << ": moves " << CommandToStr(command) << std::endl;
        }
        else {
            if (rCharacter.relationship == Relationships::kPlayer 
                || rCharacters[i].relationship == Relationships::kPlayer) {
                if (DealDamage(rCharacter, rCharacters[i])) return i;
            }
            else {
                std::cout << rCharacter.name << ": skips a turn\n";
            }
        }
    }
    return -1;
}

void PrintStatuses(const std::vector<Character> &kCharacters)
{
    for (int i = 0; i < kCharacters.size(); ++i) {
        std::cout << kCharacters[i].name << " (health: " << kCharacters[i].health 
                  << ", armor: " << kCharacters[i].armor << ", damage: " << kCharacters[i].damage << ")\n";
    }
}

int main()
{
    const std::string kPath = "save.bin";
    std::srand(std::time(nullptr));
    std::vector<Character> characters;

    CreatePlayerCharacter(characters);
    CreateEnemies(characters, 5);
    std::cout << "To move use the Сommands L, R, U, D.\n";

    while(characters.size() > 1 && characters[0].relationship == Relationships::kPlayer) {
        PrintMap(characters);
        PrintStatuses(characters);

        for (int i = 0; i < characters.size(); ++i) {
            Сommands command;
            if (characters[i].relationship == Relationships::kEnemy) {
                command = GetCommand(characters[i]);
            }
            else {
                bool is_action = false;
                do {
                    command = GetCommand(characters[i]);
                    if (command == Сommands::kSaveProgress) {
                        if (SaveToFile(kPath, characters)) {
                            std::cout << "The game has been saved.\n";
                        }
                        else {
                            std::cerr << "Saving failed.\n";
                        }
                    }
                    else if (command == Сommands::kLoadProgress) {
                        if (LoadFromFile(kPath, characters)) {
                            PrintMap(characters);
                            PrintStatuses(characters);
                            std::cout << "The game has been loaded.\n";
                        }
                        else {
                            std::cerr << "Loading failed.\n";
                        }
                    }
                    else {
                        is_action = true;
                    }
                } while (!is_action);
            }

            int corpse = ExecuteСommand(characters, characters[i], command);
            if (corpse >= 0) {
                if (corpse <= i) --i;
                characters.erase(characters.cbegin() + corpse);
            }
        }
    }

    PrintMap(characters);
    PrintStatuses(characters);
    std::cout << ((characters[0].relationship == Relationships::kPlayer)?
                  ">>> VICTORY! <<<\n" : ">>> YOU DIED <<<") << std::endl;
}