---
title: " DTOJ3734Circle selection\t\t"
tags:
  - K-D Tree
url: 6743.html
id: 6743
categories:
  - DTOJ
  - Solution
date: 2019-03-03 13:42:26
---

先考虑暴力。 我们将所有圆按半径从大到小排序，相同半径的按编号从小到大排序。 然后我们每次找一个标号最小的且没有被删掉的圆，找到所有和它有交的圆，更新答案，然后把这些圆删掉。 这样时间复杂度是$\\Theta(n^2)$的，瓶颈在于找有交的圆。 我们可以利用K-D Tree优化找圆的过程。 我们拿圆心当点去建K-D Tree。对于K-D Tree上每个点我们维护一下把它子树中所有的圆框住的最小矩形。 找圆时，如果框住当前点子树的矩形和当前的圆没有交，那么这个子树中就一定没有和当前圆有交的圆，我们就不用继续往下找了。 时间复杂度$\\Theta(玄学)$，具体细节参考代码。 好像如果被卡了旋转一下坐标系就好了。

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
#define N 300005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
const db pi=acos(-1),ang=pi*.1,eps=1e-3,sina=sin(ang),cosa=cos(ang);
int n,D,pos\[N\],ans\[N\];
struct point
{
	int id,r;db x,y;
	friend bool operator<(point t1,point t2) {return t1.r>t2.r||t1.r==t2.r&&t1.id<t2.id;}
}p\[N\];
db F(db x) {return x*x;}
bool check(int x,int y)
{
	x=pos\[x\],y=pos\[y\];
	return F(p\[x\].x-p\[y\].x)+F(p\[x\].y-p\[y\].y)<F(p\[x\].r+p\[y\].r)+eps;
}
class KDTree
{
#define lc t\[x\].ls
#define rc t\[x\].rs
#define mid (l+r>>1)
	struct node
	{
		int ls,rs,id,r;db d\[2\],mx\[2\],mn\[2\];
		friend bool operator<(node t1,node t2) {return t1.d\[D\]<t2.d\[D\];}
	}t\[N\];
	void upd(int x,int y)
	{
		for(int i=0;i<2;i++)
			t\[x\].mx\[i\]=max(t\[x\].mx\[i\],t\[y\].mx\[i\]),t\[x\].mn\[i\]=min(t\[x\].mn\[i\],t\[y\].mn\[i\]);
	}
	void pushup(int x)
	{
		db a=t\[x\].d\[0\],b=t\[x\].d\[1\];int v=t\[x\].r;
		t\[x\].mx\[0\]=a+v,t\[x\].mn\[0\]=a-v,t\[x\].mx\[1\]=b+v,t\[x\].mn\[1\]=b-v;
		if(lc) upd(x,lc);if(rc) upd(x,rc);
	}
	bool Judge(int x,int y)
	{
		y=pos\[y\];db a=p\[y\].x,b=p\[y\].y;int v=p\[y\].r;
		if(a+v<t\[x\].mn\[0\]-eps) return 0;
		if(a-v>t\[x\].mx\[0\]+eps) return 0;
		if(b+v<t\[x\].mn\[1\]-eps) return 0;
		if(b-v>t\[x\].mx\[1\]+eps) return 0;
		return 1;
	}
public:
	int root;
	void Prepare()
		{for(int i=1;i<=n;i++) t\[i\].d\[0\]=p\[i\].x,t\[i\].d\[1\]=p\[i\].y,t\[i\].id=p\[i\].id,t\[i\].r=p\[i\].r;}
	void build(int &x,int l,int r,int op)
	{
		if(l>r) return;
		D=op,std::nth_element(t+l,t+mid,t+r+1),x=mid;
		build(lc,l,mid-1,op^1),build(rc,mid+1,r,op^1);
		pushup(x);
	}
	void Solve(int x,int y)
	{
		if(!x||!Judge(x,y)) return;
		if(!ans\[t\[x\].id\]&&check(t\[x\].id,y)) ans\[t\[x\].id\]=y;
		Solve(lc,y),Solve(rc,y);
	}
}T;
int main()
{
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&p\[i\].r),p\[i\].id=i;
		p\[i\].x=cosa\*a-sina\*b,p\[i\].y=sina\*a+cosa\*b;
	}
	T.Prepare(),T.build(T.root,1,n,0);
	std::sort(p+1,p+1+n);
	for(int i=1;i<=n;i++) pos\[p\[i\].id\]=i;
	for(int i=1;i<=n;i++) if(!ans\[p\[i\].id\]) T.Solve(T.root,p\[i\].id);
	for(int i=1;i<=n;i++) printf("%d ",ans\[i\]);puts("");
	return 0;
}