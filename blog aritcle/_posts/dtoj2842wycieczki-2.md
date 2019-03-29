---
title: " DTOJ2842Wycieczki\t\t"
tags:
  - 倍增
  - 矩阵
url: 4530.html
id: 4530
categories:
  - DTOJ
  - Solution
date: 2018-10-25 13:23:35
---

注意到答案$\\leq 3k$。考虑二分答案$mid$，判断是否可行。 如果边权只有$1$的话，通过建一个虚拟点，我们可以用矩阵快速幂求出$\\leq mid$的路径条数。 边权有$1,2,3$的话，我们将每个点拆成$3$个点，那么就能将边权为$2$的边拆成两条边权为$1$的边，边权为$3$的边拆成三条边权为$1$的边。 这样子就能用矩阵快速幂求路径条数了。 这样是$\\Theta(n^3\\log ^2 10^{18})$的，会TLE。 我们先用矩阵快速幂求出$\\leq 2^i$的路径条数，其中$i\\in\[0,62\]$。 然后可以用类似倍增“试探”的方法求出答案。具体地，我们从大到小枚举$i$，然后在当前求出的答案上$+2^i$，即乘上$2^i$的矩阵，然后计算一下路径条数。如果路径条数$<k$的话，最终的答案肯定大于当前答案$+2^i$，我们就可以先把$2^i$加进去。否则换个更小的$i$继续试即可。 注意在矩乘中是两个long long相乘，可能会爆long long。如果当前值超过long long的范围，我们可以用$-1$表示，运算时特判一下即可。具体可参考代码。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 150
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
#define dbg(x) cerr<<\_\_FUNCTION\_\_<<"() L"<<\_\_LINE\_\_<<" "<<#x"="<<(x)<<"\\n"
int n,m,a,b,c;ll ans,K;
struct Matrix
{
	ll v\[N\]\[N\];
	friend Matrix operator*(Matrix t1,Matrix t2)
	{
		Matrix res;
		for(int i=0;i<=n*3;i++)
			for(int j=0;j<=n*3;j++)
			{
				res.v\[i\]\[j\]=0;
				for(int k=0;k<=n*3;k++)
				{
					if(t1.v\[i\]\[k\]<0||t2.v\[k\]\[j\]<0) {res.v\[i\]\[j\]=-1;break;}
					if(t1.v\[i\]\[k\]>K*1./t2.v\[k\]\[j\]) {res.v\[i\]\[j\]=-1;break;}
					res.v\[i\]\[j\]+=t1.v\[i\]\[k\]*t2.v\[k\]\[j\];
					if(res.v\[i\]\[j\]>K) {res.v\[i\]\[j\]=-1;break;}
				}
			}
		return res;
	}
}e,po\[65\],A,B;
bool Judge()
{
	ll res=0;
	for(int i=1;i<=n;i++) if(B.v\[i\]\[0\]<0||(res+=B.v\[i\]\[0\]-1)>=K) return 0;
	return 1;
}
int main()
{
	scanf("%d%d%lld",&n,&m,&K),e.v\[0\]\[0\]=1;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&a,&b,&c),e.v\[a+(c-1)*n\]\[b\]++;
	for(int i=1;i<=n;i++) A.v\[i\]\[i\]=e.v\[i\]\[0\]=e.v\[i\]\[i+n\]=e.v\[i+n\]\[i+n+n\]=1;
	po\[0\]=e;
	for(int i=1;i<63;i++) po\[i\]=po\[i-1\]*po\[i-1\];
	for(int i=62;~i;i--) {B=A*po\[i\];if(Judge()) ans|=1ll<<i,A=B;}
	printf("%lld\\n",ans>K*3?-1:ans);
	return 0;
}