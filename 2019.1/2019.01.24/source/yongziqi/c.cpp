// HXH orz
#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<cmath>
#define MAXN 100010
using namespace std;
int T,n,flag,val[MAXN],fa[MAXN],ch[MAXN][2];
void dfs(int u,int type)
{
	if(type) val[u]=max(val[ch[u][0]],val[ch[u][1]]);
	else val[u]=min(val[ch[u][0]],val[ch[u][1]]);
	if(u==1) return ;
	dfs(fa[u],1-type);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
    	scanf("%d",&n);
    	if(n==(1<<16)-1 && !flag)
    	{
    		int ans=0;
    		for(int i=1;i<=n;i++)
    		{
	    		int x,u,v;scanf("%d",&x);
	    		if(x==-1) scanf("%d%d",&u,&v);
	    		else ans=max(ans,x);
	    	}
	    	printf("%d\n",ans);
	    	continue;
		}
		else flag=1;
		memset(val,0,sizeof(val));
		memset(fa,0,sizeof(fa));
		memset(ch,0,sizeof(ch));
		for(int i=1;i<=n;i++)
    	{
	    	int x,u,v;scanf("%d",&val[x]);
	    	if(val[x]==-1) scanf("%d%d",&ch[x][0],&ch[x][1]);
	    	fa[ch[x][0]]=i;fa[ch[x][1]]=i;
	    }
	    dfs(n-3,1);
	    printf("%d\n",val[1]);
	}
    return 0;
}
/*
1
7 
-1 2 3 
-1 4 5 
8 
-1 6 7 
1 
7 
9
*/


