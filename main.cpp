#include <iostream>
#include <chrono>
#include "TSP.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::vector<std::vector<double>> distances;
    readDistances(filename, distances);
    int numCities = distances.size();

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> bfPath = bruteForce(distances, numCities);
    auto bfEnd = std::chrono::high_resolution_clock::now();

    auto gaStart = std::chrono::high_resolution_clock::now();
    std::vector<int> gaPath = geneticAlgorithm(distances, numCities, 100, 1000, 0.01);
    auto gaEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Brute force path: ";
    for (std::vector<int>::size_type i = 0; i < bfPath.size(); i++)
    {
        std::cout << bfPath[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Brute force cost: " << calculateCost(bfPath, distances) << std::endl;
    std::cout << "Brute force time: " << std::chrono::duration_cast<std::chrono::milliseconds>(bfEnd - start).count() << " ms" << std::endl;

    std::cout << "Genetic algorithm path: ";
    for (std::vector<int>::size_type i = 0; i < gaPath.size(); i++)
    {
        std::cout << gaPath[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Genetic algorithm cost: " << calculateCost(gaPath, distances) << std::endl;
    std::cout << "Genetic algorithm time: " << std::chrono::duration_cast<std::chrono::milliseconds>(gaEnd - gaStart).count() << " ms" << std::endl;

    return 0;
}
