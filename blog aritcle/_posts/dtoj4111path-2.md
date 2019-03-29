---
title: " DTOJ4111path\t\t"
tags:
  - 奇技淫巧
  - 最短路
  - 期望
url: 6303.html
id: 6303
categories:
  - DTOJ
  - Solution
date: 2019-02-01 20:18:57
---

和[DTOJ3618Gambling Guide](http://www.dtenomde.com/author=jiangyutong/article=5941/)类似。 测试前不久刚写233 记$f\[i\]$为从第$i$个点出发，走到第$n$个点的期望时间。 那么我们可以列出方程 $$ f\[i\]=\\frac{\\sum_{i\\rightarrow j}\\min(f\[i\],f\[j\])+(m-deg\_i)f\[i\]}{m}+1 $$ 其中$deg\_i$表示点$i$的度数。 我们用堆优化Dijkstra来转移dp。 当前堆顶为$x$，$y$是与$x$相邻的一个点，且$f\[x\]<f\[y\]$。 如果$f\[y\]$是第一次被更新，那么有 $$ f\[y\]=\\frac{(deg\_y-1)f\[y\]+f\[x\]+(m-deg\_y)f\[y\]}{m}+1 $$ 然后我们解得 $$ f\[y\]=f\[x\]+m $$ 如果$f\[y\]$是第二次被更新，不妨设$f\[y\]$第一次是被$f\[z\]$更新的，那么有 $$ f\[y\]=\\frac{(deg\_y-2)f\[y\]+f\[x\]+f\[z\]+(m-deg\_y)f\[y\]}{m}+1 $$ 可以解得 $$ f\[y\]=\\frac{f\[x\]+f\[z\]+m}{2} $$ 依次类推，我们只要记下当前每个点被更新了多少次即可。 具体细节参考代码。

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
#define inf 1e9
#define eps 1e-9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,ecnt,last\[N\],cnt\[N\];db f\[N\];
struct node
{
	int x;db v;
	friend bool operator<(node t1,node t2) {return t1.v>t2.v;}
}top;
std::priority_queue<node>H;
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
void Dijkstra()
{
	for(int i=1;i<n;i++) f\[i\]=inf;
	H.push({n,0});
	for(int x;!H.empty();)
	{
		top=H.top(),H.pop(),x=top.x;
		if(fabs(f\[x\]-top.v)>eps) continue;
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(f\[x\]<f\[e\[k\].to\])
			{
				if(cnt\[e\[k\].to\]) f\[e\[k\].to\]=(f\[e\[k\].to\]*cnt\[e\[k\].to\]+f\[x\])/(cnt\[e\[k\].to\]+1);
				else f\[e\[k\].to\]=f\[x\]+m;
				cnt\[e\[k\].to\]++,H.push({e\[k\].to,f\[e\[k\].to\]});
			}
	}
}
int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	Dijkstra();
	printf("%.10lf\\n",f\[1\]);
	return 0;
}