#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define oo 2139062143
#define fo(i,x,y) for (int i=(x);i<=(y);++i)
using namespace std;
const int N=100100;
int n,m;
int sn[N][2],va[N];
int v[N],bz[N],dep[N],fa[N];
int le,ri,mid,ans;
struct node{
	int x,d,t;
	node(int x_=0,int y_=0,int z_=0)
	{
		x=x_,d=y_,t=z_;
	}
};
bool operator <(node a,node b)
{
	return (a.t>b.t||(a.t==b.t&&a.d>b.d));
}
priority_queue<node> q;
void dfs(int x,int d)
{
	dep[x]=d;
	if(va[x]!=-1) fo(i,0,1) dfs(sn[x][i],d+1);
}
int s;
int check()
{
	while(!q.empty())q.pop();
	fo(i,1,n)
	{
		if(v[i]==-1 && v[sn[i][0]]!=-1 && v[sn[i][1]]!=-1)
			q.push(node(i,dep[i],v[sn[i][0]]==v[sn[i][1]]));
	}
	fo(i,1,s)
	{
		node p=q.top();int x=p.x;q.pop();
		if(i&1) v[x]=max(v[sn[x][0]],v[sn[x][1]]);
		else v[x]=min(v[sn[x][0]],v[sn[x][1]]);
		x=fa[x];
		if(v[x]==-1 && v[sn[x][0]]!=-1 && v[sn[x][1]]!=-1)
			q.push(node(x,dep[x],v[sn[x][0]]==v[sn[x][1]]));
	}
	return v[1];
}
int main()
{
	// freopen("D:/LiuYuanHao/c.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		le=oo,ri=-oo;
		s=(n-1)/2;
		fo(i,1,n) fa[i]=0;
		fo(i,1,n)
		{
			sn[i][0]=sn[i][1]=0;
			int x,y;
			scanf("%d",&x);	
			if(x==-1) 
			{
				scanf("%d%d",&x,&y);
				sn[i][0]=x,sn[i][1]=y;
				fa[x]=i,fa[y]=i;
				va[i]=-1;
			}
			else va[i]=x,ri=max(ri,va[i]),le=min(le,va[i]);
		}
		ans=le;
		while(le<=ri)
		{
			mid=(le+ri)>>1;
			fo(i,1,n) 
			{
				if(va[i]>=mid) v[i]=1; else v[i]=0;
				if(va[i]==-1) v[i]=-1;
			}
			if(check()) le=mid+1,ans=mid;
			else ri=mid-1;
		}
		printf("%d\n",ans);
		
	}
	return 0;
}








