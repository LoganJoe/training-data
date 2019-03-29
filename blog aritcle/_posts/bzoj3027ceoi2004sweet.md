---
title: " BZOJ3027[Ceoi2004]Sweet\t\t"
tags:
  - 容斥
url: 6452.html
id: 6452
categories:
  - BZOJ
  - Solution
date: 2019-02-08 22:50:07
---

我们用不超过$b$个的方案数减去不超过$a-1$个的方案数就能得到答案。 考虑如何求出形如不超过$x$个的方案数。 假如每个糖果罐里有无限个糖果，那么方案数就是将$x$个球放入$n+1$个盒子里（盒子可为空）的方案数，即$\\binom{x+n}{n}$。 但每个糖果罐有数量限制，因此我们考虑容斥。即用至少$0$个超过限制的方案数-至少$1$个超过限制的方案数+至少$2$个超过限制的方案数…… 对于至少$i$个超过限制的方案数，我们枚举超过限制的是哪些糖果罐，然后强制这些糖果罐超过限制，其他的随便取即可。 有一个问题是，这题组合数的范围很大，模数又不是质数，要怎么办呢？难道要用中国剩余定理？ 虽然组合数的范围很大，但是都是$\\binom{k+n}{n}$的形式，而$n$很小。 然后就有一种神奇的方法。 $$ \\binom{k+n}{n}\\% 2004=\\frac{\\sum_{i=0}^{n-1}(k+n-i)\\%(2004\\cdot n!)}{n!} $$ 每次$\\Theta(n)$即可。 为什么呢？我们只需证明$\\frac{a}{b}\\% m=\\frac{a \\% bm}{b}$。

> 设$\\frac{a}{b}\\% m =c$，那么有$\\frac{a}{b}=k\\cdot m+c$，即$a=k\\cdot bm+bc$。 所以$a\\%bm =bc$，即$c=\\frac{a\\% bm}{b}$。

具体细节参考代码。

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
#define mod 2004
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,a,b,A\[15\],MaxS,fac;ll mo;
int cal(int x) {x-=x<mod?0:mod;return x;}
int C(int x,int y)
{
	ll res=1;
	for(int i=1;i<=y;i++) res=res*(x-i+1)%mo;
	return res/fac;
}
int Solve(int x)
{
	int Sum,cnt,res=0;
	for(int i=0;i<=MaxS;i++)
	{
		Sum=cnt=0;
		for(int j=1;j<=n;j++) if(i>>j-1&1) Sum+=A\[j\]+1,cnt++;
		if(Sum>x) continue;
		res=cnt&1?cal(res-C(x-Sum+n,n)+mod):cal(res+C(x-Sum+n,n));
	}
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&a,&b),MaxS=(1<<n)-1,fac=1;
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),fac*=i;
	mo=(ll)fac*mod;
	printf("%d\\n",cal(Solve(b)-Solve(a-1)+mod));
	return 0;
}