#include "algorithm.hpp"
#include <iostream>
#include <algorithm>

Result Algorithm::execute()
{
    startTime = std::chrono::steady_clock::now();
    return VNS();
}

int Algorithm::getRunningTime() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
}

bool Algorithm::createGreedySolution(Solution& s)
{
	s.p = problem.p;
	s.c1.resize(problem.n);
	s.c2.resize(problem.n);
	s.inSol.resize(problem.n);
	s.criticalUsers.resize(problem.n);
	s.isCritical.resize(problem.n);

	//------------------------------------------------------------------------------------

	int firstCity = 0;
	double sol = std::numeric_limits<double>::max();

	for (int i = 0;i < problem.n;i++)
	{	
		double maxRad = 0;
		
		for (int j = 0;j < problem.n;j++)
		{
			if (j != i) maxRad = std::max(maxRad, problem.d[i][j]);
		}

		if (sol > maxRad)
		{
			sol = maxRad;
			firstCity = i;
		}
	}


	s.x_opt.push_back(firstCity);
	s.inSol[firstCity] = true;
	for (int i = 0;i < problem.n;i++)
	{
		s.c1[i] = firstCity;
		s.c2[i] = i;
	}

	for (int i = 0;i < (problem.p - 1);i++)
	{
		double maxRad = 0;
		
		//sledeci grad u kojem se postavlja fabrika je onaj koji je najudaljeniji od trenutnih fabrika 
		int nextCity = 0;

		for (int j = 0;j < problem.n;j++)
		{
			if (s.inSol[j] == false && maxRad < problem.d[j][s.c1[j]])
			{
				maxRad = problem.d[j][s.c1[j]];
				nextCity = j;
			}
		}

		s.x_opt.push_back(nextCity);
		s.inSol[nextCity] = true;

		for (int j = 0;j < problem.n;j++)
		{
			if (problem.d[j][s.c1[j]] > problem.d[j][nextCity] && nextCity!=j)
			{
				s.c2[j] = s.c1[j];
				s.c1[j] = nextCity;
			}
			else if (problem.d[j][s.c2[j]] > problem.d[j][nextCity] && nextCity != j) s.c2[j] = nextCity;
		}
	}


	for (int i = 0;i < problem.n;i++)
	{
		if (s.inSol[i] == false) s.x_opt.push_back(i);
	}

	initializeIdCriticalAndFOpt(s, problem);

	initializeHeep(s, problem);

	return true;
}
 
int Algorithm::Move(Solution& s,double& f, int& in, int& newCritCnt)
{
	newCritCnt = std::numeric_limits<int>::max();

	int critUsersPrim = 0;
	int critUsersR1 = 0;
	int critUsersR2 = 0;

	std::vector<int> critUsersNum;
	critUsersNum.resize(problem.n);

	// x_opt oznacava trenutni vektor centara

	// f_prim oznacava radijus seta korisnika za koje je novoubaceni centar in optimalan
	double f_prim = 0;

	// r[i] oznacava radijus grupe korisnika kojima je centar i najblizi, kada taj centar ne bi bio izbacen
	std::vector<double> r;
	for (int i = 0;i < problem.n;i++) r.push_back(0);
	

	// z[i] oznacava radijus grupe korisnika kojima je centar i bio najblizi, ukoliko se on izbaci
	std::vector<double> z;
	std::vector<int> critUsersZ;
	for (int i = 0;i < problem.n;i++)
	{
		z.push_back(0);
		critUsersZ.push_back(0);
	}


	// c1[i] centar koji je najblizi korisniku i
	// c2[i] drugi najblizi centar korisniku i
	// d[i][j] vektor rastojanja izmedju korisnika i i centra j
	// u ovoj for petlji se racunaju f_prim, r i z

	for (int i = 0;i < problem.n;i++)
	{
		if (problem.d[i][in] < problem.d[i][s.c1[i]]) f_prim = std::max(f_prim, problem.d[i][in]);
		else
		{
			r[s.c1[i]] = std::max(r[s.c1[i]], problem.d[i][s.c1[i]]);

			z[s.c1[i]] = std::max(z[s.c1[i]], std::min(problem.d[i][in], problem.d[i][s.c2[i]]));
		}
	}


	// g1, g2 su redom prvi i drugi maksimum funkcije r[i]
	double g1 = 0;
	double g2 = 0;

	// id1, id2 su redom indeksi prvog i drugog maksimuma fje r[s.x_opt[i]]
	int id1 = 0;
	int id2 = 0;

	for (int i = 0;i < s.p;i++)
	{
		if (r[s.x_opt[i]] >= g1)
		{
			g2 = g1;
			g1 = r[s.x_opt[i]];

			id2 = id1;
			id1 = i;
		}
		else
		{
			if (r[s.x_opt[i]] > g2)
			{
				g2 = r[s.x_opt[i]];
				id2 = i;
			}
		}
	}


	//----------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------
	
	for (int i = 0;i < problem.n;i++)
	{
		if (problem.d[i][in] < problem.d[i][s.c1[i]])
		{
			if (f_prim == problem.d[i][in]) critUsersPrim++;
		}
		else
		{
			if (g1 == problem.d[i][s.c1[i]]) critUsersR1++;
			else if (g2 == problem.d[i][s.c1[i]]) critUsersR2++;

			if (z[s.c1[i]] == std::min(problem.d[i][in], problem.d[i][s.c2[i]])) critUsersZ[s.c1[i]]++;
		}
	}
	int CritUsersTmp1 = 0, CritUsersTmp2 = 0;
	double currSol1, currSol2;

	currSol1 = std::max(f_prim, g1);
	currSol2 = std::max(f_prim, g2);

	if (g1 == g2) critUsersR2 = critUsersR1 - 1;

	if (f_prim == g1) CritUsersTmp1 = critUsersR1 + critUsersPrim;
	else if (f_prim > g1) CritUsersTmp1 = critUsersPrim;
	else CritUsersTmp1 = critUsersR1;

	if (f_prim == g2) CritUsersTmp2 = critUsersR2 + critUsersPrim;
	else if (f_prim > g2) CritUsersTmp2 = critUsersPrim;
	else CritUsersTmp2 = critUsersR2;

	for (int i = 0;i < problem.p;i++)
	{
		if (i != id1)
		{
			if (z[s.x_opt[i]] == currSol1) critUsersNum[i] = CritUsersTmp1 + critUsersZ[s.x_opt[i]];
			else if (z[s.x_opt[i]] > currSol1) critUsersNum[i] = critUsersZ[s.x_opt[i]];
			else critUsersNum[i] = CritUsersTmp1;
		}
		else
		{
			if (z[s.x_opt[i]] == currSol2) critUsersNum[i] = CritUsersTmp2 + critUsersZ[s.x_opt[i]];
			else if (z[s.x_opt[i]] > currSol2) critUsersNum[i] = critUsersZ[s.x_opt[i]];
			else critUsersNum[i] = CritUsersTmp2;
		}
	}

	//----------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------


	// g[i] oznacava vrednost maksimalnog radijusa f ako bi se izbacio centar x_opt[i]
	std::vector<double> g(problem.p, 0);
	for (int i = 0;i < s.p;i++)
	{
		if (i != id1) g[i] = std::max(f_prim, std::max(z[s.x_opt[i]], g1));
		else
		{
			g[i] = std::max(f_prim, std::max(z[s.x_opt[i]], g2));
		}
	}


	// out predstavlja indeks koji izbacujemo da bi postigli minimalnu vrednost funkcije f
	f = g[0];
	int id_out = 0;

	for (int i = 0;i < s.p;i++)
	{
		if (f > g[i])
		{
			f = g[i];

			newCritCnt = critUsersNum[i];

			id_out = i;
		}
		else if ((f == g[i]) && (critUsersNum[i] < newCritCnt))
		{
			newCritCnt = critUsersNum[i];

			id_out = i;
		}
	}
	
	return id_out;
}

void Algorithm::Update(Solution& s, int& goin, int& goout)
{
	updateHeep(s, problem, goin, goout);

	double f_tmp = std::numeric_limits<double>::min();

	for (int i = 0;i < problem.n;i++)
	{
		if (s.c1[i] == goout)
		{
			if (problem.d[i][goin] <= problem.d[i][s.c2[i]]) s.c1[i] = goin;
			else
			{
				s.c1[i] = s.c2[i];

				//ovde preko heepa nadjemo drugi po redu minimum za novu vrednost c2
				s.c2[i] = findSecondMin(s, i);

			}
		}
		else
		{
			if (problem.d[i][goin] < problem.d[i][s.c1[i]])
			{
				s.c2[i] = s.c1[i];
				s.c1[i] = goin;
			}
			else
			{
				if (problem.d[i][goin] < problem.d[i][s.c2[i]]) s.c2[i] = goin;
				else
				{
					//ovde preko heepa nadjemo drugi po redu minimum za novu vrednost c2
					if (s.c2[i] == goout) s.c2[i] = findSecondMin(s, i);
				}
			}
		}

		/*if (f_tmp < problem.d[i][s.c1[i]])
		{
			f_tmp = problem.d[i][s.c1[i]];

			s.id_crit = i;
		}*/
	}

	initializeIdCriticalAndFOpt(s, problem);
}

void Algorithm::localSearchSwap(Solution& s, bool& hasImproved)
{
	hasImproved = false;

	double f_new = std::numeric_limits<double>::max();
	double f;
	int id_in_new,id_out_new;
	int oldCriticalNum = s.critUsersNum;
	int newCritCnt;
	int critCnt= std::numeric_limits<int>::max();
	bool better = false;

	for (int i = problem.p;i < problem.n;i++)
	{
		int in = s.x_opt[i];
		int in_id = i;

		//for (int j = 0;j < s.critUsersNum;j++)
		//{
		//	int CritUser = s.criticalUsers[j];

			if (problem.d[s.id_crit][in] < problem.d[s.id_crit][s.c1[s.id_crit]])
			{
				int out_id = Move(s, f, in, newCritCnt);

				if (f < f_new || (f==f_new && critCnt<newCritCnt))
				{
					f_new = f;
					id_in_new = in_id;
					id_out_new = out_id;
					critCnt = newCritCnt;
				}
			}
		//}
		
	}

	if (f_new < s.f_opt)
	{
		hasImproved = true;

		//novo f_opt = f 
		s.f_opt = f_new;

		// Updejtovanje za c1 i c2 i id_crit
		Update(s, s.x_opt[id_in_new], s.x_opt[id_out_new]);

	    // u x_opt leti x_opt[out_sol] a upada x_opt[in_sol]
		std::swap(s.x_opt[id_out_new], s.x_opt[id_in_new]);
	}
	else if ((f_new == s.f_opt) && (critCnt<oldCriticalNum))
	{
		//std::cout << "Ovde sam:  " << critCnt << " , " << oldCriticalNum << std::endl;
		better = true;

		hasImproved = true;

		s.f_opt = f_new;

		// Updejtovanje za c1 i c2 i id_crit
		Update(s, s.x_opt[id_in_new], s.x_opt[id_out_new]);

		// u x_opt leti x_opt[out_sol] a upada x_opt[in_sol]
		std::swap(s.x_opt[id_out_new], s.x_opt[id_in_new]);
	}
	//std::cout << critCnt << std::endl;
	//if (better) std::cout << "Problematika problema: " << critCnt << " , " << s.critCentersNum << std::endl;
}

bool Algorithm::BruteSolutionCheck(Solution& s)
{
	int cnt = 0;
	for (int i = 0;i < problem.n;i++)
	{
		double mx1 = std::numeric_limits<double>::max();
		double mx2 = std::numeric_limits<double>::max();
		int id1 = 0, id2 = 0;

		for (int k = 0;k < problem.p;k++)
		{
			int j = s.x_opt[k];

			if (problem.d[i][j] < mx1 && i != j)
			{
				mx2 = mx1;
				mx1 = problem.d[i][j];

				id2 = id1;
				id1 = j;
			}
			else if (problem.d[i][j] < mx2 && i != j) { mx2 = problem.d[i][j]; id2 = j; }
		}

		if ( (fabs(problem.d[i][s.c1[i]] - problem.d[i][id1])>0.0001) || (fabs(problem.d[i][s.c2[i]] - problem.d[i][id2]) > 0.0001))
		{
			std::cout << problem.d[i][s.c1[i]] << "=" << problem.d[i][id1] << " , " << problem.d[i][s.c2[i]] << "=" << problem.d[i][id2] << std::endl;
			cnt++;
		}

	}

	std::cout << cnt << std::endl;

	if (cnt > 0) return false;
	else return true;
}


Result Algorithm::VNS()
{
	Solution bestSol;
	createGreedySolution(bestSol);

	while (getRunningTime() < timeMax)
	{
		int k = 1;
		int kmax = problem.p;

		while (k < kmax && getRunningTime() < timeMax)
		{

			Solution newSol = bestSol;

			for (int j = 0;j < k;j++)
			{
				std::uniform_int_distribution<int> distribIn(newSol.p, problem.n - 1);
				std::uniform_int_distribution<int> distribOut(0, newSol.p - 1);

				int in_id = distribIn(generator);

				int in = newSol.x_opt[in_id];
				int out_id;

				//if (problem.d[newSol.id_crit][in] < newSol.f_opt)
				//{
					out_id = distribOut(generator);

					int out = newSol.x_opt[out_id];

					Update(newSol, in, out);

					std::swap(newSol.x_opt[out_id], newSol.x_opt[in_id]);

					//newSol.f_opt = problem.d[newSol.id_crit][newSol.c1[newSol.id_crit]];
					
					//newSol.f_opt = problem.d[newSol.criticalUsers[0]][newSol.c1[newSol.criticalUsers[0]]];
				//}

				//if (BruteSolutionCheck(newSol) == false) std::cout << "Problematic : " << j << std::endl;
				//if (CheckAgain(newSol) == false) std::cout << "Problematic : " << j << std::endl;
			}

			bool hasImproved=true;

			while (hasImproved)
			{
				localSearchSwap(newSol, hasImproved);
			}

			if ((newSol.f_opt < bestSol.f_opt) || (newSol.f_opt == bestSol.f_opt && newSol.critUsersNum > bestSol.critUsersNum))
			{
				std::cout << newSol.f_opt << std::endl;

				bestSol = newSol;
				k = 1;
			}
			else
			{
				newSol = bestSol;
				k = k + 1;
			}
		}
	}
	
	Result r;

	r.s = bestSol;
	r.includedSites = bestSol.x_opt;
	r.minDistance = bestSol.f_opt;

	return r;
}

bool Algorithm::CheckAgain(Solution& s)
{
	for (int i = 0;i < problem.p;i++)
	{
		if (s.inSol[s.x_opt[i]] == false) { std::cout << i << std::endl; return false; }
	}

	for (int i = problem.p;i < problem.n;i++)
	{
		if (s.inSol[s.x_opt[i]] == true) { std::cout << i << std::endl; return false; }
	}

	return true;
}
