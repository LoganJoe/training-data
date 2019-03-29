---
title: " DTOJ4230Subsequence\t\t"
tags:
  - 二分
  - 平衡树
url: 6980.html
id: 6980
categories:
  - DTOJ
  - Solution
date: 2019-03-16 11:25:33
---

这道题其实是[DTOJ3037最大价值](http://www.dtenomde.com/author=jiangyutong/article=3428/)经过第一步的简单转换后的模型。 题解直接戳进去就好了。

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
#define N 100005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,A\[N\];ll ans\[N\];
class SplayTree
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
#define pa t\[x\].fa
	struct node{int fa,son\[2\],sz;ll v,f;}t\[N\];
	bool getson(int x) {return t\[pa\].son\[1\]==x;}
	void pushup(int x) {t\[x\].sz=t\[lc\].sz+t\[rc\].sz+1;}
	void pushdown(int x)
	{
		if(t\[x\].f)
		{
			t\[lc\].v+=t\[x\].f,t\[lc\].f+=t\[x\].f;
			t\[rc\].v+=t\[x\].f,t\[rc\].f+=t\[x\].f,t\[x\].f=0;
		}
	}
	void rotate(int x)
	{
		int y=pa,z=t\[y\].fa,k=getson(x);
		if(z) t\[z\].son\[t\[z\].son\[1\]==y\]=x;
		t\[y\].son\[k\]=t\[x\].son\[!k\],t\[t\[x\].son\[!k\]\].fa=y;
		t\[x\].son\[!k\]=y,t\[y\].fa=x,t\[x\].fa=z;
		pushup(y);
	}
	void splay(int x,int f=0)
	{
		for(;pa^f;rotate(x))
			if(t\[pa\].fa^f) rotate(getson(x)^getson(pa)?x:pa);
		pushup(x);if(!f) root=x;
	}
public:
	int root,cntnode;
	void init() {root=cntnode=1,t\[1\].v=A\[1\],t\[1\].sz=1;}
	int find(int x,int rk,int v)
	{
		if(!x) return 0;
		pushdown(x);
		if((ll)(rk+t\[lc\].sz+1)*v<=t\[x\].v) return find(rc,rk+t\[lc\].sz+1,v);
		int res=find(lc,rk,v);
		if(!res) res=x;
		return res;
	}
	void insert(int p,int v)
	{
		int cnt,x=++cntnode;
		if(p) splay(p),cnt=t\[t\[p\].son\[0\]\].sz+1;
		else cnt=t\[root\].sz+1;
		t\[x\].v=(ll)v*cnt,t\[x\].sz=1;
		if(p)
		{
			pushdown(p);
			if(t\[p\].son\[0\]) t\[t\[p\].son\[0\]\].fa=x,t\[x\].son\[0\]=t\[p\].son\[0\],t\[p\].son\[0\]=0,pushup(p);
			t\[x\].son\[1\]=p,t\[p\].fa=x,pushup(root=x),t\[rc\].v+=v,t\[rc\].f+=v;
		}
		else
		{
			for(p=root;t\[p\].son\[1\];pushdown(p),p=t\[p\].son\[1\]);
			splay(p),t\[p\].son\[1\]=x,pa=p,pushup(p);
		}
	}
	void dfs(int x) {if(!x) return;pushdown(x),dfs(lc),ans\[++ans\[0\]\]=t\[x\].v,dfs(rc);}
}T;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]);
	T.init();
	for(int i=2,pos;i<=n;i++) pos=T.find(T.root,0,A\[i\]),T.insert(pos,A\[i\]);
	T.dfs(T.root),ans\[0\]=0;
	for(int i=1;i<=n;i++) ans\[i\]+=ans\[i-1\],printf("%lld ",ans\[i\]);puts("");
	return 0;
}