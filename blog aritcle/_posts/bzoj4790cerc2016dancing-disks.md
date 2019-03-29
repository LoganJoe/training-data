---
title: " BZOJ4790[CERC2016]Dancing Disks\t\t"
tags:
  - 构造
url: 7131.html
id: 7131
categories:
  - DTOJ
  - Solution
date: 2019-03-26 10:41:04
---

神仙构造。 这种方法应该叫多路归并排序。 考虑$2\\times 2$的格子。 $(1,2)$和$(2,1)$可以通过观察$(1,1)$最上方的两个盘子，来达到$2$个盘子的升序/降序。那么$(2,2)$就可以通过$(1,1),(1,2),(2,1)$归并做到$5$个盘子的升序/降序。 到$(6,6)$时，就可以做到$42960$个盘子的有序。 ![](http://www.dtenomde.com/wp-content/uploads/2019/03/20170330165728847.png) 记$Solve(x,y,0/1)$为归并使得$(x,y)$上棋子降序/升序排列的方法。 求$Solve(x,y,0/1)$的时候就先递归调用$Solve(i,j,1/0),(i<x \\space or\\space j<y)$，然后归并合并即可。 具体细节参考代码。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,num\[9\]\[9\],Sum\[9\]\[9\],cnt\[9\]\[9\];
std::stack<int>A\[9\]\[9\];
struct node
{
	int x,y,v;
	friend bool operator<(node t1,node t2) {return t1.v<t2.v;}
}top;
std::priority_queue<node>H;
void move(int lx,int ly,int rx,int ry)
{
	int top=A\[lx\]\[ly\].top();A\[lx\]\[ly\].pop(),A\[rx\]\[ry\].push(top);
	for(;lx<rx;lx++) printf("%d %d D 1\\n",lx,ly);
	for(;ly<ry;ly++) printf("%d %d R 1\\n",lx,ly);
}
void work(int x,int y,int op)
{
	for(int i=1;i<=x;i++)
		for(int j=1;j<=y;j++) if(i<x||j<y)
		{
			cnt\[i\]\[j\]=min((int)A\[i\]\[j\].size(),num\[i\]\[j\]);
			if(cnt\[i\]\[j\]) H.push({i,j,A\[i\]\[j\].top()*op});
		}
	for(int tx,ty;!H.empty();)
	{
		top=H.top(),H.pop(),tx=top.x,ty=top.y,move(tx,ty,x,y);
		if(--cnt\[tx\]\[ty\]) H.push({tx,ty,A\[tx\]\[ty\].top()*op});
	}
}
void Solve(int x,int y,int op)
{
	if(x==1&&y==1) return;
	if(x==1&&y==2||x==2&&y==1)
	{
		if(A\[1\]\[1\].empty()) return;
		int top1=A\[1\]\[1\].top();A\[1\]\[1\].pop();
		if(A\[1\]\[1\].empty()) return printf("1 1 %c 1\\n",x^1?'D':'R'),A\[x\]\[y\].push(top1);
		int top2=A\[1\]\[1\].top();A\[1\]\[1\].pop();
		if((top1>top2)^op) printf("1 1 %c 1\\n1 1 %c 1\\n",x^1?'D':'R',x^1?'D':'R'),A\[x\]\[y\].push(top1),A\[x\]\[y\].push(top2);
		else printf("1 1 %c 2\\n",x^1?'D':'R'),A\[x\]\[y\].push(top2),A\[x\]\[y\].push(top1);
		return;
	}
	for(int i=x;i;i--)
		for(int j=y;j;j--) if(i<x||j<y) Solve(i,j,op^1);
	work(x,y,op?-1:1);
	if(A\[x\]\[y\].empty()) return;
}
int main()
{
	scanf("%d",&n),num\[1\]\[1\]=num\[1\]\[2\]=num\[2\]\[1\]=1;
	for(int i=1,a;i<=n;i++) scanf("%d",&a),A\[1\]\[1\].push(a);
	for(int i=1;i<7;i++)
		for(int j=1;j<7;j++)
		{
			num\[i\]\[j\]+=Sum\[i-1\]\[j\]+Sum\[i\]\[j-1\]-Sum\[i-1\]\[j-1\];
			Sum\[i\]\[j\]=Sum\[i-1\]\[j\]+Sum\[i\]\[j-1\]-Sum\[i-1\]\[j-1\]+num\[i\]\[j\];
		}
	Solve(6,6,0);
	return 0;
}