#include<bits/stdc++.h>
#define N 1005
#define M 100005
#define ull unsigned long long
int n,m,q,head[N],cnt,fa[N],fb[N],dis[N];
std::map<ull,int> mp;
struct node
{
	int u,v,w,mark,id,del;
}s[M];
bool cmp(node t1,node t2){return t1.w<t2.w;}
struct edge
{
	int v,w,id,del;
};
std::vector<edge>e[N];
void add(int u,int v,int w)
{
	e[u].push_back({v,w,cnt,0});
}
int f[N];
int find(int x){return f[x]==x?f[x]:find(f[x]);}
void Kruscal()
{
	std::sort(s+1,s+1+m,cmp);
	for(int i=1;i<=n;i++)
	{
		mp[s[i].u*n+s[i].v]=mp[s[i].v*n+s[i].u]=i;
	}
	for(int i=1;i<=m;i++)
	{
		int fx=find(s[i].u),fy=find(s[i].v);
		if(fx==fy) continue;
		fa[i]=fx,fb[i]=fy;
		f[fx]=fy,s[i].mark=++cnt;
		add(s[i].u,s[i].v,s[i].w);
		add(s[i].v,s[i].u,s[i].w);
	}
}
void dfs(int u,int fa=0)
{
	for(edge to:e[u])
	{
		if(to.v==fa || to.del) continue;
		dis[to.v]=std::max(dis[u],to.w);
		dfs(to.v,u);
	}
}
int main()
{
	freopen("pipe.in","r",stdin);
	freopen("pipe.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&s[i].u,&s[i].v,&s[i].w);s[i].id=i;
	}
	for(int i=1;i<=n;i++) f[i]=i;
	Kruscal();
	while(q--)
	{
		int opt,a,b;scanf("%d%d%d",&opt,&a,&b);
		if(opt==1)
		{
			dis[a]=0;
			dfs(a);
			printf("%d\n",dis[b]);
		}
		else
		{
			int id=mp[a*n+b];
			s[id].del=1;
			if(!s[id].mark) continue;
			for(int i=0;i<e[a].size();i++) if(e[a][i].v==b) e[a][i].del=1;
			for(int i=0;i<e[b].size();i++) if(e[b][i].v==a) e[b][i].del=1;
			f[fa[id]]=fa[id];
			for(int i=1;i<=m;i++)
			{
				if(s[i].del) continue;
				int fx=find(s[i].u),fy=find(s[i].v);
				if(fx==fy) continue;
				f[fx]=fy,s[i].mark=1;(s[i].u,s[i].v,s[i].w);
				add(s[i].u,s[i].v,s[i].w);
				add(s[i].v,s[i].u,s[i].w);
				break;
			}
		}
	}
}
