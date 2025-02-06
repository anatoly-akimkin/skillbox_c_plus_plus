#include <iostream>
#include <cassert>

// Задание 3. Использование assert. Что нужно сделать. Создайте в своей программе функцию float travelTime(float distance, float speed). Она будет находить время в пути и при этом использовать assert, чтобы отбросить нулевую и отрицательную скорость. Вызовите эту функцию в main. Убедитесь, что падение происходит за счёт assert. Не забудьте подключить заголовочный файл cassert. Что оценивается. При запуске происходит падение с указанием исходника и строки в нём, на которой расположен вызов макроса assert.

float travelTime(float distance, float speed)
{
    assert (speed > 0);
    return distance / speed;
}

int main() 
{
    float distance, speed;
    std::cout << "Enter distance: ";
    std::cin >> distance;
    std::cout << "Enter speed: ";
    std::cin >> speed;

    std::cout << "Travel time: " << travelTime(distance, speed) << std::endl;
}