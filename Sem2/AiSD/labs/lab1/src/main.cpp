#include <iostream>
#include <cmath>

struct point
{
    int x;
    int y;
    int prev_x;
    int prev_y;
};


int main()
{
    int polygons, points, Area;

    std::cin >> polygons;

    for (int p = 0; p < polygons; p++)
    {
        std::cin >> points;
        points /= 2;
        Area = 0;

        point starting_point;

        std::cin >> starting_point.x;
        std::cin >> starting_point.y;

        point current_point;
        current_point.prev_x = starting_point.x;
        current_point.prev_y = starting_point.y;

        for (int i = 0; i < points - 1; i++)
        {
            std::cin >> current_point.x;
            std::cin >> current_point.y;

            Area += (current_point.prev_x * current_point.y) - (current_point.x * current_point.prev_y);

            current_point.prev_x = current_point.x;
            current_point.prev_y = current_point.y;
        }

        Area += (current_point.x * starting_point.y) - (starting_point.x * current_point.y);
        Area /= 2;
        Area = abs(Area);

        std::cout << Area << std::endl;
    }

    return 0;
}