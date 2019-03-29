#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define fo(i,a,b) for(int i=a;i<=b;++i)
#define fod(i,a,b) for(int i=a;i>=b;--i)
#define N 300005
using namespace std;
int n,m,a1[N][3],ask[N][4];
struct node
{
	int fn[N],f[N],r[N],d[N],sz[N],sd[N],t[N][2],s1[N],vl[N],sv[N];
	void hb(int p,int x,int y)
	{
		if(x&&p>=0) t[x][p]=y;
		if(y) f[y]=x,fn[y]=p;
	}
	void up(int k)
	{
		if(!k) return;
		sz[k]=sz[t[k][0]]+sz[t[k][1]]+1+sd[k];
		s1[k]=s1[t[k][0]]+s1[t[k][1]]+sv[k]+vl[k];
	}
	void down(int k)
	{
		r[t[k][0]]^=r[k],r[t[k][1]]^=r[k];
		if(r[k]) swap(t[k][0],t[k][1]),fn[t[k][0]]=0,fn[t[k][1]]=1;
		r[k]=0;
	}
	void rot(int k)
	{
		int p=fn[k],fa=f[k];
		hb(p,fa,t[k][1-p]);
		hb(fn[fa],f[fa],k);
		hb(1-p,k,fa);
		up(fa),up(k),up(f[k]);
	}
	void splay(int k,int x)
	{
		d[0]=1,d[1]=k;
		while(fn[d[d[0]]]!=-1&&f[d[d[0]]]!=x) d[++d[0]]=f[d[d[0]-1]];
		fod(i,d[0],1) down(d[i]);
		while(fn[k]!=-1&&f[k]!=x)
		{
			if(fn[f[k]]==-1||f[f[k]]==x) rot(k);
			else if(fn[f[k]]==fn[k]) rot(f[k]),rot(k);
			else rot(k),rot(k);
		}
	}
	void access(int k)
	{	
		int t1=k;
		splay(k,0);
		sd[k]+=sz[t[k][1]],sv[k]+=s1[t[k][1]];
		fn[t[k][1]]=-1,t[k][1]=0;
		up(k);
		while(f[k]!=0)
		{
			int p=f[k];splay(p,0);
			sd[p]+=sz[t[p][1]],sv[p]+=s1[t[p][1]];
			fn[t[p][1]]=-1;
			hb(1,p,k);
			sd[p]-=sz[k],sv[p]-=s1[k];
			up(p),k=p;
		}
		splay(t1,0);
	}
	void make(int k)
	{
		access(k),r[k]^=1;
	}
	void link(int x,int y,int p)
	{
		make(x),access(y);
		hb(-1,y,x);
		sd[y]+=sz[x],sv[y]+=s1[x];
		up(x),up(y);
		if(p==3&&x<=n) 
		{
			vl[x]-=sz[y+n];
			vl[y]-=sz[x+n];
		}
		up(x),up(y);
	}
	void cut(int x,int y,int p)
	{
		make(x),access(y),splay(x,y);
		f[x]=0,fn[x]=-1,t[y][0]=0;
		up(x),up(y);
		if(p==3&&x<=n) 
		{
			vl[y]+=sz[x+n];
			vl[x]+=sz[y+n];
			up(x),up(y);
		}
	}
}T;
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	cin>>n>>m;
	fo(i,1,2*n) T.sz[i]=1;
	fo(i,1,n-1)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a1[i][0]=x,a1[i][1]=y,a1[i][2]=z;
		if(z==2) T.link(x+n,y+n,2);
		else 
		{
			if(z!=3) T.link(x,y,1),T.link(x+n,y+n,2);
			else T.link(x,y,1),T.cut(x,y,3);
		}
	}
	int ans=0;
	fo(i,1,m)
	{
		fo(j,0,3) scanf("%d",&ask[i][j]),ask[i][j]^=ans;
		if(ask[i][1]!=a1[ask[i][0]][2])
		{
			int p=a1[ask[i][0]][2],q=ask[i][1],x=a1[ask[i][0]][0],y=a1[ask[i][0]][1];
			if(p==3) T.link(x+n,y+n,q);
			if(q==3) T.cut(x+n,y+n,p);
			if(p==1) T.cut(x,y,q);
			if(q==1) T.link(x,y,p);
			a1[ask[i][0]][2]=q;
		}
		int x=ask[i][2];
		T.make(x),T.access(x);
		T.make(x+n),T.access(x+n);
		ans=T.sz[x+n]+T.s1[x];
		printf("%d\n",ans);
	}
}