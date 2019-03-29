// HXH orz
#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<cmath>
#define MAXN 1010
using namespace std;
int n,q,cnt,rev[MAXN],dp[MAXN][2],ans,fa[MAXN],dep[MAXN];
struct node
{
	int v,w;
	node *next;
}pool[2*MAXN],*h[MAXN];
void addedge(int u,int v,int w,int id)
{
	node *p=&pool[++cnt];rev[id]=cnt;
	p->v=v;p->w=w;p->next=h[u];h[u]=p;
	p=&pool[++cnt];
	p->v=u;p->w=w;p->next=h[v];h[v]=p;
}
void dfs(int u,int ff)
{
	for(node *p=h[u];p;p=p->next)
	{
		int v=p->v;
		if(v==ff) continue;
		fa[v]=u;dep[v]=p->w;dfs(v,u);
		if(p->w==1)
		{
			dp[u][0]+=dp[v][0];
			dp[u][1]+=dp[v][1];
		}
		if(p->w==2) dp[u][1]+=dp[v][1];
		if(p->w==3) dp[u][0]+=dp[v][1];
	}
	dp[u][1]++;
}
bool check(int s,int t)
{
	int u=t,type=1,flag=1;
	while(u!=s)
	{
		if(dep[u]==3)
		{
			if(type==1) type=0;
			else 
			{
				flag=0;
				break;
			}
		}
		if(dep[u]==2)
		{
			if(type==0)
			{
				flag=0;
				break;
			}
		}
		u=fa[u];
	}
	return flag;
}
int main()
{
    scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++)
	    {
	    	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	    	addedge(u,v,w,i);
		}
	while(q--)
	{
		int x,w,s,t;scanf("%d%d%d%d",&x,&w,&s,&t);
		x^=ans;w^=ans;s^=ans;t^=ans;
		pool[rev[x]].w=w;pool[rev[x]+1].w=w;
		memset(dp,0,sizeof(dp));
		memset(fa,0,sizeof(fa));
		memset(dep,0,sizeof(dep));
		dfs(s,s);
		printf("%d %d\n",ans=dp[s][0]+dp[s][1],check(s,t));
	}
    return 0;
}
/*
6 10 
1 6 3 
1 3 3 
6 5 3 
5 2 3 
2 4 2 
3 1 3 1 
1 0 0 3
1 5 1 6 
6 5 7 7 
1 7 7 6 
5 5 5 6 
7 5 6 2 
3 7 0 4 
4 5 7 0 
5 5 4 3
*/

