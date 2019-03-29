---
title: " DTOJ4110painting\t\t"
tags:
  - 区间dp
  - 思路
url: 6300.html
id: 6300
categories:
  - DTOJ
  - Solution
  - 不会证
date: 2019-02-01 20:03:17
---

题目中给出了很多优秀的性质，比如说每次刷的颜色都不同，并且最终每种颜色都有出现，保证有解。 记$l\_i$为第$i$种颜色出现的最靠左的位置，$r\_i$为第$i$种颜色出现的最靠右的位置。那么刷第$i$种颜色的区间一定包含了$\[l\_i,r\_i\]$。 考虑如何使刷的区间尽可能长。 显然是要让后面的覆盖当前的。 如果$j$能覆盖$i$，说明$\[l\_i,r\_i\]$和$\[l\_j,r\_j\]$是连续的。 假设我们有$tot$个连续的区间，分别为$\[L\_1,R\_1\],\[L\_2,R\_2\],…,\[L_{tot},R_{tot}\]$，如何最大化刷的区间长度呢？ 考虑dp。 记$f\[i\]\[j\]$为考虑第$i$个到第$j$个区间，并且仅使用位置$\[L\_i,R\_j\]$，最多能刷的区间长度。 枚举最先刷的区间$k$，即可转移。 $$ f\[i\]\[k-1\]+f\[k+1\]\[j\]+R\_j-L\_i+1\\Rightarrow f\[i\]\[j\] $$ 时间复杂度$\\Theta(tot^3)$。 考虑优化。 通过打表…或者手模，我们发现，最优的转移点一定是$k=i$或$k=j$（不会证），那么就变成了： $$ f\[i\]\[j\]=\\max(f\[i+1\]\[j\],f\[i\]\[j-1\])+R\_j-L\_i+1 $$ 时间复杂度$\\Theta(tot^2)$。 每组连续区间之间是独立的，我们每次抓出一组连续区间来跑dp即可。 实现细节参考代码。 时间复杂度$\\Theta(n^2)$。

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
#define M 5005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,Cn,A\[N\],mark\[N\];ll f\[M\]\[M\],ans;
struct info{int l,r;}B\[M\],C\[M\];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),B\[A\[i\]\].l=B\[A\[i\]\].l?B\[A\[i\]\].l:i,B\[A\[i\]\].r=i;
	for(int i=1;i<=m;i++) mark\[B\[i\].l\]=i;
	for(int i=1;i<=n;i++) if(mark\[i\])
	{
		Cn=0;
		for(int j=mark\[i\];j;j=mark\[B\[j\].r+1\]) C\[++Cn\]=B\[j\],mark\[B\[j\].l\]=0;
		for(int j=1;j<=Cn;j++)
			for(int k=1;k<=Cn;k++) f\[j\]\[k\]=0;
		for(int j=1;j<=Cn;j++)
			for(int l=1,r=j;r<=Cn;l++,r++) f\[l\]\[r\]=max(f\[l\]\[r-1\],f\[l+1\]\[r\])+C\[r\].r-C\[l\].l+1;
		ans+=f\[1\]\[Cn\];
	}
	printf("%lld\\n",ans+f\[1\]\[m\]);
	return 0;
}