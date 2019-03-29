---
title: " DTOJ4166「PKUWC2018」Minimax\t\t"
tags:
  - 树形dp
  - 线段树合并
url: 6862.html
id: 6862
categories:
  - DTOJ
  - Solution
date: 2019-03-07 22:48:17
---

我们可以将权值离散化。 记$f\[i\]\[j\]​$表示结点$i​$权值为$j​$的概率。 那么有 $$ f\[lc\_i\]\[j\]\\times f\[rc\_i\]\[k\]\\times p\_i\\Rightarrow f\[i\]\[\\max(j,k)\] $$ $$ f\[lc\_i\]\[j\]\\times f\[rc\_i\]\[k\]\\times (1-p\_i)\\Rightarrow f\[i\]\[\\min(j,k)\] $$ 对每一个结点开一棵线段树，第$i$个位置是这个点权值为$i$的概率。 可以发现合并的时候可以用线段树合并优化。 在合并的过程中我们要记录下两棵树在当前区间左侧的权值和，因为要先递归右儿子。 具体细节参考代码。 时间复杂度$\\Theta(n\\log n)$。

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
#define N 300005
#define mod 998244353
#define ll long long
#define db double
#define lb(x) std::lower_bound(so+1,so+1+tot,x)-so
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,ecnt,last\[N\],fa\[N\],son\[N\],val\[N\],inv,so\[N\],cnt,tot,ans;
struct road{int to,nex;}e\[N\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
class SegmentTree
{
#define lc t\[x\].ls
#define rc t\[x\].rs
#define mid (l+r>>1)
	struct node{int ls,rs,f,v;}t\[N*20\];
	void pushup(int x) {t\[x\].v=cal(t\[lc\].v+t\[rc\].v);}
	void pushdown(int x)
	{
		if(t\[x\].f>1)
		{
			t\[lc\].v=(ll)t\[lc\].v\*t\[x\].f%mod,t\[rc\].v=(ll)t\[rc\].v\*t\[x\].f%mod;
			t\[lc\].f=(ll)t\[lc\].f\*t\[x\].f%mod,t\[rc\].f=(ll)t\[rc\].f\*t\[x\].f%mod,t\[x\].f=1;
		}
	}
public:
	int root\[N\],cntnode;
	void insert(int &x,int l,int r,int p,int v)
	{
		t\[x=++cntnode\].v=v,t\[x\].f=1;
		if(l==r) return;
		p<=mid?insert(lc,l,mid,p,v):insert(rc,mid+1,r,p,v);
	}
	void merge(int &x,int y,int id,int v1,int v2)
	{
		if(!x&&!y) return;
		if(!x||!y)
		{
			if(!y) v1=v2;
			int p=cal((ll)v1\*val\[id\]%mod+(ll)(mod+1-v1)\*(mod+1-val\[id\])%mod);
			x=x+y,t\[x\].v=(ll)t\[x\].v\*p%mod,t\[x\].f=(ll)t\[x\].f\*p%mod;
			return;
		}
		pushdown(x),pushdown(y);
		merge(rc,t\[y\].rs,id,cal(v1+t\[lc\].v),cal(v2+t\[t\[y\].ls\].v)),merge(lc,t\[y\].ls,id,v1,v2);
		pushup(x);
	}
	void Solve(int x,int l,int r)
	{
		if(!x) return;
		if(l==r)
		{
			ans=cal(ans+(ll)l\*so\[l\]%mod\*t\[x\].v%mod*t\[x\].v%mod);
			return;
		}
		pushdown(x);
		Solve(lc,l,mid),Solve(rc,mid+1,r);
	}
}T;
void dfs(int x)
{
	int to1=0,to2=0;
	for(int k=last\[x\];k;k=e\[k\].nex) dfs(e\[k\].to),to1?to2=e\[k\].to:to1=e\[k\].to;
	if(to1) T.root\[x\]=T.root\[to1\];else T.insert(T.root\[x\],1,tot,val\[x\],1);
	if(to2) T.merge(T.root\[x\],T.root\[to2\],x,0,0);
}
int main()
{
	scanf("%d",&n),inv=Pow(10000,mod-2);
	for(int i=1;i<=n;i++) scanf("%d",&fa\[i\]),son\[fa\[i\]\]++,i>1?(adde(fa\[i\],i),1):1;
	for(int i=1;i<=n;i++) scanf("%d",&val\[i\]),son\[i\]?val\[i\]=(ll)val\[i\]*inv%mod:so\[++cnt\]=val\[i\];
	std::sort(so+1,so+1+cnt),tot=std::unique(so+1,so+1+cnt)-so-1;
	for(int i=1;i<=n;i++) if(!son\[i\]) val\[i\]=lb(val\[i\]);
	dfs(1),T.Solve(T.root\[1\],1,tot);
	printf("%d\\n",ans);
	return 0;
}