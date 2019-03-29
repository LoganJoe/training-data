---
title: " BZOJ1563[NOI2009]诗人小G\t\t"
tags:
  - dp
  - 决策单调性
url: 6338.html
id: 6338
categories:
  - BZOJ
  - Solution
  - 不会证
date: 2019-02-05 17:32:16
---

考虑dp。 记$f\[i\]$为对前$i$个句子进行排版的最小不和谐度。 枚举哪些句子在最后一行，有 $$ f\[i\]=\\min_{j=0}^{i-1}\\{f\[j\]+(Sum\[i\]-Sum\[j\]+i-j-1-L)^P\\} $$ 其中，$Sum\[i\]$为前$i$个句子的长度总和。 这样是$\\Theta(n^2)$的。我们肯定要优化转移。 但这个$P$次方让人很头疼，我们总不能用二项式定理展开吧。 当$P=2$时是BZOJ1010，这时候转移满足决策单调性。 我们感性理解一下（或者打表），无论$P$是多少，都满足决策单调性。 证明的话好像是因为满足四边形不等式，但我不会。 那么我们用一个栈保存决策表。 具体地，栈中的三元组$(l,r,x)$满足$x<l\\leq r$且$f\[l\\sim r\]$的最优转移点都是$x$。 每次求出一个$f\[i\]$后进行弹栈或者将一个三元组分成两个。 具体细节参考代码。 注意会爆long long，要开dp。 时间复杂度$\\Theta(Tn\\log n)$。

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
#define inf 1e18
#define ll long long
#define db long double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int T,n,m,K,A\[N\],Sum\[N\],ql,qr;db f\[N\];char s\[N\];
struct node{int l,r,p;}q\[N\];
db Pow(db x,int y) {x=fabs(x);db res=1;for(;y;x*=x,y>>=1) if(y&1) res*=x;return res;}
db cal(int x,int y) {return f\[x\]+Pow(Sum\[y\]-Sum\[x\]+y-x-1-m,K);}
void Solve()
{
	q\[ql=qr=1\]={1,n,0};
	for(int i=1,l,r,mid;i<=n;i++)
	{
		if(q\[ql\].r<i) ql++;
		f\[i\]=cal(q\[ql\].p,i);
		for(;ql<=qr&&q\[qr\].l>i&&cal(i,q\[qr\].l)<=cal(q\[qr\].p,q\[qr\].l);qr--);
		for(l=max(q\[qr\].l,i),r=q\[qr\].r;l<r;)
			mid=l+r+1>>1,cal(q\[qr\].p,mid)<cal(i,mid)?l=mid:r=mid-1;
		q\[qr\].r=l;
		if(l<n) q\[++qr\]={l+1,n,i};
	}
}
int main()
{
	for(scanf("%d",&T);T--;puts("--------------------"))
	{
		scanf("%d%d%d",&n,&m,&K);
		for(int i=1;i<=n;i++) scanf("%s",s),A\[i\]=strlen(s),Sum\[i\]=Sum\[i-1\]+A\[i\];
		Solve();
		if(f\[n\]>inf) puts("Too hard to arrange");
		else printf("%lld\\n",(ll)(f\[n\]+.5));
	}
	return 0;
}