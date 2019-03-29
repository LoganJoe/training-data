---
title: " BZOJ5311贞鱼\t\t"
tags:
  - dp
  - 决策单调性
  - 带权二分
url: 6432.html
id: 6432
categories:
  - BZOJ
  - Solution
date: 2019-02-08 16:31:11
---

推荐一个写得很好的[blog](https://blog.csdn.net/Izumi_Hanako/article/details/80275299)。 考虑dp。 记$f\[i\]\[j\]$为前$i$只贞鱼坐$j$辆车的最小怨气值。 枚举最后一辆车坐了哪些贞鱼即可转移。具体地，有 $$ f\[i\]\[j\]=\\min_{k=0}^{i-1}\\{f\[k\]\[j-1\]+cost(k+1,i)\\} $$ 其中$cost(i,j)$表示$i\\sim j$这些贞鱼坐同一辆车产生的怨气值之和。我们预处理出怨气值矩阵的二维前缀和，$cost(i,j)$就可以$\\Theta(1)$计算了。 观察（或者打表）可以发现，这个dp满足决策单调性。对于同一个$i$，$j$增大时，最优转移点是右移的；对于同一个$j$，$i$增大时，最优转移点也是右移的。 因此可以利用决策单调性来优化dp。 时间复杂度$\\Theta(nk\\log n)$。 其实$f\[i\]\[j\]$关于$j$是一个下凸的函数，我们可以用dp凸优化，也叫带权二分。这样就可以把第二维去掉。 然后变成了一个1D1D的dp，利用决策单调性可以做到$\\Theta(n\\log n)$。 总时间复杂度$\\Theta(n\\log n\\log \\sum a_{i,j})$。 辣鸡BZOJ卡常数，要用fread的快读板子才能过。

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
#define N 4005
#define il inline
#define ll long long
#define db double
#define _(d) while(d((ch=gc()-48)>=0&&ch<=9))
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[N\]\[N\],Sum\[N\]\[N\],f\[N\],g\[N\],ql,qr;
struct info{int l,r,p;}q\[N\];
il char gc()
{
	static char buf\[100000\],\*p1,\*p2;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
il int get() {char ch;int v;_(!);v=ch;_()v+=(v<<3)+v+ch;return v;}
il int cal(int x,int y) {return f\[x\]+Sum\[y\]\[y\]-Sum\[x\]\[y\]-Sum\[y\]\[x\]+Sum\[x\]\[x\];}
il void Solve(int x)
{
	q\[ql=qr=1\]={1,n,0};
	for(int i=1,l,r,mid;i<=n;i++)
	{
		if(q\[ql\].r<i) ql++;
		f\[i\]=cal(q\[ql\].p,i)+x,g\[i\]=g\[q\[ql\].p\]+1;
		for(;ql<qr&&q\[qr\].l>i&&cal(i,q\[qr\].l)<=cal(q\[qr\].p,q\[qr\].l);qr--);
		for(l=max(q\[qr\].l,i),r=q\[qr\].r;l<r;)
			mid=l+r+1>>1,cal(i,mid)<=cal(q\[qr\].p,mid)?r=mid-1:l=mid;
		q\[qr\].r=l;if(l<n) q\[++qr\]={l+1,n,i};
	}
}
int main()
{
	n=get(),m=get();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			A\[i\]\[j\]=get();
			if(i>j) A\[i\]\[j\]=0;
			Sum\[i\]\[j\]=Sum\[i-1\]\[j\]+Sum\[i\]\[j-1\]-Sum\[i-1\]\[j-1\]+A\[i\]\[j\];
		}
	int l=0,r=Sum\[n\]\[n\],mid;
	for(;l<r;) mid=l+r+1>>1,Solve(mid),g\[n\]>=m?l=mid:r=mid-1;
	Solve(l);
	printf("%d\\n",f\[n\]-m*l);
	return 0;
}