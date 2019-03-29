---
title: " BZOJ2125最短路\t\t"
tags:
  - 仙人掌
  - 圆方树
  - 最短路
url: 5954.html
id: 5954
categories:
  - BZOJ
  - Solution
date: 2019-01-02 22:55:24
---

仙人掌上的最短路。 我们先把仙人掌的圆方树建起来。圆方树上圆点和圆点之间的边权就是原图的边权，圆点和方点之间的边权是圆点到方点对应的环的顶端（方点的父亲）的最短距离。 假设询问$a,b$之间的最短路。我们先求出$a,b$的$LCA$。 如果$LCA$为圆点，那么$a,b$之间的最短路就是圆方树上$a,b$之间的路径长度。预处理根到每个点的路径长度即可直接求出。 如果$LCA$为方点，我们找到$a$往上走离$LCA$最近的一个点$x$，$b$往上走离$LCA$最近的一个点$y$。 我们可以将$a\\rightarrow b$的路径拆成$a\\rightarrow x\\rightarrow y\\rightarrow b$，其中$a\\rightarrow x$和$y\\rightarrow b$的长度就是圆方树上的路径长度，可以直接求。 那么我们只用考虑$x\\rightarrow y$的最短路，也就是在环上如何绕的问题。 对于每个环，我们记下环的长度，以及环上每个点走到环的顶端的最短距离（也就是圆点到方点之间的边权），还有最短距离的走法（两种）。 根据这些信息，我们就可以求出在环上从$x$到$y$的两条路径长度，取个$\\min$就是最短路了。 实现细节见代码。 注意对long long取绝对值要用llabs。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 20005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,Q,a,b,c;
class Tree
{
	int ecnt,last\[N\],deep\[N\],fa\[N\]\[20\];ll dist\[N\];
	struct road{int to,v,nex;}e\[N<<1\];
	int asklca(int x,int y)
	{
		if(deep\[x\]<deep\[y\]) std::swap(x,y);
		for(int j=19;~j;j--) if(deep\[x\]-(1<<j)>=deep\[y\]) x=fa\[x\]\[j\];
		if(x==y) return x;
		for(int j=19;~j;j--) if(fa\[x\]\[j\]^fa\[y\]\[j\]) x=fa\[x\]\[j\],y=fa\[y\]\[j\];
		return fa\[x\]\[0\];
	}
	int Jump(int x,int d) {for(int j=19;~j;j--) if(d>>j&1) x=fa\[x\]\[j\];return x;}
public:
	int n,mark\[N\];ll val\[N\];
	void adde(int u,int v,int w) {e\[++ecnt\]=(road){v,w,last\[u\]},last\[u\]=ecnt;}
	void dfs(int x,int fath=0)
	{
//		dbg1(x),dbg2(fath);
		deep\[x\]=deep\[fath\]+1,fa\[x\]\[0\]=fath;
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(e\[k\].to^fath) dist\[e\[k\].to\]=dist\[x\]+e\[k\].v,dfs(e\[k\].to,x);
	}
	void Prepare()
	{
		for(int j=1;j<20;j++)
			for(int i=1;i<=n;i++) fa\[i\]\[j\]=fa\[fa\[i\]\[j-1\]\]\[j-1\];
	}
	ll ask(int x,int y)
	{
		int LCA=asklca(x,y),a,b;
		if(LCA<=::n) return dist\[x\]+dist\[y\]-2*dist\[LCA\];
		a=Jump(x,deep\[x\]-deep\[LCA\]-1),b=Jump(y,deep\[y\]-deep\[LCA\]-1);
		ll d1=dist\[a\]-dist\[LCA\],d2=dist\[b\]-dist\[LCA\];
		if(mark\[a\]) d1=val\[LCA\]-d1;if(mark\[b\]) d2=val\[LCA\]-d2;
		return dist\[x\]-dist\[a\]+dist\[y\]-dist\[b\]+min(llabs(d1-d2),val\[LCA\]-llabs(d1-d2));
	}
}T;
class Graph
{
	int ecnt,last\[N\],fa\[N\],idx,low\[N\],dfn\[N\],A\[N\],An;ll dist\[N\];
	struct road{int to,v,nex;}e\[N<<1\];
	void Solve(int x,int y,ll v)
	{
		An=0;ll d=0,tmp;
		for(int i=x;i^y;i=fa\[i\]) A\[++An\]=i,v+=dist\[i\]-dist\[fa\[i\]\];
		A\[++An\]=y,std::reverse(A+1,A+1+An),T.val\[++T.n\]=v;
		for(int i=1;i<=An;i++)
		{
			tmp=min(d,v-d),T.adde(T.n,A\[i\],tmp),T.adde(A\[i\],T.n,tmp);
			T.mark\[A\[i\]\]=tmp!=d,d+=dist\[A\[i+1\]\]-dist\[A\[i\]\];
		}
	}
public:
	void adde(int u,int v,int w) {e\[++ecnt\]=(road){v,w,last\[u\]},last\[u\]=ecnt;}
	void tarjan(int x,int fath=0)
	{
		fa\[x\]=fath,low\[x\]=dfn\[x\]=++idx;
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(!dfn\[e\[k\].to\])
			{
				dist\[e\[k\].to\]=dist\[x\]+e\[k\].v,tarjan(e\[k\].to,x),low\[x\]=min(low\[x\],low\[e\[k\].to\]);
				if(low\[e\[k\].to\]>dfn\[x\]) T.adde(x,e\[k\].to,e\[k\].v),T.adde(e\[k\].to,x,e\[k\].v);
			}
			else if(e\[k\].to^fath) low\[x\]=min(low\[x\],dfn\[e\[k\].to\]);
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(dfn\[e\[k\].to\]>dfn\[x\]&&fa\[e\[k\].to\]^x) Solve(e\[k\].to,x,e\[k\].v);
	}
}G;
int main()
{
	scanf("%d%d%d",&n,&m,&Q),T.n=n;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&a,&b,&c),G.adde(a,b,c),G.adde(b,a,c);
	G.tarjan(1);T.dfs(1),T.Prepare();
	for(;Q--;) scanf("%d%d",&a,&b),printf("%lld\\n",T.ask(a,b));
	return 0;
}