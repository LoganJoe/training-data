---
title: " DTOJ1811E-card\t\t"
tags:
  - 线段树
url: 4797.html
id: 4797
categories:
  - DTOJ
  - Solution
date: 2018-10-30 20:37:09
---

显然每次是在$v\[i\]$最大的位置出奴隶。 那么我们就是要维护最大的$v\[i\]$的位置。 我们每次的更新是使一段区间的值和一个一次函数取$\\max$。因此我们要维护一段区间最上方的一次函数。 我们考虑用线段树维护。用线段树维护一次函数的更新是一个很经典的问题。 对于线段树上的每个节点，我们维护对应区间的最大的一次函数。如果这段区间最大值由两个一次函数组成，我们认为最大的一次函数不存在。 我们每次更新一段区间时，先把新的一次函数和当前节点记录的一次函数比较，如果两者之间没有交点，就取最大的。如果有交点，那么这个节点的最大的一次函数就不存在了，我们就把新的一次函数下放到两个儿子去更新。交点只有一个，因此两个儿子至少有一个是新的一次函数和原来的没有交点的情况，因此每次下放最多经过$\\log n$个区间。 修改就直接查询叶子节点对应的一次函数即可。 时间复杂度$\\Theta(n\\log ^2 n)$。具体实现参考代码。 每次修改的区间范围很大，要先离散化一下。

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
#define N 100005
#define ll long long
#define db double
#define lb(x) std::lower_bound(so+1,so+1+n,x)-so
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
#define dbg(x) cerr<<\_\_FUNCTION\_\_<<"() L"<<\_\_LINE\_\_<<" "<<#x"="<<(x)<<"\\n"
int n,m,so\[N<<1\],cnt;
struct info{int op,l,r,a;ll b;}A\[N\];
class SegmentTree
{
#define lc x<<1
#define rc x<<1|1
#define mid (l+r>>1)
	struct node{int id;ll mx,k,b;}t\[N<<3\];
	ll cal(int x,ll k,ll b) {return k*so\[x\]+b;}
	void update(int x,int l,int r,ll k,ll b)
	{
		ll vl=cal(l,t\[x\].k,t\[x\].b),tl=cal(l,k,b);
		ll vr=cal(r,t\[x\].k,t\[x\].b),tr=cal(r,k,b);
		if(tl<=vl&&tr<=vr) return;
		if(tl>vl&&tr>vr) {t\[x\].k=k,t\[x\].b=b;return;}
		update(lc,l,mid,t\[x\].k,t\[x\].b),update(lc,l,mid,k,b);
		update(rc,mid+1,r,t\[x\].k,t\[x\].b),update(rc,mid+1,r,k,b);
		t\[x\].k=t\[x\].b=0;
	}
	void pushup(int x)
		{t\[lc\].mx>t\[rc\].mx?(t\[x\].mx=t\[lc\].mx,t\[x\].id=t\[lc\].id):(t\[x\].mx=t\[rc\].mx,t\[x\].id=t\[rc\].id);}
	void pushdown(int x,int l,int r)
	{
		if(!t\[x\].k&&!t\[x\].b) return;
		update(lc,l,mid,t\[x\].k,t\[x\].b),update(rc,mid+1,r,t\[x\].k,t\[x\].b);
		t\[x\].k=t\[x\].b=0;
	}
public:
	void build(int x,int l,int r)
		{if(l==r) return void(t\[x\].id=so\[l\]);build(lc,l,mid),build(rc,mid+1,r);}
	void change(int x,int l,int r,int \_l,int \_r,ll k,ll b)
	{
		if(\_l<=l&&r<=\_r) return update(x,l,r,k,b);
		pushdown(x,l,r);
		if(\_l<=mid) change(lc,l,mid,\_l,_r,k,b);
		if(\_r>mid) change(rc,mid+1,r,\_l,_r,k,b);
	}
	void modify(int x,int l,int r,int p)
	{
		if(l==r) return void(t\[x\].mx=cal(l,t\[x\].k,t\[x\].b));
		pushdown(x,l,r);
		p<=mid?modify(lc,l,mid,p):modify(rc,mid+1,r,p);
		pushup(x);
	}
	int ask() {return t\[1\].id?t\[1\].id:1;}
}T;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&A\[i\].op);
		if(A\[i\].op^2)
		{
			scanf("%d%d%d%d",&A\[i\].l,&A\[i\].r,&A\[i\].a,&A\[i\].b);
			A\[i\].b-=(ll)A\[i\].a*A\[i\].l,so\[++cnt\]=A\[i\].l,so\[++cnt\]=A\[i\].r;
		}
		else scanf("%d",&A\[i\].a),so\[++cnt\]=A\[i\].a;
	}
	std::sort(so+1,so+1+cnt);
	n=std::unique(so+1,so+1+cnt)-so-1;
	for(int i=1;i<=m;i++)
		if(A\[i\].op^2) A\[i\].l=lb(A\[i\].l),A\[i\].r=lb(A\[i\].r);else A\[i\].a=lb(A\[i\].a);
	T.build(1,1,n);
	for(int i=1;i<=m;i++)
		if(A\[i\].op^2) T.change(1,1,n,A\[i\].l,A\[i\].r,A\[i\].a,A\[i\].b);
		else T.modify(1,1,n,A\[i\].a),printf("%d\\n",T.ask());
	return 0;
}