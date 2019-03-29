#include<bits/stdc++.h>
#define N 100005
int n,K,m,S,mark[N],dis[N];
class Fath_set
{
public:
	int f[N];
	int find(int x){return f[x]==x?f[x]:f[x]=find(f[x]);}
}F[2];
std::queue<int>q;
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%d%d%d%d",&n,&K,&m,&S);
	for(int i=1,x;i<=m;i++) scanf("%d",&x),mark[x]=1;
	for(int i=1;i<=n;i++) F[0].f[i]=F[1].f[i]=i,dis[i]=-1;
	dis[S]=0;q.push(S);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		if(mark[x]) continue;
		for(int i=x+2+((K&1)?0:-1);i<x+K && i>0 && i<=n;i=F[1].find(i+2))
			{
			//	printf("%d %d\n",x,i);
				if((i+x)/2+K/2>n || (i+x+1)/2-K/2<1) break;
				if(dis[i]==-1 && !mark[i])
					dis[i]=dis[x]+1,q.push(i);
				if(i==x+K-1 || i+2>n) break;
				F[1].f[i]=i+2;
			}
		for(int i=x-2-((K&1)?0:-1);i>x-K && i>0 && i<=n;i=F[0].find(i-2))
			{
			//	printf("%d %d\n",x,i);
				if((i+x)/2+K/2>n || (i+x+1)/2-K/2<1) break;
				if(dis[i]==-1 && !mark[i])
					dis[i]=dis[x]+1,q.push(i);
				if(i==x-K+1 || i-2<0) break;
				F[0].f[i]=i-2;
			}
	}
	printf("%d",dis[1]);for(int i=2;i<=n;i++) printf(" %d",dis[i]);
	puts("");
	return 0;
}
