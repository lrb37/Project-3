#include <iostream>
#include <string>
#include <vector>
#include "TSP.hpp"

int main() {
    // Read distances from file
    std::vector<std::vector<double>> distances(20, std::vector<double>(20));
    readDistances("distances.txt", distances);

    // Get user input
    int numCities, populationSize, numGenerations;
    double mutationRate;
    std::cout << "Enter the number of cities to run: ";
    std::cin >> numCities;
    std::cout << "Enter the number of individual tours in a population: ";
std::cin >> populationSize;
std::cout << "Enter the number of generations to run: ";
std::cin >> numGenerations;
std::cout << "Enter the mutation rate: ";
std::cin >> mutationRate;
// Solve TSP using brute force
std::vector<int> bfPath = bruteForce(distances, numCities);
double bfCost = calculateCost(bfPath, distances);

// Solve TSP using genetic algorithm
std::vector<int> gaPath = geneticAlgorithm(distances, numCities, populationSize, numGenerations, mutationRate);
double gaCost = calculateCost(gaPath, distances);

// Print results
std::cout << "Brute force solution:" << std::endl;
for (int i = 0; i < bfPath.size(); i++) {
    std::cout << bfPath[i] << " ";
}
std::cout << std::endl;
std::cout << "Cost: " << bfCost << std::endl;

std::cout << "Genetic algorithm solution:" << std::endl;
for (int i = 0; i < gaPath.size(); i++) {
    std::cout << gaPath[i] << " ";
}
std::cout << std::endl;
std::cout << "Cost: " << gaCost << std::endl;

return 0;
}
