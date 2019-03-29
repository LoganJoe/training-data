---
title: " BZOJ1023[SHOI2008]cactus仙人掌图\t\t"
tags:
  - 仙人掌
  - 单调队列
url: 5950.html
id: 5950
categories:
  - BZOJ
  - Solution
date: 2019-01-02 22:30:43
---

如果是树的话，方法有很多，可以dfs两遍找到直径的两个端点，或者树形dp最长链。 如果是仙人掌，我们仍然考虑树形dp的写法。 记$f\[i\]$为从$i$出发最长的路径长度。 我们从$1$开始dfs一遍来求所有的$f$。 对于不在环上的边，我们可以直接转移和更新答案，即$f\[i\]=\\max\\{f\[j\]\\}+1$。 如果我们求完$f\[i\]$后，发现$i$是一个环的顶端，那么我们就开始处理这个环。 我们把环上的点拎出来，分别记为$a\_1,a\_2,a\_3,…,a\_m$。 假设进入环的点和从环上出去的点分别为$a\_x,a\_y(x>y)$，那么最长的路径长度为$f\[a\_x\]+f\[a\_y\]+\\min(x-y,m-(x-y))$。 我们可以枚举$x$，然后用单调队列维护最优的$y$。 最后再用环上所有点更新$f\[i\]$即可。 具体实现看代码。

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
#define N 50005 
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K,a,b,ecnt,last\[N\],idx,low\[N\],dfn\[N\],fa\[N\],A\[N<<1\],q\[N<<1\],f\[N\],ans;
struct road{int to,nex;}e\[N<<2\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
void Solve(int x,int y)
{
	int An=0,l,r;q\[l=r=1\]=1;
	for(int i=x;i^y;i=fa\[i\]) A\[++An\]=f\[i\];
	A\[++An\]=f\[y\];
	for(int i=1;i<=An;i++) A\[i+An\]=A\[i\]; 
	for(int i=2;i<=An<<1;i++)
	{
		for(;l<r&&i-q\[l\]>An>>1;l++);
		ans=max(ans,A\[i\]+i+A\[q\[l\]\]-q\[l\]);
		for(;l<=r&&A\[i\]-i>=A\[q\[r\]\]-q\[r\];r--);
		q\[++r\]=i;
	}
	for(int i=1;i<=An;i++) f\[y\]=max(f\[y\],A\[i\]+min(i,An-i));
}
void tarjan(int x,int fath=0)
{
	low\[x\]=dfn\[x\]=++idx,fa\[x\]=fath;
	for(int k=last\[x\];k;k=e\[k\].nex)
	{
		if(!dfn\[e\[k\].to\]) tarjan(e\[k\].to,x),low\[x\]=min(low\[x\],low\[e\[k\].to\]);
		else if(e\[k\].to^fath) low\[x\]=min(low\[x\],dfn\[e\[k\].to\]);
		if(low\[e\[k\].to\]>dfn\[x\])
			ans=max(ans,f\[x\]+f\[e\[k\].to\]+1),f\[x\]=max(f\[x\],f\[e\[k\].to\]+1);
	}
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(dfn\[e\[k\].to\]>dfn\[x\]&&fa\[e\[k\].to\]^x) Solve(e\[k\].to,x);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&K,&a);
		for(int j=1;j<K;j++,a=b) scanf("%d",&b),adde(a,b),adde(b,a);
	}
	tarjan(1);
	printf("%d\\n",ans);
	return 0;
}