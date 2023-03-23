#include "TSP.hpp"
#include <algorithm>

 void
readDistances (const std::string & filename,
	       std::vector < std::vector < double >>&distances)
{
  
std::ifstream inputFile (filename);
  
if (!inputFile)
    {
      
std::cerr << "Unable to open file " << filename << std::endl;
      
exit (1);
    
}
  
for (int i = 0; i < distances.size (); i++)
    {
      
for (int j = 0; j < distances[i].size (); j++)
	{
	  
inputFile >> distances[i][j];

} 
} 
} 
 
double

calculateCost (const std::vector < int >&path,
	       const std::vector < std::vector < double >>&distances)
{
  
double cost = 0.0;
  
for (int i = 0; i < path.size () - 1; i++)
    {
      
int city1 = path[i];
      
int city2 = path[i + 1];
      
cost += distances[city1][city2];
    
} 
int lastCity = path[path.size () - 1];
  
int firstCity = path[0];
  
cost += distances[lastCity][firstCity];
  
return cost;
}


 
std::vector < int >
bruteForce (const std::vector < std::vector < double >>&distances,
	    const int &numCities)
{
  
std::vector < int >
  path (numCities);
  
for (int i = 0; i < numCities; i++)
    {
      
path[i] = i;
    
} 
std::vector < int >
    bestPath = path;
  
double
    bestCost = calculateCost (path, distances);
  
while (std::next_permutation (path.begin (), path.end ()))
    {
      
double
	currentCost = calculateCost (path, distances);
      
if (currentCost < bestCost)
	{
	  
bestPath = path;
	  
bestCost = currentCost;
	
}
    
}
  
return bestPath;

}


 
std::vector < int >
geneticAlgorithm (const std::vector < std::vector < double >>&distances,
		  const int &numCities, const int &populationSize,
		  const int &numGenerations, const double &mutationRate)
{
  
// Create initial population
  std::vector < std::vector < int >>
  population (populationSize, std::vector < int >(numCities));
  
for (int i = 0; i < populationSize; i++)
    {
      
std::vector < int >
      path (numCities);
      
for (int j = 0; j < numCities; j++)
	{
	  
path[j] = j;
	
} 
std::random_shuffle (path.begin (), path.end ());
      
population[i] = path;
    
} 
// Iterate over generations
    for (int generation = 0; generation < numGenerations; generation++)
    {
      
	// Evaluate fitness
      std::vector < double >
      fitness (populationSize);
      
double
	totalFitness = 0.0;
      
for (int i = 0; i < populationSize; i++)
	{
	  
double
	    cost = calculateCost (population[i], distances);
	  
double
	    fit = 1.0 / cost;
	  
fitness[i] = fit;
	  
totalFitness += fit;
	
} 
 
	// Select parents
      std::vector < std::vector < int >>
      parents (populationSize, std::vector < int >(numCities));
      
for (int i = 0; i < populationSize; i++)
	{
	  
	    // Roulette wheel selection
	    double
	    r = ((double) rand () / (RAND_MAX)) * totalFitness;
	  
int
	    j = 0;
	  
double
	    s = fitness[j];
	  
while (s < r)
	    {
	      
j++;
	      
s += fitness[j];
	    
}
	  
parents[i] = population[j];
	
}
      
 
	// Create offspring
      std::vector < std::vector < int >>
      offspring (populationSize, std::vector < int >(numCities));
      
for (int i = 0; i < populationSize; i += 2)
	{
	  
int
	    parent1Index = rand () % populationSize;
	  
int
	    parent2Index = rand () % populationSize;
	  
std::vector < int >
	    parent1 = parents[parent1Index];
	  
std::vector < int >
	    parent2 = parents[parent2Index];
	  
int
	    crossoverPoint = rand () % numCities;
	  
 
	    // Create child
	  std::vector < int >
	  child (numCities);
	  
for (int j = 0; j < crossoverPoint; j++)
	    {
	      
child[j] = parent1[j];
	  
} 
for (int j = crossoverPoint; j < numCities; j++)
	    {
	      
// Check if city already in child
		bool cityAlreadyInChild = false;
	      
for (int k = 0; k < crossoverPoint; k++)
		{
		  
if (parent2[j] == child[k])
		    {
		      
cityAlreadyInChild = true;
		      
break;
		    
}
		
}
	      
if (!cityAlreadyInChild)
		{
		  
child[j] = parent2[j];
		
}
	      else
		{
		  
// Find next available city from parent 2
		    for (int k = crossoverPoint; k < numCities; k++)
		    {
		      
bool cityAlreadyInChild2 = false;
		      
for (int l = 0; l < crossoverPoint; l++)
			{
			  
if (parent2[k] == child[l])
			    {
			      
cityAlreadyInChild2 = true;
			      
break;
			    
}
			
}
		      
if (!cityAlreadyInChild2)
			{
			  
child[j] = parent2[k];
			  
break;
			
}
		    
}
		
}
	    
}
	  
offspring[i] = child;	// Create second child
	  std::vector < int >
	  child2 (numCities);
	  
for (int j = 0; j < crossoverPoint; j++)
	    {
	      
child2[j] = parent2[j];
	  
} 
for (int j = crossoverPoint; j < numCities; j++)
	    {
	      
		// Check if city already in child
		bool cityAlreadyInChild = false;
	      
for (int k = 0; k < crossoverPoint; k++)
		{
		  
if (parent1[j] == child2[k])
		    {
		      
cityAlreadyInChild = true;
		      
break;
		    
}
		
}
	      
if (!cityAlreadyInChild)
		{
		  
child2[j] = parent1[j];
		
}
	      else
		{
		  
		    // Find next available city from parent 1
		    for (int k = crossoverPoint; k < numCities; k++)
		    {
		      
bool cityAlreadyInChild2 = false;
		      
for (int l = 0; l < crossoverPoint; l++)
			{
			  
if (parent1[k] == child2[l])
			    {
			      
cityAlreadyInChild2 = true;
			      
break;
			    
}
			
}
		      
if (!cityAlreadyInChild2)
			{
			  
child2[j] = parent1[k];
			  
break;
			
}
		    
}
		
}
	    
}
	  
offspring[i + 1] = child2;
	
}
      
 
// Mutate offspring
	for (int i = 0; i < populationSize; i++)
	{
	  
for (int j = 0; j < numCities; j++)
	    {
	      
double
		r = ((double) rand () / (RAND_MAX));
	      
if (r < mutationRate)
		{
		  
int
		    k = rand () % numCities;
		  
int
		    temp = offspring[i][j];
		  
offspring[i][j] = offspring[i][k];
		  
offspring[i][k] = temp;
		
}
	
} 
} 
 
// Replace population with offspring
	population = offspring;
    
} 
 
// Find best path in final population
  std::vector < int >
    bestPath = population[0];
  
double
    bestCost = calculateCost (bestPath, distances);
  
for (int i = 1; i < populationSize; i++)
    {
      
double
	currentCost = calculateCost (population[i], distances);
      
if (currentCost < bestCost)
	{
	  
bestPath = population[i];
	  
bestCost = currentCost;
	
}
    
}
  
return bestPath;

}
