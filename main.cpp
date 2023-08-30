#include "structures.hpp"
#include "algorithm.hpp"
#include <random>
#include <string>
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[])
{
	double bestKnownSol;
	Problem p;

	int seed = std::stoi(argv[2]);

	std::random_device rd;
	std::mt19937 generator(rd());

	p = loadData(argv[1], bestKnownSol);

	generator.seed(1);

	Algorithm alg = Algorithm(p, generator);
	Result res = alg.execute();
	
	std::cout << res.minDistance << " " << bestKnownSol << std::endl;
}