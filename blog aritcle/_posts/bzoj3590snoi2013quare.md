---
title: " BZOJ3590[Snoi2013]Quare\t\t"
tags:
  - 思路
  - 状压dp
url: 5959.html
id: 5959
categories:
  - BZOJ
  - Solution
date: 2019-01-03 22:28:21
---

$n$这么小，我们考虑状压。 记$f\[i\]$为使状态$i$中的点形成一个强连通分量的最小代价。 容易发现，最优解的策略一定是由一个小的强连通分量加一条链组成一个大的强连通分量。 我们可以设计dp辅助转移。 记$g\[i\]\[j\]\[k\]$为使状态$i$中的点形成一条链，且链的两个端点分别为$j$和$k$的最小代价。 记$Min1\[i\]\[j\],Min2\[i\]\[j\]$为点$j$到状态$i$中的所有点的边权的最小值和次小值。 通过这些我们就可以求出$f\[i\]$。 具体地，我们枚举$i$的一个子集$j$，以及在$i$中而不在$j$中的两点$a,b$，那么有 $$ f\[i\]=\\min \\begin{cases} f\[j\]+g\[i\\oplus j\]\[a\]\[b\]+Min1\[j\]\[a\]+Min1\[j\]\[b\] & a\\neq b \\newline f\[j\]+g\[i\\oplus j\]\[a\]\[b\]+Min1\[j\]\[a\]+Min2\[j\]\[b\] & a=b \\end{cases} $$ 其中$\\oplus$表示异或运算。 $g\[i\]\[j\]\[k\],MIn1\[i\]\[j\],Min2\[i\]\[j\]$都很容易预处理出来。 具体参考代码。 时间复杂度$\\Theta(n^23^n)​$，不是很满。 好像是第一次rk1？害怕。

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
#define N 15
#define M 5000
#define inf 1e9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int T,n,m,a,b,c,MaxS,ecnt,last\[N\],A\[N\],An,f\[M\],g\[M\]\[N\]\[N\],Min1\[M\]\[N\],Min2\[M\]\[N\];
struct road{int to,v,nex;}e\[N\];
void adde(int u,int v,int w) {e\[++ecnt\]=(road){v,w,last\[u\]},last\[u\]=ecnt;}
void clear()
{
	ecnt=0;
	for(int i=1;i<=n;i++) last\[i\]=0;
}
int main()
{
	for(scanf("%d",&T);T--;clear())
	{
		scanf("%d%d",&n,&m),MaxS=(1<<n)-1;
		for(int i=1;i<=m;i++) scanf("%d%d%d",&a,&b,&c),adde(a,b,c),adde(b,a,c);
		for(int i=0;i<=MaxS;i++)
		{
			f\[i\]=inf;
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++) g\[i\]\[j\]\[k\]=inf;
			for(int j=1;j<=n;j++) Min1\[i\]\[j\]=Min2\[i\]\[j\]=inf;
		}
		for(int i=1;i<=MaxS;i++)
			for(int j=1;j<=n;j++) if(!(i>>j-1&1))
				for(int k=last\[j\];k;k=e\[k\].nex) if(i>>e\[k\].to-1&1)
					if(e\[k\].v<Min1\[i\]\[j\]) Min2\[i\]\[j\]=Min1\[i\]\[j\],Min1\[i\]\[j\]=e\[k\].v;
					else Min2\[i\]\[j\]=min(Min2\[i\]\[j\],e\[k\].v);
		for(int i=1;i<=n;i++) f\[1<<i-1\]=g\[1<<i-1\]\[i\]\[i\]=0;
		for(int i=1,S;i<MaxS;i++)
		{
			An=0;
			for(int j=1;j<=n;j++) if(i>>j-1&1) A\[++An\]=j;
			for(int j=1;j<=An;j++)
				for(int s=1;s<=An;s++) if(g\[i\]\[A\[j\]\]\[A\[s\]\]<inf)
					for(int k=last\[A\[s\]\];k;k=e\[k\].nex) if(!(i>>e\[k\].to-1&1))
						S=i|(1<<e\[k\].to-1),g\[S\]\[A\[j\]\]\[e\[k\].to\]=min(g\[S\]\[A\[j\]\]\[e\[k\].to\],g\[i\]\[A\[j\]\]\[A\[s\]\]+e\[k\].v);
		}
		for(int i=1;i<=MaxS;i++)
			for(int j=(i-1)&i;j;j=(j-1)&i) if(f\[i^j\]<inf)
			{
				An=0;
				for(int k=1;k<=n;k++) if(j>>k-1&1) A\[++An\]=k;
				for(int k=1;k<=An;k++) if(Min1\[i^j\]\[A\[k\]\]<inf)
					for(int s=1;s<=An;s++)
						if(g\[j\]\[A\[k\]\]\[A\[s\]\]<inf&&Min1\[i^j\]\[A\[s\]\]<inf)
							if(k^s) f\[i\]=min(f\[i\],f\[i^j\]+g\[j\]\[A\[k\]\]\[A\[s\]\]+Min1\[i^j\]\[A\[k\]\]+Min1\[i^j\]\[A\[s\]\]);
							else f\[i\]=min(f\[i\],f\[i^j\]+g\[j\]\[A\[k\]\]\[A\[s\]\]+Min1\[i^j\]\[A\[k\]\]+Min2\[i^j\]\[A\[s\]\]);
			}
		f\[MaxS\]<inf?printf("%d\\n",f\[MaxS\]):puts("impossible");
	}
	return 0;
}