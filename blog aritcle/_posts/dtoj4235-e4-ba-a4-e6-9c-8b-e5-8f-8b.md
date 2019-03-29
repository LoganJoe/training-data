---
title: " DTOJ4235交朋友\t\t"
tags:
  - 并查集
  - 思路
url: 7021.html
id: 7021
categories:
  - DTOJ
  - Solution
date: 2019-03-17 12:32:34
---

若两个点能找到一个中介，就在并查集中将这两个点合并。 那么在同一个并查集中的任意两点都可以连边，这样就可以计算出最终的所有边数，扣掉原有的就是答案。 考虑如何合并点。 我们从出度$\\geq 2$的点开始dfs，将它所有能访问到的点在并查集中合并。因为总是能在这些点中找到一个点做中介将它们合并，可以画图理解。 如果一个点能到的所有点都已经和它并在一起了，那么这个点就不用继续dfs下去了。 具体细节参考代码。

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
int n,m,a,b,ecnt=1,last\[N\],out\[N\],mark\[N\],fa\[N\],id,cnt\[N\];ll ans;
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
int find(int x) {return fa\[x\]^x?fa\[x\]=find(fa\[x\]):x;}
void dfs(int x)
{
	for(int k=last\[x\];k;k=e\[k\].nex)
	{
		fa\[find(e\[k\].to)\]=id;
		if(!mark\[e\[k\].to\]) mark\[e\[k\].to\]=1,dfs(e\[k\].to);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b),out\[a\]++;
	for(int i=1;i<=n;i++) fa\[i\]=i;
	for(int i=1;i<=n;i++)
		if(out\[i\]>1&&!mark\[i\])
		{
			for(int k=last\[i\];k;k=e\[k\].nex) {id=find(e\[k\].to);break;}
			dfs(i);
		}
	for(int i=1;i<=n;i++) cnt\[find(i)\]++;
	for(int i=1;i<=n;i++) if(cnt\[i\]) ans+=(ll)cnt\[i\]*(cnt\[i\]-1);
	for(int i=1;i<=n;i++)
		for(int k=last\[i\];k;k=e\[k\].nex) if(fa\[i\]==fa\[e\[k\].to\]) ans--;
	printf("%lld\\n",ans+m);
	return 0;
}