---
title: " DTOJ4063C\t\t"
tags:
  - 倍增
  - 思路
url: 5449.html
id: 5449
categories:
  - DTOJ
  - Solution
date: 2018-12-12 19:01:28
---

记$f\[i\]\[j\]\[k\]$表示从点$i$往上走$2^j$步的点中，距离$i$的距离$\\& 2^k=2^k$且点权二进制第$k$位为$0$的点数。 对于一次询问$(u,v)$，我们先把所有经过的点的点权和加起来再考虑路径长度的影响。 记$u,v$的最近公共祖先为$LCA$。 我们按位计算路径长度带来的贡献。即枚举路径长度每一位为$1$的情况，然后用$f$算出此时点权这位为$0$的点的个数。 对于$u$到$LCA$上的点这样就解决了。但对于$LCA$到$v$上的点，由于路径是从上往下的，我们还得处理处一个$g\[i\]\[j\]\[k\]$表示从点$i$往上走$2^j$步的点中，距离$i$的第$2^j$个父亲的距离$\\& 2^k=2^k$（也就是到$i$的距离$\\& 2^k=0$）且点权二进制第$k$位为$0$的点数。 由于只能算$v$到$LCA$的点，我们可能会算到深度小于$LCA$的点。我们只需要作差相减即可。具体可以看代码。 预处理$f,g$都可以通过维护根到每个点每位上为$0$的个数来求。但这样是$\\Theta(n\\log^2 n)$的，我们考虑优化。 其实我们并不需要对于每位都存下点的个数，我们只需要存下每位的贡献与点的个数的乘积即可。 也就是说，记$F\[i\]\[j\]=\\sum_{k}f\[i\]\[j\]\[k\]\\times 2^k,G\[i\]\[j\]=\\sum_{k}g\[i\]\[j\]\[k\]\\times 2^k$。这样就可以把所有位的贡献一起算了。 时间复杂度$\\Theta(n\\log n)$。 讲的不是很清楚，具体细节参考代码。

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
int n,m,a,b,A\[N\],ecnt,last\[N\],deep\[N\],fa\[N\]\[20\],cnt\[N\]\[20\];ll f\[N\]\[20\],g\[N\]\[20\];
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
void dfs(int x,int fath=0)
{
	deep\[x\]=deep\[fath\]+1,fa\[x\]\[0\]=fath;
	for(int i=0;i<20;i++) cnt\[x\]\[i\]=cnt\[fath\]\[i\]+(A\[x\]>>i&1^1);
	for(int k=last\[x\];k;k=e\[k\].nex) if(e\[k\].to^fath) dfs(e\[k\].to,x);
}
int asklca(int x,int y)
{
	if(deep\[x\]<deep\[y\]) std::swap(x,y);
	for(int j=19;~j;j--) if(deep\[x\]-(1<<j)>=deep\[y\]) x=fa\[x\]\[j\];
	if(x==y) return x;
	for(int j=19;~j;j--) if(fa\[x\]\[j\]^fa\[y\]\[j\]) x=fa\[x\]\[j\],y=fa\[y\]\[j\];
	return fa\[x\]\[0\];
}
ll ask1(int x,int y,int d)
{
	ll res=0;
	for(int j=19;~j;j--)
		if(d>>j&1) res+=f\[x\]\[j\]+(1ll<<j)*(cnt\[fa\[x\]\[j\]\]\[j\]-cnt\[y\]\[j\]),x=fa\[x\]\[j\];
	return res;
}
ll ask2(int x,int d)
{
	ll res=0;int y=x;
	for(int j=0;j<20;j++)
		if(d>>j&1) res+=g\[x\]\[j\]+(1ll<<j)*(cnt\[y\]\[j\]-cnt\[x\]\[j\]),x=fa\[x\]\[j\];
	return res;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),f\[i\]\[0\]=g\[i\]\[0\]=A\[i\];
	for(int i=1;i<n;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	dfs(1);
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++)
		{
			fa\[i\]\[j\]=fa\[fa\[i\]\[j-1\]\]\[j-1\];
			f\[i\]\[j\]=f\[i\]\[j-1\]+f\[fa\[i\]\[j-1\]\]\[j-1\]+(1ll<<j-1)*(cnt\[fa\[i\]\[j-1\]\]\[j-1\]-cnt\[fa\[i\]\[j\]\]\[j-1\]);
			g\[i\]\[j\]=g\[i\]\[j-1\]+g\[fa\[i\]\[j-1\]\]\[j-1\]+(1ll<<j-1)*(cnt\[i\]\[j-1\]-cnt\[fa\[i\]\[j-1\]\]\[j-1\]);
		}
	for(int LCA,d;m--;)
	{
		scanf("%d%d",&a,&b),LCA=asklca(a,b),d=deep\[a\]+deep\[b\]-2*deep\[LCA\];
		printf("%lld\\n",ask1(a,LCA,deep\[a\]-deep\[LCA\])+ask2(b,d+1)-ask2(fa\[LCA\]\[0\],deep\[a\]-deep\[LCA\]));
	}
	return 0;
}