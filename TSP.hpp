#ifndef TSP_HPP
#define TSP_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readDistances (const std::string & filename,
		     std::vector < std::vector < double >>&distances);

double calculateCost (const std::vector < int >&path,
		       const std::vector < std::vector < double >>&distances);

std::vector < int >
bruteForce (const std::vector < std::vector < double >>&distances,
	    const int &numCities);

std::vector < int >
geneticAlgorithm (const std::vector < std::vector < double >>&distances,
		  const int &numCities, const int &populationSize,
		  const int &numGenerations, const double &mutationRate);

 
#endif // TSP_HPP
