#include "rank.hpp"
using namespace std;
vector<int> work(int n)
{
	char c=ask(0,1);
	vector<int> v;
	for(int i=0;i<n;++i)
		v.push_back(i-1);
	return v;
}
