#include <iostream>
#include <typeinfo>
#include "Picture.hpp"

void makePicture(std::ofstream & file, const std::vector<Village> & villages, 
                 const std::vector<Shop> & shops, const unsigned WIDTH, 
                 const unsigned HEIGHT)
{
    std::vector<std::vector<const Facility *>> objectsLocation;
    for (unsigned i = 0; i < WIDTH - 4; i++)
    {
        objectsLocation.push_back(std::vector<const Facility *>());
        for (unsigned j = 0; j < HEIGHT - 4; j++)
            objectsLocation[i].push_back(nullptr);
    }
    for (unsigned i = 0; i < shops.size(); i++)
        objectsLocation[shops[i].get_x()][shops[i].get_y()] = &shops[i];
    for (unsigned i = 0; i < villages.size(); i++)
        if (objectsLocation[villages[i].get_x()][villages[i].get_y()] == nullptr)
            objectsLocation[villages[i].get_x()][villages[i].get_y()] = &villages[i];
    std::vector<std::vector<char>> pixels;
    for (unsigned i = 0; i < WIDTH; i++)
    {
        pixels.push_back(std::vector<char>());
        for (unsigned j = 0; j < HEIGHT; j++)
            pixels[i].push_back('0');
    }
    for (unsigned i = 2; i < WIDTH - 2; i++)
        for (unsigned j = 2; j < HEIGHT - 2; j++)
        {
            bool isShop;
            try
            {
                isShop = (typeid(*objectsLocation[i - 2][j - 2]) == typeid(Shop));
            }
            catch (std::bad_typeid &)
            {
                continue;
            }
            if (isShop)
                for (unsigned k = i - 2; k <= i + 2; k++)
                    for (unsigned l = j - 2; l <= j + 2; l++)
                        pixels[k][l] = 'S';
            else
                for (unsigned k = i - 2; k <= i + 2; k++)
                    for (unsigned l = j - 2; l <= j + 2; l++)
                        if (pixels[k][l] != 'S')
                            pixels[k][l] = 'V';
        }
    file << "P3\n";
    file << WIDTH << " " << HEIGHT << std::endl;
    file << 255 << std::endl;
    for (unsigned j = 0; j < HEIGHT; j++)
        for (unsigned i = 0; i < WIDTH; i++)
            if (pixels[i][j] == 'S')
                file << "0 255 0\n";
            else if (pixels[i][j] == 'V')
                file << "255 0 0\n";
            else
                file << "255 255 255\n";
}

unsigned power(unsigned base, unsigned exp)
{
    unsigned result = 1;
    for (unsigned i = 0; i < exp; i++)
        result *= base;
    return result;
}
