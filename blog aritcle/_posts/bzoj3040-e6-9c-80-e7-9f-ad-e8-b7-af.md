---
title: " BZOJ3040最短路\t\t"
tags:
  - 最短路
url: 5934.html
id: 5934
categories:
  - BZOJ
  - Solution
date: 2019-01-01 22:08:23
---

提示已经告诉了你算法。 能不能过就看你了 用堆优化Dijkstra时，更新一个点后我们就会把这个点丢进堆里，这样就造成了一个点会在堆里有很多个，那么时间复杂度就会变成$\\Theta(m\\log m)$。 因此我们需要一种能快速维护修改堆内元素的堆。 比如说配对堆，修改元素是$\\Theta(1)$的。 pb_ds库里有，直接用即可。 具体实现看代码。

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
#include<ext/pb\_ds/priority\_queue.hpp>
using std::cin;using std::cerr;
using std::max;using std::min;
using namespace \_\_gnu\_pbds;
#define N 1000005
#define inf 1e18
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K,a,b,c,rxa,rxb,rya,ryb,mod,ecnt,last\[N\];ll dist\[N\];
struct node
{
	int x;ll v;
	friend bool operator<(node t1,node t2) {return t1.v>t2.v;}
}top;
priority\_queue<node>H;priority\_queue<node>::point_iterator it\[N\];
struct road{int to,v,nex;}e\[N*10\];
void adde(int u,int v,int w) {e\[++ecnt\]=(road){v,w,last\[u\]},last\[u\]=ecnt;}
int cal(int x) {x-=x<mod?0:mod;return x;}
void Dijkstra()
{
	for(int i=1;i<=n;i++) dist\[i\]=inf;
	dist\[1\]=0,it\[1\]=H.push((node){1,0});
	for(int x;!H.empty();)
	{
		top=H.top(),H.pop(),x=top.x;
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(dist\[e\[k\].to\]>dist\[x\]+e\[k\].v)
			{
				dist\[e\[k\].to\]=dist\[x\]+e\[k\].v;
				if(it\[e\[k\].to\]!=0) H.modify(it\[e\[k\].to\],(node){e\[k\].to,dist\[e\[k\].to\]});
				else it\[e\[k\].to\]=H.push((node){e\[k\].to,dist\[e\[k\].to\]});
			}
	}
}
int main()
{
	scanf("%d%d%d%d%d%d%d%d",&n,&m,&K,&rxa,&rxb,&rya,&ryb,&mod);
	for(int i=1,x,y;i<=K;i++)
	{
		a=cal((ll)a\*rxa%mod+rxb),b=cal((ll)b\*rya%mod+ryb);
		x=a%n+1,y=b%n+1;if(x>y) std::swap(x,y);adde(x,y,1e8-100*x);
	}
	for(int i=1;i<=m-K;i++) scanf("%d%d%d",&a,&b,&c),adde(a,b,c);
	Dijkstra();
	printf("%lld\\n",dist\[n\]);
	return 0;
}