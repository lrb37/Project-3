/***************************************************************
Student Name: Logan Belew
File Name: main.cpp
Assignment number 3

This program reads distances between cities from a file and solves
the traveling salesman problem using brute force and genetic algorithm.
It prompts the user to enter the number of cities to run, the number
of individual tours in a population, the number of generations to run,
and the mutation rate.

***************************************************************/

/*#include <iostream>
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
*/ #include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "TSP.hpp"

int main() {
    // Read distances from file
    std::vector<std::vector<double>> distances(20, std::vector<double>(20));
    readDistances("distances.txt", distances);

    // Create spreadsheet
    std::cout << "Number of Cities\tPopulation Size\tNumber of Generations\tMutation Rate\tBrute Force Time (s)\tGA Time (s)\tBrute Force Cost\tGA Cost\tGA Cost Percentage of Optimal" << std::endl;

    // Run TSP solver for different values of parameters
    for (int numCities = 10; ; numCities++) {
        if (bruteForce(distances, numCities).size() == 0) {
            break;
        }
        for (int populationSize = 10; populationSize <= numCities; populationSize += 10) {
            for (int numGenerations = 10; numGenerations <= 100; numGenerations += 10) {
                for (double mutationRate = 0.1; mutationRate <= 0.5; mutationRate += 0.1) {
                    // Solve TSP using brute force
                    std::vector<int> bfPath;
                    double bfCost;
                    auto bfStart = std::chrono::steady_clock::now();
                    bfPath = bruteForce(distances, numCities);
                    bfCost = calculateCost(bfPath, distances);
                    auto bfEnd = std::chrono::steady_clock::now();
                    double bfTime = std::chrono::duration<double>(bfEnd - bfStart).count();

                    // Solve TSP using genetic algorithm
                    std::vector<int> gaPath;
                    double gaCost;
                    auto gaStart = std::chrono::steady_clock::now();
                    gaPath = geneticAlgorithm(distances, numCities, populationSize, numGenerations, mutationRate);
                    gaCost = calculateCost(gaPath, distances);
                    auto gaEnd = std::chrono::steady_clock::now();
                    double gaTime = std::chrono::duration<double>(gaEnd - gaStart).count();

                    // Calculate GA cost percentage of optimal
                    double gaCostPercentage = (bfCost == 0) ? 0 : (gaCost / bfCost) * 100;

                    // Output results to spreadsheet
                    std::cout << numCities << "\t" << populationSize << "\t" << numGenerations << "\t" << mutationRate << "\t" << bfTime << "\t" << gaTime << "\t" << bfCost << "\t" << gaCost << "\t" << gaCostPercentage << std::endl;
}
}
}
}
return 0;
}
