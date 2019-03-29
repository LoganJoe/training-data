---
title: " BZOJ4316小C的独立集\t\t"
tags:
  - 仙人掌
  - 树形dp
url: 5832.html
id: 5832
categories:
  - BZOJ
  - Solution
date: 2018-12-28 18:35:48
---

显然这是一个在仙人掌上的dp问题。 先考虑在树上的dp。 记$f\[x\]\[0/1\]$为考虑完以$x$为根的子树，其中$x$不选/选最大独立集大小。 那么有 $$f\[x\]\[0\]=\\sum_{x\\rightarrow son}\\max(f\[son\]\[0\],f\[son\]\[1\])$$ $$f\[x\]\[1\]=\\sum_{x\\rightarrow son}f\[son\]\[0\]$$ 其中$son$是$x$的儿子。 那么答案就是$\\max(f\[1\]\[0\],f\[1\]\[1\])$。 考虑有环了要怎么做。 我们照样dfs，在转移$x\\rightarrow son$的边时，如果这条边没有在任何一个环上，我们就直接像上面那样转移。否则我们暂时忽略这条边。 当我们求完$x$的信息后，如果发现$x$是一个环的顶端，那么我们就开始考虑这个环的取法。 挂在环外面的子树不影响环的取法，我们可以把每棵子树的最大独立集大小当作环上的点不选/选的权值。 记这个环的最顶端为$x$，最底端为$y$。 我们考虑$x$选不选。 如果$x$不选的话，那么$y$可选可不选。我们从$y$往上对$y$到$x$这条链上的点单独做dp，同样用$0/1$表示当前点不选/选的最大独立集大小，转移和树形dp是类似的。最后把算出来的独立集大小加进$f\[x\]\[0\]$即可。 如果$x$选的话，那么$y$就一定不能选了。我们还是从$y$往上对$y$到$x$这条链上的点单独做dp，只不过初始时选$y$的贡献要赋成$-\\infty$。最后把算出来的独立集大小加进$f\[x\]\[1\]$即可。 具体参考代码。

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
#define N 60005
#define inf 1e9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,ecnt,last\[N\],fa\[N\],idx,dfn\[N\],low\[N\],f\[N\]\[2\];
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
void Solve(int x,int y)
{
	int f0=0,f1=0,tmp0,tmp1;
	for(int i=y;i^x;i=fa\[i\])
		tmp0=f0,tmp1=f1,f0=max(tmp0+f\[i\]\[0\],tmp1+f\[i\]\[1\]),f1=tmp0+f\[i\]\[0\];
	f\[x\]\[0\]+=f0,f0=0,f1=-inf;
	for(int i=y;i^x;i=fa\[i\])
		tmp0=f0,tmp1=f1,f0=max(tmp0+f\[i\]\[0\],tmp1+f\[i\]\[1\]),f1=tmp0+f\[i\]\[0\];
	f\[x\]\[1\]+=f1;
}
void tarjan(int x,int fath=0)
{
	fa\[x\]=fath,dfn\[x\]=low\[x\]=++idx,f\[x\]\[1\]=1;
	for(int k=last\[x\];k;k=e\[k\].nex)
	{
		if(!dfn\[e\[k\].to\]) tarjan(e\[k\].to,x),low\[x\]=min(low\[x\],low\[e\[k\].to\]);
		else if(e\[k\].to^fath) low\[x\]=min(low\[x\],dfn\[e\[k\].to\]);
		if(low\[e\[k\].to\]>dfn\[x\])
			f\[x\]\[0\]+=max(f\[e\[k\].to\]\[0\],f\[e\[k\].to\]\[1\]),f\[x\]\[1\]+=f\[e\[k\].to\]\[0\];
	}
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(dfn\[e\[k\].to\]>dfn\[x\]&&fa\[e\[k\].to\]^x) Solve(x,e\[k\].to);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	tarjan(1);
	printf("%d\\n",max(f\[1\]\[0\],f\[1\]\[1\]));
	return 0;
}