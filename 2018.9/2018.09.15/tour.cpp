#include<bits/stdc++.h>
#define N 20005
int n,m,A[N],f[12][60000],ecnt,head[N],vis[N],deep[N],ans=0;
int po[12];
struct edge
{
	int v,next;
}e[N<<2];
void add(int u,int v)
{
	e[++ecnt]={v,head[u]};head[u]=ecnt;
}
int getbit(int S,int k){return (S/po[k])%3;}
void dfs(int u,int dep)
{
	vis[u]=1,deep[u]=dep;
	for(int s=0;s<po[dep+1];s++) f[dep][s]=1e9;	
	if(dep==0) f[0][0]=A[u],f[0][1]=0;
	else 
		for(int s=0;s<po[dep];s++)
		{
			int up=po[dep],t=s;
			for(int i=head[u];i;i=e[i].next)
				if(vis[e[i].v] && deep[e[i].v]<dep)
					if(getbit(s,deep[e[i].v])==0) up=po[dep]<<1;//to 2 fal to 1
					else if(getbit(s,deep[e[i].v])==1) t+=po[deep[e[i].v]];//mst_choes
			f[dep][t]=std::min(f[dep][t],f[dep-1][s]+A[u]);
			if(getbit(s,dep)==0) f[dep][s+up]=std::min(f[dep][s+up],f[dep-1][s]);
		}
	for(int i=head[u];i;i=e[i].next)
		if(!vis[e[i].v])
		{
			dfs(e[i].v,dep+1);
			for(int s=0;s<po[dep+1];s++)
				f[dep][s]=std::min(f[dep+1][s],f[dep+1][s+(po[dep+1]<<1)]);
				//0-->2(satfy) 1-->0(dep+2,cho), 2-->1(dep+2, permit)
		}
}
int main()
{
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);
	po[0]=1;for(int i=1;i<=10;i++) po[i]=po[i-1]*3;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	for(int i=1;i<=n;i++) 
		if(!vis[i]) dfs(i,0),ans+=std::min(f[0][0],f[0][2]);
	printf("%d\n",ans);
	return 0;
}
/*
everybit:
0 choose 
1 unchoose and not legal 
2 unchoose but legal
*/
/*
10 10
9 8 7 8 9 6 5 4 5 6
1 2 
2 3
3 4
3 7
4 5
5 6
6 7
7 8
8 9
9 10
*/

