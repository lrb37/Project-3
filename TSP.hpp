/***************************************************************
Student Name: Logan Belew
File Name: tsp.hpp
Assignment number 3

Header file for TSP functions, including reading distances from file,
calculating the cost of a path, and implementing the brute force and
genetic algorithm approaches to the Traveling Salesman Problem.

***************************************************************/

#ifndef TSP_HPP
#define TSP_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readDistances(const std::string& filename, std::vector<std::vector<double>>& distances);
double calculateCost(const std::vector<int>& path, const std::vector<std::vector<double>>& distances);
std::vector<int> bruteForce(const std::vector<std::vector<double>>& distances, const int& numCities);
std::vector<int> geneticAlgorithm(const std::vector<std::vector<double>>& distances, const int& numCities, const int& populationSize, const int& numGenerations, const double& mutationRate);

#endif
