#include <cmath>
#include "Facility.hpp"

Facility::Facility(unsigned x_coord, unsigned y_coord) : x(x_coord), y(y_coord) {}

unsigned Facility::get_x() const
{
    return x;
}

unsigned Facility::get_y() const
{
    return y;
}

Shop::Shop(unsigned x_coord, unsigned y_coord) : Facility(x_coord, y_coord), 
                                        customers(0), villages(0) {}

unsigned Shop::get_customers() const
{
    return customers;
}

void Shop::set_customers(unsigned c)
{
    customers = c;
}

unsigned Shop::get_villages() const
{
    return villages;
}

void Shop::set_villages(unsigned v)
{
    villages = v;
}

Village::Village(unsigned x_coord, unsigned y_coord, unsigned c) : 
                Facility(x_coord, y_coord), citizens(c), nearest(nullptr), distance(0.0) {}

unsigned Village::get_citizens() const
{
    return citizens;
}

Shop & Village::get_shop() const
{
    return *nearest;
}

void Village::set_shop(Shop & S)
{
    nearest = &S;
    distance = std::sqrt((get_x() - S.get_x()) * (get_x() - S.get_x()) + 
                        (get_y() - S.get_y()) * (get_y() - S.get_y()));
}

double Village::get_distance() const
{
    return distance;
}
