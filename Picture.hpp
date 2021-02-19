#ifndef PICTURE_HPP
#define PICTURE_HPP
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Facility.hpp"

void makePicture(std::ofstream &, const std::vector<Village> &, const std::vector<Shop> &, 
                 const unsigned, const unsigned);

struct triplet
{
    int r;
    int g;
    int b;
};

unsigned power(unsigned, unsigned);

template <typename T>
void print_color(std::ofstream &, const std::vector<T> &, const std::vector<triplet> &,
                 const unsigned, const unsigned);

template <typename T>
void makeVoronoi(std::ofstream & file, const std::vector<T> & objects, 
                 const unsigned WIDTH, const unsigned HEIGHT)
{
    std::vector<std::vector<const T *>> objectsLocation;
    for (unsigned i = 0; i < WIDTH - 4; i++)
    {
        objectsLocation.push_back(std::vector<const T *>());
        for (unsigned j = 0; j < HEIGHT - 4; j++)
            objectsLocation[i].push_back(nullptr);
    }
    for (unsigned i = 0; i < objects.size(); i++)
        objectsLocation[objects[i].get_x()][objects[i].get_y()] = &objects[i];
    std::srand(std::time(nullptr));
    std::vector<triplet> colors;
    for (unsigned i = 0; i < objects.size(); i++)
    {
        triplet temp;
        temp.r = rand() % 256;
        temp.g = rand() % 256;
        temp.b = rand() % 256;
        colors.push_back(temp);
    }
    std::vector<std::vector<bool>> pixels;
    for (unsigned i = 0; i < WIDTH; i++)
    {
        pixels.push_back(std::vector<bool>());
        for (unsigned j = 0; j < HEIGHT; j++)
            pixels[i].push_back(false);
    }
    for (unsigned i = 2; i < WIDTH - 2; i++)
        for (unsigned j = 2; j < HEIGHT - 2; j++)
            if (objectsLocation[i - 2][j - 2] != nullptr)
                for (unsigned k = i - 2; k <= i + 2; k++)
                    for (unsigned l = j - 2; l <= j + 2; l++)
                        pixels[k][l] = true;
    file << "P3\n";
    file << WIDTH << " " << HEIGHT << std::endl;
    file << 255 << std::endl;
    for (unsigned j = 0; j < HEIGHT; j++)
        for (unsigned i = 0; i < WIDTH; i++)
            if (pixels[i][j])
                file << "0 255 0\n";
            else
                print_color(file, objects, colors, i, j);
}

template <typename T>
void print_color(std::ofstream & file, const std::vector<T> & objects,
                 const std::vector<triplet> & colors, const unsigned x, const unsigned y)
{
    unsigned objectNumber = 0;
    double min_distance, distance;
    min_distance = std::sqrt(power(x - objects[0].get_x(), 2) + 
                            power(y - objects[0].get_y(), 2));
    for (unsigned i = 1; i < objects.size(); i++)
    {
        distance = std::sqrt(power(x - objects[i].get_x(), 2) + 
                            power(y - objects[i].get_y(), 2));
        if (distance < min_distance)
        {
            min_distance = distance;
            objectNumber = i;
        }
    }
    file << colors[objectNumber].r << " " << colors[objectNumber].g << " ";
    file << colors[objectNumber].b << std::endl;
}

#endif
