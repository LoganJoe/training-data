#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<ctime>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\n"
int n,a,fa[N];
std::map<int,int>mp[N];
int rd(int x) {return (rand()^(rand()<<15))%x;}
int main()
{
	srand(time(0));
	freopen("magic.in","w",stdout);
	n=rd(3000)+2000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++) a=rd(i),fa[i]=a,printf("%d ",a);puts("");
	for(int i=1;i<=n;i++)
	{
		a=rd(n)+1;
		while(mp[fa[i]][a]) a=rd(n)+1;
		mp[fa[i]][a]=1;
		printf("%d ",a);puts("");
	}
	return 0;
}

