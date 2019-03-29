#include<bits/stdc++.h>
#define N 500005
int n,k,head[N],ecnt,cnt[N],Maxd;
struct edge
{
	int v,next;
}e[N];
void add(int u,int v)
{
	e[++ecnt]={v,head[u]};head[u]=ecnt;
}
void dfs(int u,int dep)
{
	cnt[dep]++,Maxd=std::max(Maxd,dep);
	for(int i=head[u];i;i=e[i].next) dfs(e[i].v,dep+1);
}
int main()
{
	freopen("imagine.in","r",stdin);
	freopen("imagine.out","w",stdout); 
	scanf("%d%d",&n,&k);
	for(int i=2,u;i<=n;i++)scanf("%d",&u),add(u,i);
	dfs(1,0);
	std::sort(cnt+1,cnt+1+Maxd);
	int res=Maxd;
	for(int i=1;i<=Maxd;i++) if(cnt[i]<=k) k-=cnt[i],res--;
	printf("%d\n",res);
}
/*
6 2
1
2
2
2
4
*/
