---
title: " DTOJ4184Nephren Runs a Cinema\t\t"
tags:
  - 数学
url: 6853.html
id: 6853
categories:
  - DTOJ
  - Solution
date: 2019-03-07 21:18:36
---

先考虑没有刷卡的人的情况。 我们将$100$元的人看成$-1$，$50$元的人看成$1$，那么就是要求前缀和$\\geq 0$且和$\\in\[L,R\]$的$-1/1$序列个数。 再将问题转化一下。 我们将$1$看成向右走，$-1$看成向上走，那么经过$y=x+1$的路径都不合法。 我们一共要走$n$步，并且终点$(x,y)$要满足$x-y\\in\[L,R\]$。 考虑对于一个合法的终点$(x,y)$，合法的路径数怎么算。 这是一个经典的问题，就不说了，方案数为$\\binom{n}{x}-\\binom{n}{x+1}$。 因为$x-y\\in\[L,R\]$，且$x+y=n$，所以$2x\\in \[L+n,R+n\]$，即$x\\in\\left \[\\left \\lceil \\frac{L+n}{2}\\right \\rceil,\\left \\lfloor \\frac{R+n}{2}\\right \\rfloor \\right\]$。 那么合法的$-1/1$序列个数就是 $$\\sum_{\\left \\lceil \\frac{L+n}{2}\\right \\rceil}^{\\left \\lfloor \\frac{R+n}{2}\\right \\rfloor}\\binom{n}{x}-\\binom{n}{x+1}$$ 即 $$\\binom{n}{\\left \\lceil \\frac{L+n}{2}\\right \\rceil}-\\binom{n}{\\left \\lfloor \\frac{R+n}{2}\\right \\rfloor+1}$$ 现在我们考虑枚举$50$元和$100$元的总人数$i$。 显然这$i$个人和剩下$n-i$个人的方案数是独立的。 那么答案就是 $$\\sum_{i=1}^n\\binom{n}{i}\\cdot \\left (\\binom{i}{\\left \\lceil \\frac{L+i}{2}\\right \\rceil}-\\binom{i}{\\left \\lfloor \\frac{R+i}{2}\\right \\rfloor+1}\\right )$$ 比较麻烦的是模数$p$不是质数，某些数不存在逆元，我们把$p$分解质因数，保留这些质因子在组合数中的幂，这样剩下的数就都有逆元了，可以直接求。 具体细节参考代码。

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
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,a,b,mod,cntp,pri\[N\],isp\[N\],ans;
std::vector<int>S;
ll cal(ll x) {x-=x<mod?0:mod;return x;}
ll Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
void doPrime(int x)
{
	for(int i=2;i<=x;i++)
	{
		if(!isp\[i\]) pri\[++cntp\]=i;
		for(int j=i+i;j<=x;j+=i) isp\[j\]=1;
	}
}
void exgcd(int a,int b,ll &x,ll &y)
{
	if(!b) {x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	ll t=x;x=y,y=t-a/b*y;
}
ll inverse(int v) {ll x,y;exgcd(v,mod,x,y);return cal(x+mod);}
struct info
{
	int cnt\[N\],val;
	void add(int x,int v)
	{
		for(int i:S) for(;x%pri\[i\]==0;x/=pri\[i\],cnt\[i\]+=v);
		if(x>1) val=(ll)val*(v>0?x:inverse(x))%mod;
	}
	ll ask()
	{
		ll res=val;
		if(!res) return res;
		for(int i:S) if(cnt\[i\]) res=res*Pow(pri\[i\],cnt\[i\])%mod;
		return res;
	}
}A,B,C;
int main()
{
	scanf("%d%d%d%d",&n,&mod,&a,&b),doPrime((int)sqrt(mod));
	int tmp=mod;
	for(int i=1;i<=cntp;i++)
		if(tmp%pri\[i\]==0) {S.pb(i);for(;tmp%pri\[i\]==0;tmp/=pri\[i\]);}
	if(tmp>1) pri\[0\]=tmp,S.pb(0);
	A.val=1;
	for(int i=0,v1,v2;i<=n;i++)
	{
		v1=a+i+1>>1,v2=(b+i>>1)+1;
		if(i>=v1&&i-1<(a+i>>1))
		{
			B.val=1;
			for(int j=1;j<=v1;j++) B.add(i-j+1,1),B.add(j,-1);
		}
		else if(i>=v1)
		{
			B.add(i,1);
			if(a+i&1) B.add(v1,-1);else B.add(i-v1,-1);
		}
		if(i>=v2&&i-1<(b+i-1>>1)+1)
		{
			C.val=1;
			for(int j=1;j<=v2;j++) C.add(i-j+1,1),C.add(j,-1);
		}
		else if(i>=v2)
		{
			C.add(i,1);
			if(b+i&1) C.add(i-v2,-1);else C.add(v2,-1);
		}
		ans=cal(ans+A.ask()*cal(B.ask()-C.ask()+mod)%mod);
		if(i<n) A.add(n-i,1),A.add(i+1,-1);
	}
	printf("%d\\n",ans);
	return 0;
}