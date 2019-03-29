---
title: " BZOJ2090[Poi2010]Monotonicity 2\t\t"
tags:
  - dp
url: 6449.html
id: 6449
categories:
  - BZOJ
  - Solution
  - 不会证
date: 2019-02-08 22:21:00
---

神仙结论题。 记$f\[i\]$为以第$i$位结尾的最长的子序列长度，那么$f\[i\]$一定是从前面某个合法的$f\[j\]$转移过来的。 证明我不会，请看[这](https://blog.csdn.net/Kanosword/article/details/52735717)和[这](http://www.cnblogs.com/dream-maker-yk/p/9840318.html)。 那么随便拿个数据结构维护分$<,>,=$三类维护一下对应的$f\[i\]$的最大值。线段树或者树状数组都行。$=$直接拿数组维护就行了。 时间复杂度$\\Theta(n\\log n)$。 具体细节参考代码。

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
#define N 500005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,Max,A\[N\],B\[N<<1\],f\[N\],ans;char s\[N\];
class BIT
{
	int t\[N<<1\];
public:
	void change(int x,int v) {for(;x<=Max;x+=x&-x) t\[x\]=max(t\[x\],v);}
	int ask(int x) {int res=0;for(;x;x-=x&-x) res=max(res,t\[x\]);return res;}
}B1,B2;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),Max=max(Max,A\[i\]);
	for(int i=1;i<=m;i++) scanf(" %c",&s\[i\]);
	for(int i=1,p;i<=n;i++)
	{
		f\[i\]=max(max(B1.ask(A\[i\]-1),B2.ask(Max-A\[i\])),B\[A\[i\]\])+1;
		ans=max(ans,f\[i\]),p=(f\[i\]-1)%m+1;
		if(s\[p\]=='<') B1.change(A\[i\],f\[i\]);
		if(s\[p\]=='>') B2.change(Max-A\[i\]+1,f\[i\]);
		if(s\[p\]=='=') B\[A\[i\]\]=max(B\[A\[i\]\],f\[i\]);
	}
	printf("%d\\n",ans);
	return 0;
}