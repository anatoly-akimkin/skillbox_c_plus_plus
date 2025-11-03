// Задание 5. Умный дом. Что нужно сделать. Разработайте упрощённую модель умного дома для дачи. Выполните симуляцию его работы на протяжении двух дней. Стартовое время для симуляции умного дома 00:00. Есть несколько датчиков: датчик температуры снаружи, датчик температуры внутри дома. В доме расположен электронный умный щиток с автоматами. Каждый автомат отвечает за включение и отключение определённых устройств или групп устройств:
/*1.отключение и включение питания всего дома;
2.основные розетки дома;
3.свет внутри дома;
4.наружный свет в саду;
5.отопление в помещении;
6.отопление водопровода, идущего из скважины с насосом;
7.кондиционер в помещении.*/
// Есть несколько условий по включению/отключению техники в доме и вне его.
/*- Как только температура снаружи падает ниже 0 °С, надо включить систему обогрева водопровода. Если температура снаружи поднялась выше 5 °С, то систему обогрева водопровода нужно отключить.
- Если на дворе вечер (время больше 16:00 и меньше 5:00 утра) и снаружи есть какое-то движение, то необходимо включить садовое освещение. Если движения нет или время не вечернее, то света снаружи быть не должно.
- Если температура в помещении упала ниже 22 °С, должно включиться отопление. Как только температура равна или поднимается выше 25 °С, отопление автоматически отключается.
- Если температура в помещении поднялась до 30 °С, включается кондиционер. Как только температура становится 25 °С, кондиционер отключается.
- Всё освещение в доме также умное и поддерживает настройку цветовой температуры для комфортного нахождения. Каждый день начиная с 16:00 и до 20:00 температура цвета должна плавно изменяться с 5000K до 2700К. Разумеется, это изменение должно происходить, если свет сейчас включён. В 00:00 температура сбрасывается до 5000К.*/
// Все события по отключению и включению устройств должны выводиться в консоль явным образом. Если устройство не изменило своё состояние (осталось включённым или выключенным), событие генерироваться не должно! Если свет в доме включён, должна отображаться текущая цветовая температура.
// Программа выполняется следующим образом:
/* - Каждый час пользователь сообщает состояние всех основных датчиков и света (температура снаружи, температура внутри, есть ли движение снаружи, включён ли свет в доме).
- Данные параметры вводятся разом в одну строку через пробел, а потом парсятся в переменные из строкового буфера stringstream.
- Информация о движении выводится в формате yes/no.
- Включение и отключение света происходит с помощью on/off.*/
// Рекомендации. Состояние переключателей можно хранить в перечислении вида:
/*enum switches 
{> 
    LIGHTS_INSIDE = 1, 
    LIGHTS_OUTSIDE = 2, 
    HEATERS = 4, 
    WATER_PIPE_HEATING = 8, 
    CONDITIONER = 16 
};*/
// Чтобы включить обогреватель, нужно написать switches_state |= HEATERS; Чтобы выключить — switches_state &= ~HEATERS;
// Пример работы программы:
/*Temp_outside inside, temp_outside outside, movement, lights:
10 10 yes on
Heaters ON!
Lights ON!
Color temp_outside: 5000K
Temp_outside inside, temp_outside outside, movement, lights:
10 10 yes on
Color temp_outside: 5000K
Temp_outside inside, temp_outside outside, movement, lights:
30 30 yes on
Heaters OFF!
Conditioner ON!
Color temp_outside: 5000K
Temp_outside inside, temp_outside outside, movement, lights:
30 30 yes on
Color temp_outside: 5000K
Temp_outside inside, temp_outside outside, movement, lights:*/

#include <iostream>
#include <sstream>

enum switches 
{
    POWER = 1,
    OUTLETS = 2,
    LIGHTS_INSIDE = 4, 
    LIGHTS_OUTSIDE = 8, 
    HEATERS = 16, 
    WATER_PIPE_HEATING = 32, 
    CONDITIONER = 64 
};

int switches_state = 0;

void power_switch()
{
    if ((switches_state & POWER)) 
    {
        switches_state = 0;
    }
    else
    {
        switches_state |= POWER;
        switches_state |= OUTLETS;
    }
}

void water_pipe_heating_system(int temp_outside)
{
    if (temp_outside < 0 && !(switches_state & WATER_PIPE_HEATING))
    {
        switches_state |= WATER_PIPE_HEATING;
        std::cout << "Water pipe heating ON!\n";
    }
    else if (temp_outside > 5 && (switches_state & WATER_PIPE_HEATING))
    {
        switches_state &= ~WATER_PIPE_HEATING;
        std::cout << "Water pipe heating OFF!\n";
    }
}

void indoor_temperature_control(int temp_inside)
{
    // Heaters
    if (!(switches_state & HEATERS) && temp_inside < 22)
    {
        switches_state |= HEATERS;
        std::cout << "Heaters ON!\n";
    } else if ((switches_state & HEATERS) && temp_inside >= 25)
    {
        switches_state &= ~HEATERS;
        std::cout << "Heaters OFF!\n";
    }

    // Conditioner
    if (!(switches_state & CONDITIONER) && temp_inside >= 30)
    {
        switches_state |= CONDITIONER;
        std::cout << "Conditioner ON!\n";
    } else if ((switches_state & CONDITIONER) && temp_inside <= 25)
    {
        switches_state &= ~CONDITIONER;
        std::cout << "Conditioner OFF!\n";
    }
}

void indoor_lighting(std::string lights)
{
    if (lights == "on" && !(switches_state & LIGHTS_INSIDE))
    {
        switches_state |= LIGHTS_INSIDE;
        std::cout << "Lights ON!\n";
    }
    else if (lights == "off" && (switches_state & LIGHTS_INSIDE))
    {
        switches_state &= ~LIGHTS_INSIDE;
        std::cout << "Lights OFF!\n";
    }
}

void garden_lighting(int time, std::string movement)
{
    if ((time % 24 >= 16 || time % 24 < 5) &&
        movement == "yes" && !(switches_state & LIGHTS_OUTSIDE))
    {
        switches_state |= LIGHTS_OUTSIDE;
        std::cout << "Garden lights ON!\n";
    }
    else if (((time % 24 >= 5 && time % 24 < 16) ||
             movement == "no") && (switches_state & LIGHTS_OUTSIDE))
    {
        switches_state &= ~LIGHTS_OUTSIDE;
        std::cout << "Garden lights OFF!\n";
    }
}

int color_temperature(int time)
{
    if (time % 24 > 16 && time % 24 < 20)
    {
        return 5000 - 575 * (time % 24 - 16);
    }
    else if (time % 24 >= 20)
    {
        return 2700;
    }
    else 
    {
        return 5000;
    }
}

int main() 
{
    int operating_time = 0;

    // Turning on the building's power
    power_switch();

    while (switches_state & POWER)
    {
        int temp_inside;
        int temp_outside;
        std::string movement = "";
        std::string lights = "";
        
        bool bad_input = false;
        
        do
        {
            if (bad_input)
            {
                std::cout << "Incorrect input.\n";
            }
            else
            {
                printf("%02d", (operating_time % 24));
                std::cout << ":00 | Temperature inside, temperature outside, movement, lights:\n"; 
            }

            std::string buffer = "";
            getline(std::cin, buffer);
            std::stringstream buffer_stream(buffer);
            buffer_stream >> temp_inside >> temp_outside >> movement >> lights;
            bad_input = (temp_inside < -100 || temp_inside > 100 || 
                         temp_outside < -100 || temp_outside > 100 ||
                         (movement != "yes" && movement != "no") || 
                         (lights != "on" && lights != "off"));
        } while (bad_input);

        water_pipe_heating_system(temp_outside);

        indoor_temperature_control(temp_inside);

        indoor_lighting(lights);
        
        garden_lighting(operating_time, movement);

        if (switches_state & LIGHTS_INSIDE || 
            switches_state & LIGHTS_OUTSIDE)
        {
            std::cout << "Color temperature: " << 
            color_temperature(operating_time) << "K\n";
        }
        
        ++operating_time;
        if (operating_time >= 48) power_switch();
    }
    std::cout << std::string(70, '-') << std::endl << "The trial period is over.\nPlease renew your subscription to enjoy all the features of your smart home!";
}