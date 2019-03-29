---
title: " DTOJ3934Hazard\t\t"
tags:
  - 单调队列
  - 思路
url: 4327.html
id: 4327
categories:
  - DTOJ
  - Solution
date: 2018-10-21 23:12:06
---

记$g=gcd(n,m)$。显然赌博机可以被分成$g$个循环节，每个循环节是某个人可能抽到的项的集合，即$i$和$(i+n-1)\\%m+1$为同一部分。 显然循环节之间是独立的，我们分开考虑。 循环节中的任意一项都可能最先被抽到，那么我们要对于循环节中的每一项，求出以这项开始转一圈中亏损的最大值。还要求出循环节的权值和。 对于亏损的最大值，我们可以将循环节断成序列，然后倍长，用单调队列维护当前最优的位置。 对于一个人，如果他的钱小于等于他开始转一圈中亏损的最大值，那么他肯定还没转到一圈就结束了。如果大于，那么就得看循环节的权值和，如果权值和$\\geq 0$，那么就永远不会结束。否则就是转若干圈后钱小于等于他转一圈亏损的最大值。 如果这个人会输光，我们就得找到他第一个输光的位置。 我们从后往前，对于每个位置求从这个位置开始玩游戏的人的情况，同时维护这些位置的前缀和最早出现的位置。我们就能通过维护的位置来找到往后第一个输光的位置了。 找到位置后算一下游戏轮数即可。 讲的很乱……细节很多……做好写到心态爆炸的准备。建议配合代码食用。

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
#define N 1000005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
#define dbg(x) cerr<<\_\_FUNCTION\_\_<<"() L"<<\_\_LINE\_\_<<" "<<#x"="<<(x)<<"\\n"
int n,m,A\[N\],B\[N\],g,tot,id\[N\],Sum\[N<<1\],Min\[N\],l,r,q\[N<<1\],pos\[N<<2\];
ll ans\[N\],Ans=-1;char s\[N\];
void insert(int id) {for(;l<=r&&Sum\[id\]<=Sum\[q\[r\]\];r--);q\[++r\]=id;}
void Solve(int x,int y)
{
	int Max=-Min\[y\],cnt=0;
	if(Max<=0) return;
	if(Max<A\[x\])
	{
		if(Sum\[tot\]>=0) return;
		cnt=-(A\[x\]-Max)/Sum\[tot\],A\[x\]+=cnt*Sum\[tot\];
		if(Max<A\[x\]) A\[x\]+=Sum\[tot\],cnt++;
	}
	ans\[x\]=(ll)cnt\*n\*tot+(ll)(pos\[Sum\[y-1\]-A\[x\]+tot\*2\]-y)\*n+x;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),ans\[i\]=-1;
	scanf("%d%s",&m,s+1),g=std::__gcd(n,m);
	for(int i=1;i<=m;i++) B\[i\]=s\[i\]^'P'?1:-1;
	for(int i=1;i<=g;i++)
	{
		tot=r=0,l=1;
		for(int j=1,p=i;j<=m/g;j++,p=(p+n-1)%m+1) id\[++tot\]=p;
		for(int j=1;j<=tot;j++) Sum\[j\]=Sum\[j+tot\]=B\[id\[j\]\];
		for(int j=1;j<=tot<<1;j++) Sum\[j\]+=Sum\[j-1\],pos\[Sum\[j\]+tot*2\]=0;
		for(int j=1;j<=tot;j++) insert(j);
		for(int j=1;j<=tot;j++) l+=q\[l\]<j,Min\[j\]=Sum\[q\[l\]\]-Sum\[j-1\],insert(j+tot);
		for(int j=tot<<1;j>tot;j--) pos\[Sum\[j\]+tot*2\]=j;
		for(int j=tot;j;j--)
		{
			pos\[Sum\[j\]+tot*2\]=j;
			for(int p=id\[j\];p<=n;p+=m) Solve(p,j);
		}
	}
	for(int i=1;i<=n;i++) if(~ans\[i\]) Ans=~Ans?min(Ans,ans\[i\]):ans\[i\];
	printf("%lld\\n",Ans);
	return 0;
}