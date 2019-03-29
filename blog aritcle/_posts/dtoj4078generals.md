---
title: " DTOJ4078generals\t\t"
tags:
  - 倍增
  - 博弈
  - 思路
  - 树形dp
url: 5661.html
id: 5661
categories:
  - DTOJ
  - Solution
date: 2018-12-20 21:36:24
---

考虑这个博弈游戏的最优策略。记$a,b$之间的距离为$d$（边数）。 如果两个人不相遇的话，答案当$k$为奇数时是$1$，偶数时是$0$。 那么如果$k<d$的话，答案就是这样，因为无论如何都无法相遇。 现在考虑如果两个人能相遇，对于先手/后手，是否有更优的策略。 我们先考虑两个人都想要遇到对方的情况，即两个人相向而行。我们要根据$k$和$d$的奇偶性分类讨论。

*   $k$为奇数，$d$为奇数。相遇时答案为$2$，两个人相遇后第一步是后手走。之后先手每一步都跟着后手走，将答案保持在$2$。
*   $k$为偶数，$d$为奇数。相遇时答案为$2$，两个人相遇后第一步是后手走。之后先手每一步都跟着后手走，将答案保持在$2$。最后一步是后手走，最终答案为$0$。
*   $k$为奇数，$d$为偶数。相遇是答案为$1$，两个人相遇后第一步是先手走。之后后手每一步都跟着先手走，将答案保持在$-1$。最后一步是先手走，最终答案为$1$。
*   $k$为偶数，$d$为偶数。相遇时答案为$1$，两个人相遇后第一步是先手走。之后后手每一步都跟着先手走，将答案保持在$-1$。

现在考虑其中一方想要相遇，另一方不想相遇的情况。显然是处于劣势的那方想要跑。 跑的人一定是不会走回头路的，否则就浪费了一次机会，一定不会使答案比相遇的情况优。 我们继续分类讨论。

*   $k$为奇数，$d$为奇数。后手处于劣势。如果后手一开始就跑，而先手一直都追不上后手的话，答案就变成了$1$。如果被追上的话答案一定没有相遇的情况优。
*   $k$为偶数，$d$为奇数。如果其中一方选择跑，而另一方追不上的话，答案还是$0$。如果被追上的话跑的那方肯定劣，因此选择跑没有意义。
*   $k$为奇数，$d$为偶数。后手处于劣势。如果后手跑而先手追不上，答案还是$1$。同样选择跑没有意义。
*   $k$为偶数，$d$为偶数。先手处于劣势。如果先手一开始就跑，而后手一直都追不上先手的话，答案就变成了$0$。如果被追上的话答案一定没有相遇的情况优。

那么就只有$k\\geq d$且$k$和$d$同奇偶的时候我们需要特殊考虑，其他情况都可以$\\Theta(1)$求解。 现在我们把问题转换成了：树上与点$y$距离$\\leq \\left \\lceil \\frac{k}{2}\\right \\rceil$的点不能到达，问从$x$出发是否有长度$\\geq \\left \\lfloor \\frac{k}{2}\\right \\rfloor$的路径。 记$x$到$y$的路径上与$y$距离为$\\leq \\left \\lceil \\frac{k}{2}\\right \\rceil$的点为$z$，仍然考虑分类讨论。 考虑将$x$出发的路径分成两部分：在$x$到$y$路径上的部分（第一部分），和不在$x$到$y$路径上的部分（第二部分）。 记$LCA$为$x,y$的$LCA$。 我们把第一部分分成三种情况：$x$往上一段（未到$LCA$），$x$到$LCA$，从$x$出发跨过$LCA$再往下一段（未到$z$）。 考虑第一部分的每种情况对应的第二部分是什么样的。

*   $x$往上一段。第二部分肯定是往下走，也就是说我们要对于每个点求出往下的最长链，再加上这个点到$x$的距离取$\\max$。 我们考虑用$deep\[a\]+deep\[b\]-2deep\[LCA(a,b)\]$的方式来表示两点之间的距离。也就是说，对于$x$往上一段的某个点$a$，$a$往下能走到的深度最大的点为$b$，我们要求$deep\[b\]-2deep\[a\]$的最大值。 我们预处理出每个点往下能走到的最大和次大深度的点，分别记为$f\[x\]$和$g\[x\]$。 考虑用树上倍增维护最大值。记$A\[x\]\[i\]$为$x$往上走$2^i$步到达到的所有点$x$中，$f\[x\](g\[x\])-2deep\[x\]$的最大值。我们要保证$A\[x\]\[0\]$对应的方案的第一步不能走向$x$，所以预处理的时候要根据情况取$f\[x\]$还是$g\[x\]$。 那么用树上倍增就能求出这一种情况从$x$出发能走的最长路径的长度了。
*   $x$到$LCA$。第二部分就是从$LCA$出发再走一段。从$LCA$往上走的情况可以看成上一种情况，我们从$LCA$开始树上倍增，一直到$1$，就可以求出从$x$出发走到$LCA$再往上走的最长路径的长度。 我们还可以从$LCA$往下走，也就是要求最长链，并且要保证不能走向$x$和$y$所在的子树。因此我们除了预处理出$f\[x\]$和$g\[x\]$，还要预处理出每个点往下走能走到的第三大深度的点，记为$h\[x\]$。 那么这一种情况就被分成两部分解决了。
*   从$x$出发跨过$LCA$再往下一段。那么就是对于$LCA$到$z$的路径上的点（不包括$LCA$和$z$）求出往下的最长链，再加上这个点到$x$的距离取$\\max$。 同样考虑用$deep\[a\]+deep\[b\]-2deep\[LCA(a,b)\]$的方式来表示两点之间的距离。 不同的是，这种情况的$LCA(a,b)$一定是$LCA$，即$LCA(x,y)$。那么我们就只用维护这段路径上的某个点往下能走到的深度最大的点即可。 仍然考虑用树上倍增维护最大值。记$B\[x\]\[i\]$为$x$往上走$2^i$步到达到的所有点$x$中，$f\[x\](g\[x\])$的最大值。还是同样的原因，我们要保证$A\[x\]\[0\]$对应的方案的第一步不能走向$x$，所以预处理的时候要根据情况取$f\[x\]$还是$g\[x\]$。 再写一个树上倍增就能求出这一种情况从$x$出发能走的最长路径的长度了。

根据$z$与$LCA$的位置关系可能某些情况不存在，此时我们就不用考虑不存在的情况了。 当$LCA(x,y)$为$x$或$y$时还会有一些细节。 细节有点多，具体可以参考代码。 这真是一道分讨好题。

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
#define N 200005
#define inf 1e9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,c,ecnt,last\[N\],deep\[N\],fa\[N\]\[20\],f\[N\],g\[N\],h\[N\],F\[N\]\[20\],G\[N\]\[20\],LCA;
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
void dfs(int x,int fath=0)
{
	fa\[x\]\[0\]=fath,f\[x\]=deep\[x\]=deep\[fath\]+1;
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(e\[k\].to^fath)
		{
			dfs(e\[k\].to,x);
			if(f\[e\[k\].to\]>=f\[x\]) h\[x\]=g\[x\],g\[x\]=f\[x\],f\[x\]=f\[e\[k\].to\];
			else if(f\[e\[k\].to\]>=g\[x\]) h\[x\]=g\[x\],g\[x\]=f\[e\[k\].to\];
			else if(f\[e\[k\].to\]>=h\[x\]) h\[x\]=f\[e\[k\].to\];
		}
	for(int k=last\[x\],v;k;k=e\[k\].nex)
		if(e\[k\].to^fath)
			v=f\[x\]^f\[e\[k\].to\]?f\[x\]:g\[x\],F\[e\[k\].to\]\[0\]=v,G\[e\[k\].to\]\[0\]=v-deep\[x\]*2;
}
int asklca(int x,int y)
{
	if(deep\[x\]<deep\[y\]) std::swap(x,y);
	for(int j=19;~j;j--) if(deep\[x\]-(1<<j)>=deep\[y\]) x=fa\[x\]\[j\];
	if(x==y) return x;
	for(int j=19;~j;j--) if(fa\[x\]\[j\]^fa\[y\]\[j\]) x=fa\[x\]\[j\],y=fa\[y\]\[j\];
	return fa\[x\]\[0\];
}
int askfa(int x,int d) {for(int j=19;~j;j--) if(d>>j&1) x=fa\[x\]\[j\];return x;}
int askf(int x,int d)
{
	if(d<=0) return -inf;
	int res=-inf;
	for(int j=19;~j;j--) if(d>>j&1) res=max(res,F\[x\]\[j\]),x=fa\[x\]\[j\];
	return res;
}
int askg(int x,int d)
{
	if(d<=0) return -inf;
	int res=-inf;
	for(int j=19;~j;j--) if(d>>j&1) res=max(res,G\[x\]\[j\]),x=fa\[x\]\[j\];
	return res;
}
int ask(int x,int y,int v)
{
	int tox,toy,tmp,res=0;
	if(x^LCA) res=f\[x\]-deep\[x\];
	if(v<deep\[y\]-deep\[LCA\])
	{
		toy=askfa(y,v),tmp=askf(toy,deep\[toy\]-deep\[LCA\]-1),res=max(res,deep\[x\]+tmp-deep\[LCA\]*2);
		tmp=askg(x,deep\[x\]-deep\[LCA\]-1),res=max(res,deep\[x\]+tmp);
		tmp=askg(LCA,deep\[LCA\]-1),res=max(res,deep\[x\]+tmp);
		if(x^LCA)
		{
			tox=askfa(x,deep\[x\]-deep\[LCA\]-1),toy=askfa(y,deep\[y\]-deep\[LCA\]-1);
			if(f\[LCA\]^max(f\[tox\],f\[toy\])) tmp=f\[LCA\];
			else if(g\[LCA\]^min(f\[tox\],f\[toy\])) tmp=g\[LCA\];
			else tmp=h\[LCA\];
		}
		else toy=askfa(y,deep\[y\]-deep\[LCA\]-1),tmp=f\[LCA\]^f\[toy\]?f\[LCA\]:g\[LCA\];
		res=max(res,deep\[x\]+tmp-deep\[LCA\]*2);
	}
	if(v==deep\[y\]-deep\[LCA\])
		tmp=askg(x,deep\[x\]-deep\[LCA\]-1),res=max(res,deep\[x\]+tmp);
	if(v>deep\[y\]-deep\[LCA\])
		tmp=askg(x,deep\[x\]+deep\[y\]-deep\[LCA\]*2-v-1),res=max(res,deep\[x\]+tmp);
	return res;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	dfs(1);
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++)
		{
			fa\[i\]\[j\]=fa\[fa\[i\]\[j-1\]\]\[j-1\];
			F\[i\]\[j\]=max(F\[i\]\[j-1\],F\[fa\[i\]\[j-1\]\]\[j-1\]);
			G\[i\]\[j\]=max(G\[i\]\[j-1\],G\[fa\[i\]\[j-1\]\]\[j-1\]);
		}
	for(int d,res;m--;)
	{
		scanf("%d%d%d",&a,&b,&c),LCA=asklca(a,b),d=deep\[a\]+deep\[b\]-deep\[LCA\]*2;
		if(d>c) {printf("%d\\n",c&1);continue;}
		if(!(c&1)&&(d&1)) {puts("0");continue;}
		if((c&1)&&!(d&1)) {puts("1");continue;}
		if((c&1)&&(d&1))
		{
			if(d<=(c+1>>1)) {puts("2");continue;}
			res=ask(b,a,c+1>>1);
			if(res>=c>>1) puts("1");else puts("2");
		}
		else
		{
			if(d<=(c>>1)) {puts("-1");continue;}
			res=ask(a,b,c>>1);
			if(res>=c>>1) puts("0");else puts("-1");
		}
	}
	return 0;
}