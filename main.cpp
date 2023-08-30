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

	int testcase = std::stoi(argv[1]);
	int seed = std::stoi(argv[2]);

	std::random_device rd;
	std::mt19937 generator(rd());

	p = loadData("tests/pmed" + std::to_string(testcase) + ".txt", bestKnownSol);

	generator.seed(1);

	Algorithm alg = Algorithm(p, generator);
	Result res = alg.execute();
	
	//std::cout << res.minDistance << " " << bestKnownSol << std::endl;
	std::string foldername = "results/case_" + std::to_string(testcase);
	std::filesystem::create_directories(foldername);
	std::string filename = foldername + "/seed_" + std::to_string(seed) + ".txt";
	std::ofstream output(filename);
	std::cout<<filename<<std::endl;
	output << res.minDistance << " " << bestKnownSol << std::endl;
}