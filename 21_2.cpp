// 2. Модель данных для посёлка. Что нужно сделать. Используя структуры данных, создайте подробную модель посёлка.
// Что известно: Посёлок состоит из участков, у каждого участка свой номер.
// На любом участке может стоять жилой дом, а также другие сооружения: гараж, сарай (бытовка), баня. 
// Дана информация о площади, которую каждое здание занимает на участке.
// В доме может быть 1–3 этажа, на этаже — 2–4 комнаты: спальня, кухня, ванная, детская, гостиная.
// Дана информация о количестве комнат и высоте потолка на каждом этаже. Дана информация о площади, которую занимает каждая комната. В доме и бане может быть печь с трубой. Для всех упомянутых сущностей нужно объявить структуры данных.
// Обязательно для выполнения задания. Опишите структуры данных для создания модели посёлка. Структуры должны быть: связными и легко расширяемыми, без дублирующих конструкций. Реализуйте заполнение структур данных. 
// Пользователь заполняет данные о посёлке: вводит общее количество участков, а потом детализирует каждый. Сначала указывается количество построек на участке, а затем — информация, какие это постройки, сколько этажей в доме, какие комнаты на этажах. После ввода данных можно рассчитать суммарный параметр, например процент земли, занимаемой постройками, от общей площади посёлка. Главное в этой задаче не операция подсчёта, а структуры данных.
// Советы и рекомендации Используйте знания о типах данных в C++. Можете применять перечисления и векторы, создавать структуры внутри структур и так далее. Перечислите комнаты и типы зданий следующим образом:
/* enum room_type
{
    living,
    children,
    … */
// Затем используйте полученный тип внутри структуры. Алгоритм заполнения каждого объекта одинаковый: создать объект нужного типа, ввести с клавиатуры значения, добавить объект в вектор при помощи push_back.

#include <iostream>
#include <vector>
#include <string>
#include <limits>

enum RoomType
{
    kOtherRoom,
    kLiving,
    kChildren,
    kBedroom, 
    kKitchen, 
    kBathroom
};

enum BuildingType
{
    kOtherBuilding,
    kResidential, 
    kGarage, 
    kShed, 
    kBathhouse
};

struct Room 
{
    const int kNumRoomTypes = 6;
    RoomType type = RoomType::kOtherRoom;
    int area = 1;
};

struct Floor 
{
    double height = 1;
    const int kMinNumRooms = 2;
    const int kMaxNumRooms = 4;
    std::vector<Room> rooms;
};

struct Building 
{
    int area = 1;
    const int kMinNumFloors = 1;
    const int kMaxNumFloors = 3;
    std::vector<Floor> floors;
    const int kNumBuildingTypes = 5;
    BuildingType type = BuildingType::kOtherBuilding;
    bool has_stove = false;
};

struct Plot 
{
    int id = 0;
    std::vector<Building> buildings;
};

struct Village 
{
    int area = 1;
    std::vector<Plot> plots;
};

int GetInt(int min_val = 0, int max_val = INT_MAX)
{
    int val;
    std::cin >> val;
    while (std::cin.fail() || val < min_val || val > max_val)
    {
        std::cerr << "Invalid value.\n---> ";
        if (std::cin.fail()) std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> val;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

double GetDouble(double min_val = 0)
{
    double val;
    std::cin >> val;
    while (std::cin.fail() || val < min_val)
    {
        std::cerr << "Invalid value.\n---> ";
        if (std::cin.fail()) std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> val;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

int GetStrLen()
{
    return 50;
}

void CreateRooms(Floor &rFloor, int num_rooms)
{
    if (num_rooms + rFloor.rooms.size() > rFloor.kMaxNumRooms) 
    {
        std::cerr << "## Maximum number of rooms: " << rFloor.kMaxNumRooms << " ##" << std::endl;
        num_rooms = rFloor.kMaxNumRooms - rFloor.rooms.size();
    }
    for (int i = 0; i < num_rooms; ++i) 
    {
        std::cout << std::string(GetStrLen(), '~') << std::endl;
        std::cout << ">> Room #" << i << " <<" << std::endl;
        Room room_i;

        // Room type
        std::cout << "Room type (other=0, kLiving=1, kChildren=2, kBedroom=3, kKitchen=4, kBathroom=5)\n---> ";
        room_i.type = RoomType(GetInt(0, room_i.kNumRoomTypes-1));

        // Room area
        printf("Room area (from %d): ", room_i.area);
        room_i.area = GetInt(room_i.area);

        rFloor.rooms.push_back(room_i);
    }
}

void CreateFloors(Building &rBuilding, int num_floors = 0)
{
    if (num_floors + rBuilding.floors.size() > rBuilding.kMaxNumFloors) 
    {
        std::cerr << "## Maximum number of floors: " << rBuilding.kMaxNumFloors << " ##" << std::endl;
        num_floors = rBuilding.kMaxNumFloors - rBuilding.floors.size();
    }
    for (int i = 0; i < num_floors; ++i) 
    {
        std::cout << std::string(GetStrLen(), '~') << std::endl;
        bool is_residential = rBuilding.type == BuildingType::kResidential;
        if (is_residential) std::cout << ">> Floor #" << i << " <<" << std::endl;
        Floor floor_i;

        // Floor height
        std::cout << (is_residential? "Floor" : "Building");
        printf(" height (from %.1f): ", floor_i.height);
        floor_i.height = GetDouble(floor_i.height);
        
        // Number of rooms
        if (is_residential)
        {
            std::cout << "Number of rooms on this Floor (from " << floor_i.kMinNumRooms << " to " << floor_i.kMaxNumRooms << "): ";
            CreateRooms(floor_i, GetInt(floor_i.kMinNumRooms, floor_i.kMaxNumRooms));
        }
        
        rBuilding.floors.push_back(floor_i);
    }
}

int GetMinBuildingArea(Building &rBuilding)
{
    int min_area = 0;
    for (int i = 0; i < rBuilding.floors.size(); ++i)
    {
        int floor_area = 0;
        for (int k = 0; k < rBuilding.floors[i].rooms.size(); ++k)
        {
            floor_area += rBuilding.floors[i].rooms[k].area;
        }
        if (min_area < floor_area) min_area = floor_area;
    }
    if (min_area == 0)
    {
        std::cerr << "Failed to calculate minimum value\n";
        min_area = rBuilding.area;
    }
    return min_area;
}

void CreateBuildings(Plot &rPlot, int num_buildings)
{
    
    for (int i = 0; i < num_buildings; ++i)
    {
        std::cout << std::string(GetStrLen(), '~') << std::endl;
        std::cout << ">> Building #" << i << " <<" << std::endl;
        Building building_i;

        // Building type
        std::cout << "Building type (other=0, residential=1, garage=2, shed=3, bathhouse=4)\n---> ";
        building_i.type = BuildingType(GetInt(0, building_i.kNumBuildingTypes-1));
        bool is_residential = building_i.type == BuildingType::kResidential;

        // Stove
        if (is_residential || building_i.type == BuildingType::kBathhouse)
        {
            std::cout << "Is there a stove in the building? (no=0, yes=1)\n---> ";
            building_i.has_stove = GetInt(0, 1);
        }

        // Number of floors
        int num_floors = building_i.kMinNumFloors;
        if (is_residential)
        {
            std::cout << "Number of floors in the Building (from " << building_i.kMinNumFloors << " to " << building_i.kMaxNumFloors << "): ";
            num_floors = GetInt(building_i.kMinNumFloors, building_i.kMaxNumFloors);
        }
        CreateFloors(building_i, num_floors);

        std::cout << std::string(GetStrLen(), '~') << std::endl;
        // Building area
        int min_area = is_residential? GetMinBuildingArea(building_i) : building_i.area;
        std::cout << "Building area (from " << min_area << "): ";
        building_i.area = GetInt(min_area);

        rPlot.buildings.push_back(building_i);
    }
}

void CreatePlots(Village &rVillage, int num_plots)
{
    for (int i = 0; i < num_plots; ++i)
    {
        std::cout << std::string(GetStrLen(), '~') << std::endl;
        std::cout << ">> Plot #" << i << " <<" << std::endl;
        Plot plot_i;
        int val;

        // The Plot number
        std::cout << "The Plot number (0 --> default value (i)): ";
        val = GetInt();
        plot_i.id = (val == 0)? i : val;

        // Number of buildings
        std::cout << "Number of buildings on the plot: ";
        val = GetInt();
        CreateBuildings(plot_i, val);

        rVillage.plots.push_back(plot_i);
    }
}

int GetMinVillageArea(Village &rVillage)
{
    int min_area = 0;
    for (int i = 0; i < rVillage.plots.size(); ++i)
    {
        for (int k = 0; k < rVillage.plots[i].buildings.size(); ++k)
        {
            min_area += rVillage.plots[i].buildings[k].area;
        }
    }
    if (min_area == 0)
    {
        std::cerr << "Failed to calculate minimum value\n";
        min_area = rVillage.area;
    } 
    return min_area;
}

void CreateVillage(Village &rVillage)
{
    std::cout << std::string(GetStrLen(), '~') << std::endl;
    int val;
    
    // Number of plots
    std::cout << "Number of plots in the village: ";
    val = GetInt();
    CreatePlots(rVillage, val);

    std::cout << std::string(GetStrLen(), '~') << std::endl;

    // Village area
    int min_area = GetMinVillageArea(rVillage);
    std::cout << "Village area (from " << min_area << "): ";
    rVillage.area = GetInt(min_area);

    double buildings_part = double(min_area) / double(rVillage.area) * 100;
    printf("Buildings occupy %.2f%% of the village's area\n", buildings_part);
}

std::string RoomTypeToStr(RoomType room_type)
{
    switch (room_type)
    {
    case RoomType::kOtherRoom:
        return "other";
    case RoomType::kBathroom:
        return "bathroom";
    case RoomType::kBedroom:
        return "bedroom";
    case RoomType::kChildren:
        return "children";
    case RoomType::kKitchen:
        return "kitchen";
    case RoomType::kLiving:
        return "living";
    default:
        std::cerr << "Failed to convert";
        return "";
    }
}

std::string BuildingTypeToStr(BuildingType building_type)
{
    switch (building_type)
    {
    case BuildingType::kOtherBuilding:
        return "other";
    case BuildingType::kBathhouse:
        return "bathhouse";
    case BuildingType::kResidential:
        return "residential";
    case BuildingType::kGarage:
        return "garage";
    case BuildingType::kShed:
        return "shed";
    default:
        std::cerr << "Failed to convert";
        return "";
    }
}

void PrintVillage(Village &rVillage)
{
    std::cout << std::endl << std::string(GetStrLen(), '#') << std::endl;
    std::cout << ">>>>> Village <<<<<" << std::endl;
    std::cout << "Area: " << rVillage.area << std::endl;
    std::cout << "Plots: " << rVillage.plots.size() << std::endl;
    for (int i = 0; i < rVillage.plots.size(); ++i)
    {
        std::cout << ">>>> Plot #" << i << " <<<<" << std::endl;
        std::cout << "Number: " << rVillage.plots[i].id << std::endl;
        std::cout << "Buildings: " << rVillage.plots[i].buildings.size() << std::endl;
        for (int j = 0; j < rVillage.plots[i].buildings.size(); ++j)
        {
            std::cout << ">>> Building #" << j << " <<<" << std::endl;
            std::cout << "Type: " << BuildingTypeToStr(rVillage.plots[i].buildings[j].type) << std::endl;
            std::cout << "Area: " << rVillage.plots[i].buildings[j].area << std::endl;
            if (rVillage.plots[i].buildings[j].has_stove) std::cout << "Has stove" << std::endl;
            if (rVillage.plots[i].buildings[j].type != BuildingType::kResidential)
            {
                std::cout << "Height: " << rVillage.plots[i].buildings[j].floors[0].height << std::endl;
            }
            else
            {
                std::cout << "Floors: " << rVillage.plots[i].buildings[j].floors.size() << std::endl;
                for (int k = 0; k < rVillage.plots[i].buildings[j].floors.size(); ++k)
                {
                    std::cout << ">> Floor #" << k << " <<" << std::endl;
                    std::cout << "Height: " << rVillage.plots[i].buildings[j].floors[k].height << std::endl;
                    std::cout << "Rooms: " << rVillage.plots[i].buildings[j].floors[k].rooms.size() << std::endl;
                    for (int l = 0; l < rVillage.plots[i].buildings[j].floors[k].rooms.size(); ++l)
                    {
                        std::cout << "> Room #" << l << " <" << std::endl;
                        std::cout << "Type: " << RoomTypeToStr(rVillage.plots[i].buildings[j].floors[k].rooms[l].type) << std::endl;
                        std::cout << "Area: " << rVillage.plots[i].buildings[j].floors[k].rooms[l].area << std::endl;
                        
                    }
                }
            }

            
        }
    }
    std::cout << std::string(GetStrLen(), '#') << std::endl;
}



int main() 
{
    Village some_village;

    CreateVillage(some_village);

    PrintVillage(some_village);
}