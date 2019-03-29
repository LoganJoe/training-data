#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
template<class T> inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T> inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}

const int maxn=1005,maxT=1005;

struct dandelion
{
	int s,p,t;
	dandelion(){}
	dandelion(const int &ss,const int &pp,const int &tt):s(ss),p(pp),t(tt){}
}dan[maxn];

int n,T,R,p[maxn],f[maxn][maxn];
bool rem[maxn][maxn];

bool cmp_dan(const int &a,const int &b)
{return dan[a].s<dan[b].s;}

int main()
{
	scanf("%d%d%d",&n,&T,&R);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&dan[i].s,&dan[i].p,&dan[i].t);
		p[i]=i;
	}
	sort(p+1,p+n+1,cmp_dan);
	f[0][0]=R;
	for(int i=1;i<=n;i++)
	{
		for(int t=0;t<=T;t++)
		{
			const dandelion &d=dan[p[i]];
			f[i][t]=f[i-1][t];
			if(t>=d.t&&f[i-1][t-d.t]>=d.s&&rel(f[i][t],f[i-1][t-d.t]+d.p))
				rem[i][t]=1;
		}
	}
	int anst=0;
	for(int t=1;t<=maxT;t++)
		if(f[n][t]>f[n][anst])
			anst=t;
	printf("%d\n",f[n][anst]);
	vector<int> choice;
	
	for(int i=n,t=anst;i>0&&t>0;i--)
		if(rem[i][t])
		{
			choice.push_back(p[i]);
			t-=dan[p[i]].t;
		}
	reverse(choice.begin(), choice.end());
	for(int i=0;i<choice.size();i++)
	{
		printf("%d%c",choice[i]," \n"[i+1==choice.size()]);
	}
	return 0;
}