#include<bits/stdc++.h>
#define N 2005
#define M 200005
int h,w,n,m,A[N][N],id[N][N],p[N],vis[N][N];

char mp[N][N];
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
struct node
{
	int x,y,id,dis;
	friend bool operator <(node t1, node t2){return t1.dis>t2.dis;}
};
bool check(int x,int y)
{
	if(x<1 || x>h || y<1 || y>w || A[x][y]==-1 /*|| vis[x][y]*/) return 0;
	return 1;
}
int head[M],ecnt,pcnt;
struct edge
{
	int v,w,next;
}e[M<<2];
void add(int u,int v,int w)
{
	e[++ecnt]={v,w,head[u]};head[u]=ecnt;
	e[++ecnt]={u,w,head[v]};head[v]=ecnt;
}
struct info
{
	int u,v,w;
	friend bool operator <(info t1,info t2)
	{
		return t1.w<t2.w;
	}
}ft[M<<2];
void bfs(int id)
{
	std::priority_queue<node>q;
	q.push({(p[id]-1)/w+1,(p[id]-1)%w+1,id,0});
	while(!q.empty())
	{
		node u=q.top();q.pop();
		if(vis[u.x][u.y]==u.id) continue;
		vis[u.x][u.y]=u.id;
		for(int k=0;k<4;k++)
		{
			node v={u.x+dx[k],u.y+dy[k],u.id,u.dis+1};
			if(!check(v.x,v.y)) continue;
			if(vis[v.x][v.y]==u.id) continue;
			if(A[v.x][v.y]>0) 
			{
				//add(u.id,A[v.x][v.y],u.dis);
				//v.id=A[v.x][v.y],v.dis=0;
				if(u.id<A[v.x][v.y]) ft[++pcnt]={u.id,A[v.x][v.y],u.dis};
				q.push(v);
			}
			else
				q.push(v);
		}
	}
}
int f[M];
int find(int x){return f[x]==x?f[x]:f[x]=find(f[x]);}
void kruscal()
{
	std::sort(ft+1,ft+1+pcnt);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=pcnt;i++)
	{
		int fx=find(ft[i].u),fy=find(ft[i].v);
		if(fx==fy) continue;
		f[fx]=fy,add(ft[i].u,ft[i].v,ft[i].w);
	}
}
int fa[M][20],deep[N],val[N][20],LCA;
void dfs(int u,int fath)
{
	deep[u]=deep[fath]+1;
	for(int i=head[u];i;i=e[i].next)
		if(e[i].v!=fath) 
			fa[e[i].v][0]=u,val[e[i].v][0]=e[i].w,dfs(e[i].v,u);
}
void process ()
{
	for(int i=1;i<=n;i++)bfs(i);
	kruscal();
	for(int i=1;i<=n;i++) if(!deep[i]) dfs(i,0);
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1],val[i][j]=std::max(val[i][j-1], val[fa[i][j-1]][j-1]);
}
int FuckJyc (int u, int v)
{
	int res=0;
	if(deep[u]<deep[v]) std::swap (u,v);
	for(int i=19;~i;i--)
		if(deep[fa[u][i]]>=deep[v]) res=std::max(res,val[u][i]),u=fa[u][i];
	LCA=u;
	if(u==v) return res;
	for(int i=19;~i;i--) 
		if(fa[u][i]!=fa[v][i]) 
			res=std::max(res,std::max(val[u][i],val[v][i])),u=fa[u][i],v=fa[v][i];
	res=std::max (res,std::max(val[u][0],val[v][0]));LCA=fa[u][0];
	if(fa[u][0]!=fa[v][0] || fa[u][0]==0) return -1;
	return res;
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d%d%d%d",&h,&w,&n,&m);
	for(int i=1;i<=h;i++)
	{
		scanf("%s",mp[i]+1);
		for(int j=1;j<=w;j++)
		{
			if(mp[i][j]=='#') A[i][j]=-1;
			id[i][j]=(i-1)*w+j;
		}
	}
	for(int i=1,x,y;i<=n;i++) 
		scanf("%d%d",&x,&y),A[x][y]=i,p[i]=id[x][y];
	process();

	while(m--)
	{
		int a,b;scanf("%d%d",&a,&b);
		printf("%d\n",FuckJyc(a,b));
	}
	//printf("%d\n",ecnt);
}
