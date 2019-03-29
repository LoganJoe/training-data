#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define fo(i,a,b) for(int i=a;i<=b;++i)
#define fod(i,a,b) for(int i=a;i>=b;--i)
#define N 300005
using namespace std;
int pr[N],t[N][2],n,m,tc;
void dfs(int k)
{
	if(t[k][0]) 
	{
		dfs(t[k][0]),dfs(t[k][1]);
		if(tc%2==0) pr[k]=max(pr[t[k][0]],pr[t[k][1]]);
		else pr[k]=min(pr[t[k][0]],pr[t[k][1]]);
		tc++;
	}
}
int main()
{
//	freopen("c.in","r",stdin);
	//freopen("c.out","w",stdout);
	int t1;
	cin>>t1;
	while(t1--)
	{
		scanf("%d",&n);
		memset(pr,0,sizeof(pr));
		memset(t,0,sizeof(t));
		fo(i,1,n) 
		{
			int p;
			scanf("%d",&p);
			if(p<0) scanf("%d%d",&t[i][0],&t[i][1]);
			else pr[i]=p;
		}
		tc=0;
		dfs(1);
		printf("%d\n",pr[1]);
	}
}