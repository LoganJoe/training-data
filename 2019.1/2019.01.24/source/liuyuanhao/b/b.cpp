#include <cstdio>
#include <cstring>
#include <iostream>
#define oo 2139062143
#define fo(i,x,y) for (int i=(x);i<=(y);++i)
using namespace std;
const int N=50500;
int n,q;
int tot,nex[N*2],las[N],v[N*2],to[N*2];
int p[N];
int ans;
void link(int x,int y,int c)
{
	to[++tot]=y,nex[tot]=las[x],las[x]=tot;
	v[tot]=c;
}
int typ;
int vis[N];
void run(int x,int t,int f)
{
	++ans;vis[x]=1;
	for(int tp=las[x];tp;tp=tp[nex])
	if(to[tp]!=f)
	{
		if(v[tp]==2||(v[tp]==3&&t==0))
			run(to[tp],1,x);
		if(v[tp]==1)
			run(to[tp],t,x);
	}
}
int va[N];
int t[5][N*4];
//0 是否不存在3
//1 是否存在1 
//2 是否存在2 
//3 是否存在3
void build(int x,int l,int r)
{
	if(l==r)
	{
		t[va[l]][x]=1;
		if(va[l]!=3) t[0][l]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	fo(i,0,3) t[i][x]=t[i][x<<1]|t[i][x<<1|1];
}
void cg(int x,int l,int r,int p,int v)
{
	if(l==r)
	{
		va[l]=v;
		t[va[l]][x]=1;
		if(va[l]!=3) t[0][l]=1;		
	}
	int mid=(l+r)>>1;
	if(p<=mid) cg(x<<1,l,mid,p,v);
	else cg(x<<1|1,mid+1,r,p,v);
	fo(i,0,3) t[i][x]=t[i][x<<1]|t[i][x<<1|1];
}
int main()
{
//	 freopen("D:/LiuYuanHao/b.in","r",stdin);
	tot=1;
	scanf("%d%d",&n,&q);
	typ=2;
	fo(i,1,n-1)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		p[i]=tot+1;
		if(y!=x+1) typ=0;
		link(x,y,c),link(y,x,c);
	}
	if(n*q<=1e7) typ=1;
	if(typ==2)
	{
		fo(i,1,n-1)
			va[i]=v[p[i]];
		build(1,1,n-1);
	}
	int lastans=0;
	while(q--)
	{
		int x,w,s,t;
		scanf("%d%d%d%d",&x,&w,&s,&t);
		x^=lastans,w^=lastans,s^=lastans,t^=lastans;
		ans=0;
		v[p[x]]=v[p[x]^1]=w;
		if(typ==1)
		{
			memset(vis,0,sizeof vis);
			run(s,0,0);
			printf("%d %d\n",ans,vis[t]);
			lastans=ans;
		}
		else if(typ==2)
		{
			cg(1,1,n-1,x,w);/*
			int le=fl(1,1,n-1,3,s-1)+1,ri=fr(1,1,n-1,3,s);
			if(fr(1,1,n-1,2,le)>=s) le=min(le,fl(1,1,n-1,3,le-1)+1);
			if(fl(1,1,n-1,2,ri)<=s-1) ri=max(ri,fr(1,1,n-1,3,ri));
			ans=ri-le+1;int flag;
			if(t>=le&&t<=ri) flag=1;
			else flag=0;
			printf("%d %d\n",ans,flag);
			lastans=ans;*/
		}
	}
	return 0;
}








