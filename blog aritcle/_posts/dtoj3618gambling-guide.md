---
title: " DTOJ3618Gambling Guide\t\t"
tags:
  - 奇技淫巧
  - 最短路
  - 期望
url: 5941.html
id: 5941
categories:
  - DTOJ
  - Solution
date: 2019-01-01 22:49:06
---

记$f\[i\]$为从第$i$个点出发，到达第$n$个点最少的期望花的钱数。 那么我们可以列出方程 $$ f\[i\]=\\frac{\\sum_{i\\rightarrow j}\\min(f\[i\],f\[j\])}{deg\_i}+1 $$ 其中$j$是$i$可以走到的一个点，$deg\_i$是第$i$个点的度数。 接下来就很神奇了。 考虑用堆优化Dijkstra来转移。 初始时令$f\[n\]=0$，其他的$f\[i\]=\\infty$。 假设从堆取出来的点为$x$，相邻的点为$y$，如果有$f\[x\]<f\[y\]$，那么我们就用$f\[x\]$去更新$f\[y\]$。 如果$f\[y\]$是第一次被更新，那么根据方程，有 $$ f\[y\]=\\frac{(deg\_i-1)f\[y\]+f\[x\]}{deg\_y}+1 $$ 可以解得 $$ f\[y\]=f\[x\]+deg\_y $$ 如果$f\[y\]$是第二次被更新，不妨设$f\[y\]$第一次是被$f\[z\]$更新的，那么可以解得 $$ f\[y\]=\\frac{f\[x\]+f\[z\]+deg\_y}{2} $$ 依次类推，我们只要记下当前每个点被更新了多少次即可。 具体细节参考代码。 没有SPJ被卡了差评。

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
#define inf 1e9
#define eps 1e-12
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,ecnt,last\[N\],deg\[N\],cnt\[N\];db f\[N\];
struct node
{
	int x;db v;
	friend bool operator<(node t1,node t2) {return t1.v>t2.v;}
}top;
std::priority_queue<node>H;
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt,deg\[u\]++;}
void Dijkstra()
{
	for(int i=1;i<n;i++) f\[i\]=inf;
	H.push((node){n,0});
	for(int x;!H.empty();)
	{
		top=H.top(),H.pop(),x=top.x;
		if(fabs(f\[x\]-top.v)>eps) continue;
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(f\[e\[k\].to\]-f\[x\]>eps)
			{
				if(cnt\[e\[k\].to\]) f\[e\[k\].to\]=(f\[e\[k\].to\]*cnt\[e\[k\].to\]+f\[x\])/(cnt\[e\[k\].to\]+1);
				else f\[e\[k\].to\]=f\[x\]+deg\[e\[k\].to\];
				cnt\[e\[k\].to\]++,H.push((node){e\[k\].to,f\[e\[k\].to\]});
			}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	Dijkstra();
	printf("%.10lf\\n",f\[1\]);
	return 0;
}