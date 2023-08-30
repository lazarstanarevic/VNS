#include "structures.hpp"
#include "algorithm.hpp"
#include <random>
#include <string>
#include <filesystem>
#include <iostream>

int main()
{
	double bestKnownSol;
	Problem p;

	std::random_device rd;
	std::mt19937 generator(rd());

	p = loadData("pmed2.dat", bestKnownSol);

	generator.seed(1);

	Algorithm alg = Algorithm(p, generator);
	Result res = alg.execute();
	
	std::cout << res.minDistance << " " << bestKnownSol << std::endl;
}