---
title: " DTOJ4234permutation\t\t"
tags:
  - NTT
  - 倍增
  - 斯特林数
url: 7009.html
id: 7009
categories:
  - DTOJ
  - Solution
date: 2019-03-17 12:03:00
---

弱化版是[DTOJ2577建筑师](http://www.dtenomde.com/author=jiangyutong/article=5108/)。若不知道答案式子请戳进这篇题解。 本题加强了数据范围，因此我们需要更快速的方法求第一类斯特林数。 假设我们要求的是$\\left \[ \\begin{matrix} n \\newline m\\end{matrix} \\right \]$。 除了递推外，第一类斯特林数有分治NTT的$\\Theta(n\\log ^2 n)$的做法。我利用了第一类斯特林数的组合意义推出了一个DP，然后用EGF优化了一下，变成了一个求多项式的幂。利用多项式ln和多项式exp就是$\\Theta(n\\log n)$的。不过常数太大，我没有去尝试…… 这里讲一种常见的$\\Theta(n\\log n)$求第一类斯特林数第一行的做法。 我们知道，$\\left \[ \\begin{matrix} n \\newline m\\end{matrix} \\right \]$等于多项式$f(x)=\\prod\\limits_{i=0}^{n-1}(x+i)$中$x^m​$前的系数。这个可以通过第一类斯特林数的递推式来理解。 这样我们就得到了分治NTT的$\\Theta(n\\log ^2 n)​$的做法。 利用倍增的想法，假设我们已经求出了$f\_n(x)=\\prod \\limits\_{i=0}^{n-1}(x+i)$和$g\_n(x)=\\prod\\limits \_{i=0}^{n-1}(x+n+i)$。这样的话，通过一次$\\Theta(n\\log n)$的NTT，我们就可以求出$f_{2n}(x)=f\_n(x)\\cdot g\_n(x)$。 考虑如何通过$f\_n(x)​$求$g\_n(x)​$。 记$f\_n(x)=\\sum\\limits\_{i=0}^na\_ix^i​$。那么有 $$ \\begin{aligned} g \_ { n } ( x ) & = \\sum _ { i = 0 } ^ { n } a _ { i } ( x + n ) ^ { i } \\\ & = \\sum _ { i = 0 } ^ { n } \\sum _ { j = 0 } ^ { i } a _ { i } \\binom{i}{j} n ^ { i - j } x ^ { j } \\\ & = \\sum_{j=0}^n x^j\\sum_{i=j}^na\_i\\binom{i}{j}n^{i-j}\\\ & = \\sum \_ { j = 0 } ^ { n } x^j \\sum _ { i = j } ^ { n } a _ { i } \\frac { i! } { j!( i - j ) ! } n ^ { i - j }\\\ & = \\sum _ { j = 0 } ^ { n } \\frac { x ^ { i } } { j ! } \\sum _ { i = j } ^ { n } a _ { i }\\cdot i! \\cdot \\frac { n ^ { i - j } } { ( i - j ) ! } \\end{aligned} $$ 看上去就很像卷积，只要将其中一个多项式reverse一下就行了。 具体地，记$A\_i=a\_i\\cdot i!,B\_i=\\frac{n^{n-i}}{(n-i)!}$，我们发现，后面的$\\sum$实际上就是$A$和$B$的卷积左移$n$位。 这样就可以在$\\Theta(n\\log n)$内求出$g\_n(x)$。 初始我们知道$f\_0(x)$，不断倍增就可以求出我们要的$f\_n(x)$。 总时间复杂度就是$T(n)=T(\\frac n 2)+\\Theta(n\\log n)=\\Theta(n\\log n)$。 常数不算很大，0.5s足够跑出来了。 具体细节参考代码。

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
#define N 200005
#define M 270000
#define mod 998244353
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,a,b,fac\[N\],inv\[N\],A\[M\],B\[M\],f\[M\],g\[M\],ans;
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
int C(int x,int y) {return x<y?0:(ll)fac\[x\]\*inv\[y\]%mod\*inv\[x-y\]%mod;}
class NTT
{
	int Rank\[M\],g1,g2,len,l,inv;
	void Prepare(int n)
	{
		for(len=1,l=0;len<=n;len<<=1,l++);
		for(int i=0;i<len;i++) Rank\[i\]=(Rank\[i>>1\]>>1)|((i&1)<<l-1);
		g1=3,g2=332748118,inv=Pow(len,mod-2);
	}
	void dft(int *x,int f)
	{
		for(int i=0;i<len;i++) if(i<Rank\[i\]) std::swap(x\[i\],x\[Rank\[i\]\]);
		for(int i=1;i<len;i<<=1)
			for(int j=0,wn=Pow(f>0?g1:g2,(mod-1)/(i<<1));j<len;j+=i<<1)
				for(int k=0,w=1,tmp;k<i;w=(ll)w*wn%mod,k++)
					tmp=(ll)x\[i+j+k\]*w%mod,x\[i+j+k\]=cal(x\[j+k\]-tmp+mod),x\[j+k\]=cal(x\[j+k\]+tmp);
		if(f<0) for(int i=0;i<len;i++) x\[i\]=(ll)x\[i\]*inv%mod;
	}
public:
	void multiply(int n,int \*x,int m,int \*y)
	{
		Prepare(n+m);
		for(int i=n+1;i<len;i++) x\[i\]=0;
		for(int i=m+1;i<len;i++) y\[i\]=0;
		dft(x,1),dft(y,1);
		for(int i=0;i<len;i++) x\[i\]=(ll)x\[i\]*y\[i\]%mod;
		dft(x,-1);
		for(int i=n+m+1;i<len;i++) x\[i\]=0;
	}
}ntt;
void Solve(int n)
{
	if(n<2) return void(f\[n\]=1);
	int mid=n>>1;Solve(mid);
	for(int i=0,v=1;i<=mid;v=(ll)v\*mid%mod,i++) A\[i\]=(ll)f\[i\]\*fac\[i\]%mod,B\[mid-i\]=(ll)v*inv\[i\]%mod;
	ntt.multiply(mid,A,mid,B);
	for(int i=0;i<=mid;i++) g\[i\]=(ll)A\[mid+i\]*inv\[i\]%mod;
	ntt.multiply(mid,f,mid,g);
	if(n&1) for(int i=n;i;i--) f\[i\]=cal(f\[i-1\]+(ll)f\[i\]*(n-1)%mod);
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	if(a+b-1>n||!a||!b) return puts("0"),0;
	fac\[0\]=inv\[0\]=inv\[1\]=1;
	for(int i=1;i<n;i++) fac\[i\]=(ll)fac\[i-1\]*i%mod;
	for(int i=2;i<n;i++) inv\[i\]=(ll)(mod-mod/i)*inv\[mod%i\]%mod;
	for(int i=2;i<n;i++) inv\[i\]=(ll)inv\[i-1\]*inv\[i\]%mod;
	if(a==1&&b==1) return puts(n>1?"0":"1"),0;
	if(a+b==n+1) return !printf("%d\\n",C(a+b-2,a-1));
	Solve(n-1),ans=(ll)f\[a+b-2\]*C(a+b-2,a-1)%mod;
	printf("%d\\n",ans);
	return 0;
}