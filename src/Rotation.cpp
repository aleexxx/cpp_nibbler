#include "Rotation.hpp"

rotation::rotation()
{
}

rotation::~rotation()
{

}

void rotation::rotation_left(int &my_rotation, int &x, int &y)
{
    my_rotation += 90;
    if (my_rotation == 360)
        my_rotation = 0;
    rotate(my_rotation, x, y);
}

void rotation::rotation_right(int &my_rotation, int &x, int &y)
{
    my_rotation -= 90;
    if (my_rotation == -360)
        my_rotation = 0;
    rotate(my_rotation, x, y);
}

void rotation::rotate(const int &rotation, int &x, int &y)
{
    if (rotation == 0)
    {
        x = 1;
        y = 0;
    }
    else if (rotation == 90 || rotation == -270)
    {
        x = 0;
        y = -1;
    }
    else if (rotation == 180 || rotation == -180)
    {
        x = -1;
        y = 0;
    }
    else if (rotation == 270 || rotation == -90)
    {
        x = 0;
        y = 1;
    }
}
