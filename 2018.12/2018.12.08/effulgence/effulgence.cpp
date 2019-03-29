// effulgence.cpp
#include "effulgence.h"
#include "grader.cpp"
#include<bits/stdc++.h>
#define N 1005
std::vector<int>e1[N],e2[N];
int deg1[N],deg2[N];
bool QuarrelOrNot(int n, std::vector<int> lyra_set, std::vector<int> evan_set) 
{
	if(lyra_set.size()+evan_set.size()>n) return true;
	while(1)
	{
		std::pair<int,int> E = GetNextFlightFromLyra();
		if(E.first == 0 && E.second == 0) break;
		e1[E.first].push_back (E.second);
		e1[E.second].push_back (E.first);
		deg1[E.first] ++, deg1[E.second] ++;
	}
	while(1)
	{
		std::pair<int,int> E = GetNextFlightFromEvan();
		if(E.first == 0 && E.second == 0) break;
		e2[E.first].push_back (E.second);
		e2[E.second].push_back (E.first);
		deg2[E.first] ++, deg2[E.second] ++;
	}
	int Limit = 10, cnt = 0;
	if(n <= 100 && n > 15) Limit = 50;
	srand(1882334);
	std::random_shuffle(lyra_set.begin(),lyra_set.end());
	for(auto p:lyra_set)
	{
		if(Limit == cnt) break;
		if(n - deg1[p] <= evan_set.size()) continue;
		int To = FromLyraToEvan(p);
		for(auto v:evan_set) if(v == To) return true;
		cnt ++;
	}
	if(Limit > cnt) return false;
	return true;
}
