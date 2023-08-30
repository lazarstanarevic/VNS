#include "structures.hpp"
#include <limits>
#include <algorithm>
#include <sstream>
#include <utility>
#include<string>

Problem loadData(const std::string& filename, double& bestKnownSol)
{
	Problem problem;

	std::ifstream input(filename);
	//checkCondition(!!input, "Opening file failed.");

	int n, p;
	std::string word1, word2, word3;

	input >> n >> word1 >> p >> word2 >> bestKnownSol >> word3;
	problem.n = n;
	problem.p = p;
	
	problem.d.resize(n);
	for (int i = 0; i < n; i++)
	{
		problem.d[i].resize(n);
	}

	
	problem.cities.resize(n);
	for (int i = 0;i < n;i++) problem.cities[i] = i;

    
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++) input >> problem.d[i][j];

		problem.d[i][i] = std::numeric_limits<double>::max();
	}

	return problem;
}

void initializeHeep(Solution& s, const Problem& p)
{
	s.pq.resize(p.n);
		
	for (int i = 0;i < p.n;i++)
	{
		for (int j = 0;j < p.p;j++)
		{
			if (i == s.x_opt[j]) continue;

			s.pq[i].push(std::make_pair(-p.d[i][s.x_opt[j]], s.x_opt[j]));
		}
	}
}

void updateHeep(Solution& s,const Problem& p, int& in, int& out)
{
	s.inSol[in] = true;
	s.inSol[out] = false;

	for (int i = 0;i < p.n;i++)
	{
		if (i == in) continue;

		s.pq[i].push(std::make_pair(-p.d[i][in], in));
	}
}

int findSecondMin(Solution& s, int& cityIndex)
{
	int c2_id;
	std::pair<double, int> tmp,ret;
	bool ok=false;

	while (true)
	{
		tmp = s.pq[cityIndex].top();
		int id = tmp.second;

		if (id != s.c1[cityIndex] && s.inSol[id] == true)
		{
			c2_id = id;
			break;
		}

		if (id == s.c1[cityIndex])
		{
			ok = true;
			ret = tmp;
		}

		s.pq[cityIndex].pop();
	}

	if(ok) s.pq[cityIndex].push(ret);

	return c2_id;
}

int bruteSecondMin(Solution& s, int& cityIndex, const Problem& p)
{
	double mx1 = std::numeric_limits<double>::max();
	double mx2 = std::numeric_limits<double>::max();
	int id1 = 0, id2 = 0;

	for (int i = 0;i < p.n;i++)
	{
		//if (i == cityIndex) continue;

		if (s.inSol[i] == true && mx1 >= p.d[cityIndex][i])
		{
			mx2 = mx1;
			mx1 = p.d[cityIndex][i];

			id2 = id1;
			id1 = i;
		}
		else if (s.inSol[i] == true && mx2 >= p.d[cityIndex][i])
		{
			mx2= p.d[cityIndex][i];

			id2 = i;
		}
	}

	return id2;
}

void initializeIdCriticalAndFOpt(Solution& s, const Problem& p)
{
	s.f_opt = 0;

	for (int i = 0;i < p.n;i++)
	{
		s.isCritical[i] = false;
		s.f_opt = std::max(s.f_opt, p.d[i][s.c1[i]]);
	}
	/*{
		if (s.f_opt < p.d[i][s.c1[i]])
		{
			s.f_opt = p.d[i][s.c1[i]];
			s.id_crit = i;
		}
	}*/
	
	s.critUsersNum = 0;
	for (int i = 0;i < p.n;i++)
	{
		if (s.f_opt == p.d[i][s.c1[i]])
		{
			s.critUsersNum++;
			s.id_crit = i;
		}

		//if (s.f_opt == p.d[i][s.c1[i]] && s.isCritical[s.c1[i]] == false)
		//{
		//	s.isCritical[s.c1[i]] = true;
			
		//	s.criticalUsers[s.critCentersNum] = i;
		//}
	}
}

bool isSiteCritical(int site, const Solution& s)
{
	return (site == s.c1[s.id_crit]);
}
