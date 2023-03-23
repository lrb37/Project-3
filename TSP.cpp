#include "TSP.hpp"
#include <algorithm>
#include <random>

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
    for (int i = 0; i < path.size(); i++) {
int fromCity = path[i];
int toCity = path[(i + 1) % path.size()];
cost += distances[fromCity][toCity];
}
return cost;
}

std::vector<int> bruteForce(const std::vector<std::vector<double>>& distances, const int& numCities) {
std::vector<int> path(numCities);
for (int i = 0; i < numCities; i++) {
path[i] = i;
}
std::vector<int> bestPath = path;
double bestCost = calculateCost(bestPath, distances);
while (std::next_permutation(path.begin(), path.end())) {
    double cost = calculateCost(path, distances);
    if (cost < bestCost) {
        bestPath = path;
        bestCost = cost;
    }
}

return bestPath;
}

std::vector<int> geneticAlgorithm(const std::vector<std::vector<double>>& distances, const int& numCities, const int& populationSize, const int& numGenerations, const double& mutationRate) {
// Initialize population
std::vector<std::vector<int>> population(populationSize, std::vector<int>(numCities));
for (int i = 0; i < populationSize; i++) {
for (int j = 0; j < numCities; j++) {
population[i][j] = j;
}
std::random_shuffle(population[i].begin(), population[i].end());
}
// Evaluate fitness of initial population
std::vector<double> fitness(populationSize);
double totalFitness = 0.0;
double bestCost = std::numeric_limits<double>::max();
std::vector<int> bestPath(numCities);
for (int i = 0; i < populationSize; i++) {
    double cost = calculateCost(population[i], distances);
    fitness[i] = 1.0 / cost;
    totalFitness += fitness[i];
    if (cost < bestCost) {
        bestCost = cost;
        bestPath = population[i];
    }
}

// Run evolution
for (int generation = 0; generation < numGenerations; generation++) {
    // Create next generation
    std::vector<std::vector<int>> nextGeneration(populationSize, std::vector<int>(numCities));
    for (int i = 0; i < populationSize; i++) {
        // Select parents
        std::uniform_real_distribution<double> distribution(0.0, totalFitness);
        std::default_random_engine generator;
        double randomValue = distribution(generator);
        int parent1 = -1;
        double sum = 0.0;
        for (int j = 0; j < populationSize; j++) {
            sum += fitness[j];
            if (sum >= randomValue) {
                parent1 = j;
                break;
            }
        }
        randomValue = distribution(generator);
        int parent2 = -1;
        sum = 0.0;
        for (int j = 0; j < populationSize; j++) {
            sum += fitness[j];
            if (sum >= randomValue) {
                parent2 = j;
                break;
            }
        }

        // Crossover
        std::uniform_int_distribution<int> intDistribution(0, numCities - 1);
        int crossoverPoint1 = intDistribution(generator);
        int crossoverPoint2 = intDistribution(generator);
        if (crossoverPoint1 > crossoverPoint2) {
            std::swap(crossoverPoint1, crossoverPoint2);
        }
        std::vector<int> child(numCities);
        for(int j = crossoverPoint1; j <= crossoverPoint2; j++) {
child[j] = population[parent1][j];
}
int index = 0;
for (int j = 0; j < numCities; j++) {
if (index == crossoverPoint1) {
index = crossoverPoint2 + 1;
}
bool alreadyInChild = false;
for (int k = crossoverPoint1; k <= crossoverPoint2; k++) {
if (population[parent2][j] == child[k]) {
alreadyInChild = true;
break;
}
}
if (!alreadyInChild) {
child[index] = population[parent2][j];
index++;
}
}
   // Mutate
    std::uniform_real_distribution<double> mutationDistribution(0.0, 1.0);
    for (int j = 0; j < numCities; j++) {
        if (mutationDistribution(generator) < mutationRate) {
            int randomIndex = intDistribution(generator);
            std::swap(child[j], child[randomIndex]);
        }
    }

    nextGeneration[i] = child;
}

// Evaluate fitness of next generation
fitness.clear();
fitness.resize(populationSize);
totalFitness = 0.0;
for (int i = 0; i < populationSize; i++) {
    double cost = calculateCost(nextGeneration[i], distances);
    fitness[i] = 1.0 / cost;
    totalFitness += fitness[i];
    if (cost < bestCost) {
        bestCost = cost;
        bestPath = nextGeneration[i];
    }
}

// Update population
population = nextGeneration;
}

return bestPath;
}
