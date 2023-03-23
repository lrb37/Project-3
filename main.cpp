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

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
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
    auto start_bf = std::chrono::high_resolution_clock::now();
    std::vector<int> bfPath = bruteForce(distances, numCities);
    double bfCost = calculateCost(bfPath, distances);
    auto end_bf = std::chrono::high_resolution_clock::now();
    auto time_bf = std::chrono::duration_cast<std::chrono::microseconds>(end_bf - start_bf);

    // Solve TSP using genetic algorithm
    auto start_ga = std::chrono::high_resolution_clock::now();
    std::vector<int> gaPath = geneticAlgorithm(distances, numCities, populationSize, numGenerations, mutationRate);
    double gaCost = calculateCost(gaPath, distances);
    auto end_ga = std::chrono::high_resolution_clock::now();
    auto time_ga = std::chrono::duration_cast<std::chrono::microseconds>(end_ga - start_ga);

    // Print results
    std::cout << "Number of cities: " << numCities << std::endl;

    for (int i = 0; i < bfPath.size(); i++) {
    }
    std::cout << std::endl;
    std::cout << "Optimal cost: " << bfCost << std::endl;
    std::cout << "Time taken by brute force: " << time_bf.count() << " microseconds" << std::endl;

    for (int i = 0; i < gaPath.size(); i++) {
    }
    std::cout << std::endl;
    std::cout << "Cost: " << gaCost << std::endl;
    std::cout << "Time taken by genetic algorithm: " << time_ga.count() << " microseconds" << std::endl;

    double percent = 100.0 * gaCost / bfCost;
    std::cout << "Percentage of optimal that genetic algorithm produced: " << percent << "%" << std::endl;

    return 0;
}
