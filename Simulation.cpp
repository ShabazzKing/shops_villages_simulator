#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include "Facility.hpp"
#include "Picture.hpp"

void findNearestShop(Village &, std::vector<Shop> &);
double averageCustomers(const std::vector<Shop> &);
double averageVillages(const std::vector<Shop> &);

int main()
{
    using std::cout;
    using std::endl;
    using std::cin;
    using std::rand;
    const unsigned WIDTH = 800;
    const unsigned HEIGHT = 800;
    unsigned nVillages, maxCitizens, nShops;
    std::string filename;
    cout << "Symulacja osad i sklepów.\n";
    cout << "Podaj liczbę osad. ";
    cin >> nVillages;
    cout << "Podaj maksymalną liczbę mieszkańców. ";
    cin >> maxCitizens;
    cout << "Podaj liczbę sklepów. ";
    cin >> nShops;
    cout << "Podaj plik do zapisu grafiki (rozszerzenie .ppm).\n";
    cin.ignore();
    std::getline(cin, filename);
    std::ofstream outputFile(filename);
    std::srand(std::time(nullptr));
    std::vector<Village> villages;
    std::vector<Shop> shops;
    for (unsigned i = 0; i < nVillages; i++)
        villages.push_back(Village(rand() % WIDTH, rand() % HEIGHT, 
                           rand() % maxCitizens + 1));
    for (unsigned i = 0; i < nShops; i++)
        shops.push_back(Shop(rand() % WIDTH, rand() % HEIGHT));
    for (unsigned i = 0; i < nVillages; i++)
        findNearestShop(villages[i], shops);
    makePicture(outputFile, villages, shops, WIDTH + 4, HEIGHT + 4);
    outputFile.close();
    cout << "Podaj plik do zapisu diagramu Woronoja dla sklepów.\n";
    std::getline(cin, filename);
    outputFile.open(filename);
    makeVoronoi(outputFile, shops, WIDTH + 4, HEIGHT + 4);
    outputFile.close();
    cout << "Podaj plik do zapisu diagramu Woronoja dla osad.\n";
    std::getline(cin, filename);
    outputFile.open(filename);
    makeVoronoi(outputFile, villages, WIDTH + 4, HEIGHT + 4);
    outputFile.close();
    cout << "Statystyki:\n";
    cout << "liczba osób na sklep:\n";
    for (unsigned i = 0; i < nShops; i++)
        cout << "Sklep nr " << i + 1 << ": " << shops[i].get_customers() << endl;
    cout << "liczba osad na sklep:\n";
    for (unsigned i = 0; i < nShops; i++)
        cout << "Sklep nr " << i + 1 << ": " << shops[i].get_villages() << endl;
    double min_distance = villages[0].get_distance();
    double max_distance = min_distance;
    for (unsigned i = 1; i < nVillages; i++)
    {
        double temp = villages[i].get_distance();
        if (min_distance > temp)
            min_distance = temp;
        if (max_distance < temp)
            max_distance = temp;
    }
    cout << "najmniejsza odległość do najbliższego sklepu wynosi " << min_distance << endl;
    cout << "największa odległość do najbliższego sklepu wynosi " << max_distance << endl;
    double av;
    av = averageCustomers(shops);
    cout << "średnio osób na sklep: " << av << endl;
    av = averageVillages(shops);
    cout << "średnio osad na sklep: " << av << endl;
    return 0;
}

void findNearestShop(Village & village, std::vector<Shop> & shops)
{
    double min_distance, distance;
    Shop * nearest = &shops[0];
    min_distance = std::sqrt(power(village.get_x() - shops[0].get_x(), 2) + 
                            power(village.get_y() - shops[0].get_y(), 2));
    for (unsigned i = 1; i < shops.size(); i++)
    {
        distance = std::sqrt(power(village.get_x() - shops[i].get_x(), 2) + 
                            power(village.get_y() - shops[i].get_y(), 2));
        if (distance < min_distance)
        {
            min_distance = distance;
            nearest = &shops[i];
        }
    }
    village.set_shop(*nearest);
    nearest->set_customers(nearest->get_customers() + village.get_citizens());
    nearest->set_villages(nearest->get_villages() + 1);
}

double averageCustomers(const std::vector<Shop> & shops)
{
    double result = 0.0;
    for (unsigned i = 0; i < shops.size(); i++)
        result += shops[i].get_customers();
    result /= shops.size();
    return result;
}

double averageVillages(const std::vector<Shop> & shops)
{
    double result = 0.0;
    for (unsigned i = 0; i < shops.size(); i++)
        result += shops[i].get_villages();
    result /= shops.size();
    return result;
}
