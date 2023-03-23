#include "TSP.hpp"
#include <algorithm>
#include <random>


void readDistances(const std::string& filename, std::vector<std::vector<double>>& distances)
{
    std::ifstream inputFile(filename);
    int numCities;

    if (inputFile.is_open())
    {
        inputFile >> numCities;
        distances.resize(numCities, std::vector<double>(numCities));

        for (int i = 0; i < numCities; i++)
        {
            for (int j = 0; j < numCities; j++)
            {
                inputFile >> distances[i][j];
            }
        }
        inputFile.close();
    }
}

double calculateCost(const std::vector<int>& path, const std::vector<std::vector<double>>& distances)
{
    double cost = 0.0;
    for (std::vector<int>::size_type i = 0; i < path.size() - 1; i++)
    {
        int city1 = path[i];
        int city2 = path[i + 1];
        cost += distances[city1][city2];
    }
    int lastCity = path[path.size() - 1];
    int firstCity = path[0];
    cost += distances[lastCity][firstCity];
    return cost;
}

std::vector<int> bruteForce(const std::vector<std::vector<double>>& distances, const int& numCities)
{
    std::vector<int> path(numCities);
    std::iota(path.begin(), path.end(), 0);
    double minCost = std::numeric_limits<double>::max();
    std::vector<int> minPath;
    do
    {
        double cost = calculateCost(path, distances);
        if (cost < minCost)
        {
            minCost = cost;
            minPath = path;
        }
    } while (std::next_permutation(path.begin(), path.end()));
    return minPath;
}

std::vector<int> geneticAlgorithm(const std::vector<std::vector<double>>& distances, const int& numCities, const int& populationSize, const int& numGenerations, const double& mutationRate)
{
    std::vector<std::vector<int>> population(populationSize, std::vector<int>(numCities));
    std::vector<int> path(numCities);
    std::iota(path.begin(), path.end(), 0);
    std::vector<int> initialIndividual = path;

    for (auto& individual : population) {
        individual = initialIndividual;
        std::shuffle(individual.begin() + 1, individual.end(), std::mt19937{std::random_device{}()});
    }

    for (int generation = 0; generation < numGenerations; generation++)
    {
        std::vector<std::pair<double, int>> fitnessScores(populationSize);
        for (int i = 0; i < populationSize; i++)
        {
            fitnessScores[i] = std::make_pair(calculateCost(population[i], distances), i);
        }
        std::sort(fitnessScores.begin(), fitnessScores.end());
        std::vector<std::vector<int>> newPopulation(populationSize, std::vector<int>(numCities));
        for (int i = 0; i < populationSize; i += 2)
        {
            int parent1 = fitnessScores[i].second;
            int parent2 = fitnessScores[i + 1].second;
            int crossoverPoint = std::rand() % (numCities - 1) + 1;
            std::vector<int> child1(numCities);
            std::vector<int> child2(numCities);
            std::vector<bool> visited(numCities, false);
            for (int j = 0; j < crossoverPoint; j++)
            {
                child1[j] = population[parent1][j];
                child2[j] = population[parent2][j];
                visited[child1[j]] = true;
            }
            for (int j = crossoverPoint; j < numCities; j++)
{
int remainingCity = -1;
for (int k = 0; k < numCities; k++)
{
if (!visited[population[parent2][k]])
{
remainingCity = population[parent2][k];
break;
}
}
child1[j] = remainingCity;
visited[remainingCity] = true;
}
visited.assign(numCities, false);
for (int j = crossoverPoint; j < numCities; j++)
{
int remainingCity = -1;
for (int k = 0; k < numCities; k++)
{
if (!visited[population[parent1][k]])
{
remainingCity = population[parent1][k];
break;
}
}
child2[j] = remainingCity;
visited[remainingCity] = true;
}
newPopulation[i] = child1;
newPopulation[i + 1] = child2;
}
population = newPopulation;
for (std::vector<int>& individual : population)
{
double mutationProbability = static_cast<double>(std::rand()) / RAND_MAX;
if (mutationProbability < mutationRate)
{
int index1 = std::rand() % numCities;
int index2 = std::rand() % numCities;
std::swap(individual[index1], individual[index2]);
}
}
}
std::vector<std::pair<double, int>> fitnessScores(populationSize);
for (int i = 0; i < populationSize; i++)
{
fitnessScores[i] = std::make_pair(calculateCost(population[i], distances), i);
}
std::sort(fitnessScores.begin(), fitnessScores.end());
return population[fitnessScores[0].second];
}
