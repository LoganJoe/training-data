---
title: " DTOJ4216车\t\t"
tags:
  - dp
  - 容斥
  - 思路
url: 6824.html
id: 6824
categories:
  - DTOJ
  - Solution
date: 2019-03-04 18:35:53
---

强制某些位置不能放的限制，我们可以容斥，枚举哪些限制没有满足，然后根据奇偶性加/减方案数。 那么问题就变成了，一共有$n$个棋子，有一些位置上一定要有棋子，且每行每列及两条对角线至少有一个棋子的方案数。 由于棋盘大小为$n\\times n$，所以每行每列有且只有一个棋子。我们把每行的棋子所在的列当做一个数，那么合法的方案得到的序列一定是一个长度为$n$的排列。因此我们可以通过保证序列是一个排列来保证每行每列都有一个棋子。 现在考虑如何保证两条对角线都至少有一个棋子。 直接计数比较困难，我们仍然考虑容斥，用所有方案-至少一条对角线没有棋子的方案数+两条对角线都没有棋子的方案数。 所有方案很好统计，若还剩下$k$行没有棋子，方案数就是$k!$。 考虑至少一条对角线没有棋子的方案数。 直接计数仍然很困难，我们可以用所有方案-至少有一个棋子的方案数+至少有两个棋子的方案数-至少有三个棋子的方案数…… 假如还剩下$k$行没有棋子，其中对角线上有$cnt$个位置可以放棋子，那么一条对角线上没有棋子的方案数就是 $$\\sum_{i=0}^{cnt}(-1)^i\\binom{cnt}{i}(k-i)!$$ 注意两条对角线的方案数是不同的，要分别求一遍。 考虑两条对角线都没有棋子的方案数。 仍然考虑容斥。 但是强制对角线上有棋子的方案数不再是组合数了。 我们发现，对于$i\\leq \\left \\lfloor \\frac{n}{2}\\right \\rfloor$，$(i,i),(i,n-1-i),(n-1-i,i),(n-1-i,n-1-i)$这四个格子是否能放棋子是相互制约的。 我们考虑第$i$行、第$n-1-i$行以及第$i$列、第$n-1-i$列中哪些是还没有棋子的，这样就可以求出这四个格子中放$1/2$个棋子的方案数。 然后我们再做一个背包，就可以求出两条对角线上放$i$个棋子的方案数$f\[i\]$。 仍然假设还剩下$k$行没有棋子，那么两条对角线上都没有棋子的方案数就是 $$\\sum_{i=0}^{k}(-1)^i f\[i\](k-i)!$$ 时间复杂度$\\Theta(2^mn^2)$，不是很满。 具体细节参考代码。

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
#define N 105
#define mod 10007 
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int T,n,m,A\[N\],B\[N\],fac\[N\],inv\[N\],mark\[N\],mark1\[N\],mark2\[N\],f\[N\],g\[5\],ans;
int cal(int x) {x-=x<mod?0:mod;return x;}
int C(int x,int y) {return (ll)fac\[x\]\*inv\[y\]%mod\*inv\[x-y\]%mod;}
bool Judge(int x,int y) {return !mark1\[x\]&&!mark2\[y\];}
int Solve1(int x,int op)
{
	int res=0,cnt=0;
	for(int i=1;i<=n;i++) cnt+=op?Judge(i,i):Judge(i,n+1-i);
	for(int i=0,v;i<=cnt;i++)
		v=(ll)C(cnt,i)*fac\[x-i\]%mod,res=i&1?cal(res-v+mod):cal(res+v);
	return res;
}
int Solve2(int x)
{
	for(int i=0;i<=x;i++) f\[i\]=0;f\[0\]=1;
	if(n&1) f\[1\]=Judge(n+1>>1,n+1>>1);
	for(int i=1,v,Sum=n&1;i+i<=n;i++)
	{
		v=Judge(i,i)+Judge(i,n+1-i)+Judge(n+1-i,i)+Judge(n+1-i,n+1-i),g\[1\]=v;
		v=(Judge(i,i)&&Judge(n+1-i,n+1-i))+(Judge(i,n+1-i)&&Judge(n+1-i,i)),g\[2\]=v;
		for(int j=Sum;~j;j--)
		{
			if(g\[1\]) f\[j+1\]=cal(f\[j+1\]+(ll)f\[j\]*g\[1\]%mod);
			if(g\[2\]) f\[j+2\]=cal(f\[j+2\]+(ll)f\[j\]*g\[2\]%mod);
		}
		if(g\[2\]) Sum+=2;else if(g\[1\]) Sum++;
	}
	int res=0;
	for(int i=0,v;i<=x;i++)
		if(f\[i\]) v=(ll)f\[i\]*fac\[x-i\]%mod,res=i&1?cal(res-v+mod):cal(res+v);
	return res;
}
int Solve(int x)
{
	int res=0,flag1=0,flag2=0;
	for(int i=1;i<=m;i++) if(mark\[i\])
	{
		if(A\[i\]==B\[i\]) flag1=1;
		if(A\[i\]+B\[i\]==n+1) flag2=1;
	}
	if(flag1&&flag2) return fac\[x\];
	if(flag1) return cal(fac\[x\]-Solve1(x,0)+mod);
	if(flag2) return cal(fac\[x\]-Solve1(x,1)+mod);
	res=cal(Solve1(x,0)+Solve1(x,1)),res=cal(fac\[x\]-res+mod);
	return cal(res+Solve2(x));
}
void work(int step,int cnt)
{
	if(step>m)
	{
		int res=Solve(n-cnt);
		if(cnt&1) ans=cal(ans-res+mod);
		else ans=cal(ans+res);
		return;
	}
	work(step+1,cnt);
	if(Judge(A\[step\],B\[step\]))
	{
		mark\[step\]=mark1\[A\[step\]\]=mark2\[B\[step\]\]=1;
		work(step+1,cnt+1);
		mark\[step\]=mark1\[A\[step\]\]=mark2\[B\[step\]\]=0;
	}
}
int main()
{
	fac\[0\]=inv\[0\]=inv\[1\]=1;
	for(int i=1;i<=N-5;i++) fac\[i\]=(ll)fac\[i-1\]*i%mod;
	for(int i=2;i<=N-5;i++) inv\[i\]=(ll)(mod-mod/i)*inv\[mod%i\]%mod;
	for(int i=2;i<=N-5;i++) inv\[i\]=(ll)inv\[i-1\]*inv\[i\]%mod;
	for(scanf("%d",&T);T--;ans=0)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++) scanf("%d%d",&A\[i\],&B\[i\]),A\[i\]++,B\[i\]++;
		work(1,0);
		printf("%d\\n",ans);
	}
	return 0;
}