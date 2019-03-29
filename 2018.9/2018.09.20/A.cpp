#include<bits/stdc++.h>
#define N 100005
int n,m,ans[N],Q,tot1;
struct edge
{
	int t,to,ar,ans;
	friend bool operator <(edge t1,edge t2){return t1.t<t2.t;}
};
struct info
{
	int t,ans;
	friend bool operator <(info t1,info t2){return t1.t<t2.t;}
};
struct node
{
	int st,ans;
	friend bool operator <(node t1,node t2){return t1.ans<t2.ans;}
}A[N];
std::vector<edge> e[N];
std::vector<info> s[N];
int find_s(int x,int v)
{
	int l=0,r=s[x].size()-1,ans=0;
	if(l>r) return 0; 
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(s[x][mid].t<=v) ans=mid,l=mid+1;
		else r=mid-1;
	}	
	return ans;
}
int dfs(int u,int t)
{
	int pos=find_s(u,t);
//	printf("%d %d %d\n",u,t,pos);
	if(s[u][pos].t==t && s[u][pos].ans!=-1) return s[u][pos].ans;
	int res=1e9;
	if(u==n) return t;
	for(int i=0;i<e[u].size();i++)
	{
		if(e[u][i].t<t || e[u][i].to==u) continue;
		if(e[u][i].ans!=1e9) res=std::min(res,e[u][i].ans);
		else res=std::min(res,e[u][i].ans=dfs(e[u][i].to,e[u][i].ar));
	}
	return s[u][pos].ans=res;
}
int find(int x)
{
	int l=1,r=tot1,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(A[mid].ans<=x) ans=mid,l=mid+1;
		else r=mid-1;
	}	
	return ans;
}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b,x,y;
		scanf("%d%d%d%d",&a,&b,&x,&y);
		e[a].push_back({x,b,y,1e9});
		s[b].push_back({y,-1});
	}
	for(int i=1;i<=n;i++)
	{
		std::sort(e[i].begin(),e[i].end());
		std::sort(s[i].begin(),s[i].end());
	}
	tot1=e[1].size();
	for(int i=0;i<tot1;i++)
		A[i+1]={e[1][i].t,dfs(e[1][i].to,e[1][i].ar)};
	std::sort(A+1,A+1+tot1);
	for(int i=1;i<=tot1;i++) ans[i]=std::max(ans[i-1],A[i].st);
	scanf("%d",&Q);
	while(Q--)
	{
		int x;scanf("%d",&x);
		int pos=find(x);
		if(pos>tot1 || A[pos].ans>x || pos==0 || ans[pos]==1e9) puts("-1");
		else printf("%d\n",ans[pos]);
	}
}
