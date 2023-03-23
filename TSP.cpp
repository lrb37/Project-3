#include "TSP.hpp"
#include <algorithm>

void readDistances(const std::string& filename, std::vector<std::vector<double>>& distances) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        exit(1);
    }
    for (int i = 0; i < distances.size(); i++) {
        for (int j = 0; j < distances[i].size(); j++) {
            inputFile >> distances[i][j];
        }
    }
}

double calculateCost(const std::vector<int>& path, const std::vector<std::vector<double>>& distances) {
    double cost = 0.0;
    for (int i = 0; i < path.size() - 1; i++) {
        cost += distances[path[i]][path[i + 1]];
    }
    cost += distances[path[path.size() - 1]][path[0]];
    return cost;
}

std::vector<int> bruteForce(const std::vector<std::vector<double>>& distances, const int& numCities) {
    std::vector<int> path(numCities);
    for (int i = 0; i < numCities; i++) {
        path[i] = i;
    }
    double minCost = calculateCost(path, distances);
    std::vector<int> bestPath = path;
    while (std::next_permutation(path.begin(), path.end())) {
        double cost = calculateCost(path, distances);
        if (cost < minCost) {
            minCost = cost;
            bestPath = path;
        }
    }
    return bestPath;
}

std::vector<int> geneticAlgorithm(const std::vector<std::vector<double>>& distances, const int& numCities, const int& populationSize, const int& numGenerations, const double& mutationRate) {
    // TODO: Implement genetic algorithm
    std::vector<int> path(numCities);
    return path;
}
