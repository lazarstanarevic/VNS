#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_ 

#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using DistanceAndCriticalCount = std::pair<double, int>;
using DistanceAndTime = std::pair<double, int>;

struct Problem
{
    std::vector<std::vector<double>> d;
    std::vector<int> cities;
    int n;
    int p;
};

struct Solution
{
    std::vector<int> x_opt;
    std::vector<int> c1;
    std::vector<int> c2;
    int p;
    int id_crit;
    int critUsersNum;
    std::vector<int> criticalUsers;
    std::vector<bool> isCritical;
    double f_opt;
    std::vector<bool> inSol;
    std::vector<std::priority_queue<std::pair<double, int>>> pq;
};

struct Result
{
    Solution s;
    std::vector<int> includedSites;
    std::vector<DistanceAndTime> history;
    std::vector<int> neighborhoodRuns;
    std::vector<int> neighborhoodImprovements;
    double minDistance;
    double cost;
    double capacity;
    double time;
    double maxCost;
    double minCapacity;
    double maxTime;
};


Problem loadData(const std::string& filename, double& bestKnownSol);

void initializeHeep(Solution& s, const Problem& p);
void updateHeep(Solution& s,const Problem& p, int& in, int& out);
int findSecondMin(Solution& s,int& cityIndex);
int bruteSecondMin(Solution& s, int& cityIndex, const Problem& p);

void initializeIdCriticalAndFOpt(Solution& s, const Problem& p);
bool isSiteCritical(int site, const Solution& s);
//void updateSolutionInfo(const Problem& p, Solution& s);
//DistanceAndCriticalCount calcMinDistanceAfterChange(const std::vector<int>& removedIndices, const std::vector<int>& addedIndices, const Solution& s, const Problem& p);
//void updateTempMinDistanceAndCriticalCount(double newDist, double& minDistance, int& criticalCount);
//double calcChangedDistanceForOneSite(int idx, const std::vector<int>& removedIndices, const std::vector<int>& removedSites, const std::vector<int>& addedIndices, const Solution& s, const Problem& p);
//bool isSolutionFeasibleAfterChange(const std::vector<int>& removedIndices, const std::vector<int>& addedIndices, const Solution& s, const Problem& p);

std::vector<int> getIncludedSitesForOutput(const Solution& s);

void fillResultInfo(Result& result, const Solution& bestSol, const Problem& p, int timeMax, const std::vector<int>& nRuns, const std::vector<int>& nImps);
Result getNonFeasibleSolutionResult();
void writeResultToCSV(const Result& res, std::ofstream& output, const std::string& instanceName);
void writeCSVHeader(std::ofstream& output);
void writeResultToFile(const Result& result, std::ofstream& output);


#endif
