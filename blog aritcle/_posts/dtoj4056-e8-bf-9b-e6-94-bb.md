---
title: " DTOJ4056进攻\t\t"
tags:
  - 单调队列
  - 奇技淫巧
  - 容斥
url: 5404.html
id: 5404
categories:
  - DTOJ
  - Solution
date: 2018-12-09 19:31:24
---

这种题肯定要容斥。 我们枚举$K$次都打到的$1\\times 1$的有效区域，假设包含它的合法矩形有$cnt$个，那么方案数就是$cnt^K$。 但这样肯定会算重。 题解给出了一个神奇的容斥方法。 我们枚举$K$次都打到的$1\\times 2,2\\times 1$和$2\\times 2$的有效区域，同样算出包含它的合法矩形的个数$cnt$，方案数同样是$cnt^K$。我们用$1\\times 1$的方案数减去$1 \\times 2$和$2\\times 1$的方案数，再加上$2\\times 2$的方案数即可。 现在的问题就是如何求出$cnt$。 先考虑求$1\\times 1$的，即求出包含位置$(x,y)$的矩形个数。 一个合法的矩形，会对矩形内的每个位置造成$+1$的贡献。二维差分后，就变成了在左上角和右下角$+1$，左下角和右上角$-1$。 那么我们就是要求以每个点为左上/左下/右上/右下角的矩形个数。 可以用单调栈求出。具体参考代码。 对于$1\\times 2,2\\times 1$和$2\\times 2$的情况，区别只是在于一个合法的矩形不是给矩形内的每个位置贡献$1$，而是会少掉一行一列。 在计算前缀和的时候错开一下即可。具体参考代码。

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
#define N 2005
#define mod 998244353
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K,L\[N\]\[N\],R\[N\]\[N\],A\[N\]\[N\],B\[N\]\[N\],C\[N\]\[N\],D\[N\]\[N\],Sum\[N\]\[N\],sta\[N\],top;
char s\[N\]\[N\];
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
int Solve(int x,int y)
{
	int res=0;ll tmp;x--,y--;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			tmp=(ll)Sum\[i-1\]\[j\]+Sum\[i\]\[j-1\]-Sum\[i-1\]\[j-1\]+A\[i\]\[j\]-B\[i+x\]\[j\]-C\[i\]\[j+y\]+D\[i+x\]\[j+y\];
			Sum\[i\]\[j\]=cal(tmp%mod+mod),res=cal(res+Pow(Sum\[i\]\[j\],K));
		}
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++) scanf("%s",s\[i\]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) L\[i\]\[j\]=s\[i\]\[j\]-48?L\[i\]\[j-1\]+1:0;
		for(int j=m;j;j--) R\[i\]\[j\]=s\[i\]\[j\]-48?R\[i\]\[j+1\]+1:0;
	}
	for(int j=1,res;j<=m;j++)
	{
		sta\[top=1\]=n+1,res=0;
		for(int i=n;i;i--)
		{
			for(;top&&R\[i\]\[j\]<R\[sta\[top\]\]\[j\];top--) res-=(sta\[top-1\]-sta\[top\])*R\[sta\[top\]\]\[j\];
			res+=(sta\[top\]-i)*R\[i\]\[j\],sta\[++top\]=i,A\[i\]\[j\]=res;
		}
		sta\[top=1\]=res=0;
		for(int i=1;i<=n;i++)
		{
			for(;top&&R\[i\]\[j\]<R\[sta\[top\]\]\[j\];top--) res-=(sta\[top\]-sta\[top-1\])*R\[sta\[top\]\]\[j\];
			res+=(i-sta\[top\])*R\[i\]\[j\],sta\[++top\]=i,B\[i\]\[j\]=res;
		}
		sta\[top=1\]=n+1,res=0;
		for(int i=n;i;i--)
		{
			for(;top&&L\[i\]\[j\]<L\[sta\[top\]\]\[j\];top--) res-=(sta\[top-1\]-sta\[top\])*L\[sta\[top\]\]\[j\];
			res+=(sta\[top\]-i)*L\[i\]\[j\],sta\[++top\]=i,C\[i\]\[j\]=res;
		}
		sta\[top=1\]=res=0;
		for(int i=1;i<=n;i++)
		{
			for(;top&&L\[i\]\[j\]<L\[sta\[top\]\]\[j\];top--) res-=(sta\[top\]-sta\[top-1\])*L\[sta\[top\]\]\[j\];
			res+=(i-sta\[top\])*L\[i\]\[j\],sta\[++top\]=i,D\[i\]\[j\]=res;
		}
	}
	printf("%d\\n",cal(((ll)Solve(0,0)+Solve(1,1)-Solve(0,1)-Solve(1,0))%mod+mod));
	return 0;
}