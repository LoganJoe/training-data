---
title: " DTOJ4233sequence\t\t"
tags:
  - 线段树
url: 6991.html
id: 6991
categories:
  - DTOJ
  - Solution
date: 2019-03-16 15:59:53
---

考虑区间的与有什么性质。 固定左端点$l$，移动右端点$r$，观察区间与的变化。显然每次发生变化，二进制位上至少有一个$1$变成$0$。由于$a_i<2^{30}$，因此$r$在不断右移的时候，区间与最多变化$30$次。 我们可以离线询问，然后从大到小枚举左端点，同时用数据结构维护右端点在每个位置时的答案。 当左端点左移一位时，多出了一些连续子序列。通过前面的性质我们可以知道，这些连续子序列最多有$30$种不同的与值。 用ST表或者预处理出每个二进制位上为$0$的数第一次出现在哪，就可以求出所有可能的与值。 如果一个连续子序列的与值是$k$的倍数，那么就会给一段区间的答案一起加$1$。我们改成维护差分，就变成了单点加$1$，查询时求区间和。 与值是$k$的倍数的连续子序列一次可能会出现很多，但它们的右端点是连续的一段，因此就变成了区间加$1$。 我们用线段树维护即可。

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
//#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
//#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K,A\[N\],Log\[N\],val\[N\]\[20\],pos\[35\],tp\[35\];ll ans\[N*5\];
struct info{int id,l,r;}B\[N*5\];
int ask(int l,int r) {int t=Log\[r-l+1\];return val\[l\]\[t\]&val\[r-(1<<t)+1\]\[t\];}
class SegmentTree
{
#define lc x<<1
#define rc x<<1|1
#define mid (l+r>>1)
	struct node{ll f,v;}t\[N<<2\];
public:
	void add(int x,int l,int r,int \_l,int \_r,int v)
	{
		t\[x\].v+=(min(\_r,r)-max(\_l,l)+1)*v;
		if(\_l<=l&&r<=\_r) return void(t\[x\].f+=v);
		if(\_l<=mid) add(lc,l,mid,\_l,_r,v);
		if(\_r>mid) add(rc,mid+1,r,\_l,_r,v);
	}
	ll ask(int x,int l,int r,int \_l,int \_r,int v=0)
	{
		if(\_l<=l&&r<=\_r) return t\[x\].v+(ll)v*(r-l+1);
		ll res=0;v+=t\[x\].f;
		if(\_l<=mid) res=ask(lc,l,mid,\_l,_r,v);
		if(\_r>mid) res+=ask(rc,mid+1,r,\_l,_r,v);
		return res;
	}
}T; 
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),val\[i\]\[0\]=A\[i\];
	for(int i=1;i<=m;i++) scanf("%d%d",&B\[i\].l,&B\[i\].r),B\[i\].id=i;
	std::sort(B+1,B+1+m,\[\](info t1,info t2){return t1.l>t2.l;});
	for(int i=2;i<=n;i++) Log\[i\]=Log\[i>>1\]+1;
	for(int j=1;j<20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) val\[i\]\[j\]=val\[i\]\[j-1\]&val\[i+(1<<j-1)\]\[j-1\];
	for(int i=n,v,k=1;i;i--)
	{
		for(int j=0;j<31;j++) if(!(A\[i\]>>j&1)) pos\[j\]=i;
		for(int j=0;j<31;j++) tp\[j\]=pos\[j\];
		std::sort(tp,tp+31);
//		for(int j=0;j<30;j++) if(tp\[j\]) dbg1(i),dbg1(j),dbg2(tp\[j\]);
		for(int j=0,op=0;j<31;j++)
		{
			if(!tp\[j\]||(j&&tp\[j\]==tp\[j-1\])) continue;
			v=ask(i,tp\[j\]);
//			dbg1(i),dbg1(j),dbg1(tp\[j\]),dbg2(v);
			if(v%K&&op==1) T.add(1,1,n,tp\[j\],n,-1),op=-1;
			if(v%K==0&&op^1) T.add(1,1,n,tp\[j\],n,1),op=1;
		}
		for(;k<=m&&B\[k\].l==i;k++) ans\[B\[k\].id\]=T.ask(1,1,n,i,B\[k\].r);
	}
	for(int i=1;i<=m;i++) printf("%lld\\n",ans\[i\]);
	return 0;
}