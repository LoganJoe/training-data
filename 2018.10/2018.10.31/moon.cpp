 #include<bits/stdc++.h>
#define N 50005
int Case,n,m,k,A[N],s[N],head[N],ecnt,ans=1e9;
char ch[N];
int flag[10],b[10];
int dis[N][20],an[N][20];
struct edge
{
	int v,next;
}e[N*10];
void add(int u,int v){e[++ecnt]={v,head[u]};head[u]=ecnt;}
struct node{int x,S;};
void bfs(int st)
{
	for(int i=1;i<=n;i++)
		for(int j=0;j<=1<<4;j++) dis[i][j]=1e9;
	dis[s[st]][1<<(A[s[st]]-1)]=0;
	std::queue<node>q;q.push({s[st],1<<(A[s[st]]-1)});
	while(!q.empty())
	{
		node u=q.front(),id;q.pop();
		for(int i=head[u.x];i;i=e[i].next)
		{
			int v=e[i].v;
			int t=1<<(A[v]-1);
			if(dis[u.x][u.S]%4==3)
			{
				if(dis[v][t]>dis[u.x][u.S]+1) 
					dis[v][t]=dis[u.x][u.S]+1,q.push({v,t});
			}
			else
			{
				if(!(u.S&t) && dis[v][t|u.S]>dis[u.x][u.S]+1)
					dis[v][t|u.S]=dis[u.x][u.S]+1,q.push({v,t|u.S});
			}
		}	
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=1<<4;j++) an[st][i]=std::min(an[st][i],dis[i][j]);
}
int main()
{
	freopen("moon.in","r",stdin);
	freopen("moon.out","w",stdout);
	scanf("%d",&Case);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++) scanf("%d",&s[i]);
	scanf("%s",ch+1);
	for(int i=1;i<=n;i++)
	{
		if(ch[i]=='R') A[i]=1;
		if(ch[i]=='G') A[i]=2;
		if(ch[i]=='Y') A[i]=3;
		if(ch[i]=='B') A[i]=4;
	}
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++) an[i][j]=1e9;
	for(int i=1;i<=k;i++) bfs(i);
	for(int i=1;i<=n;i++)
	{
		int res=0;
		for(int j=1;j<=k;j++) res=std::max(res,an[j][i]);
		ans=std::min(ans,res);
	}
	if(ans==1e9) puts("-1");
	else printf("%d\n",ans);
}
/*
1
7 10
4 7 1 3 4
RGRRBYG
1 2 
2 3
2 4
3 4
2 5
5 6
3 6
1 7
7 4
1 5

*/
