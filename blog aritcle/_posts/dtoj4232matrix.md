---
title: " DTOJ4232matrix\t\t"
tags:
  - 奇技淫巧
url: 6995.html
id: 6995
categories:
  - DTOJ
  - Solution
date: 2019-03-17 11:26:37
---

考虑用什么方法计算一个子矩阵的价值。对于每个本质不同的行，我们在它第一次出现时给价值$+1$即可。我们可以维护每行前一个和它相同的行在哪，没有则为$0$。 发现部分分中有$n$较小的，也有$m$较小的。 不妨根据$n\\leq m$和$n>m$分成两种情况，分别考虑一种比较优秀的做法。 先考虑$n>m$的情况。 我们枚举子矩阵的左右边界，考虑如何计算上下边界任意的所有子矩阵的价值和。 对于第$i$行我们维护前面第一个和它相同的行的位置，记为$pre\_i$。 那么当上边界在$\[pre\_i+1,i\]$且下边界在$\[i,n\]$时，第$i$行在子矩阵中都是第一次出现，即对子矩阵有$+1$的贡献。那么对子矩阵的价值和就有$(i-pre\_i)(n-i+1)$的贡献。 考虑如何维护$pre\_i$。 固定子矩阵的左边界后，考虑在右边界在不断右移的时候快速更新所有的$pre\_i$。 我们将在当前左右边界下相同的行看成一组，每次更新一组的$pre\_i$。容易发现，当右边界右移一格时，一组会根据新增的字符分裂成若干组。那么我们每次暴力更新一组的$pre\_i$即可。 时间复杂$\\Theta(nm^2)$。 再考虑$n\\leq m$的情况。 现在我们不能一组枚举左右边界了，但是仍然要用到$pre\_i$。 发现$n$较小，而右边界移动的时候，$pre\_i$最多只会有$i$种取值。我们只要维护每种取值会在右端点在什么位置时取到即可。 我们从小到大枚举子矩阵的左边界，同时用指针维护一下任意两行第一个出现不同的位置。这样我们就知道任意两行在什么时候相同了，就很容易求出$pre\_i$了。 时间复杂度$\\Theta(n^2m)$。 若$n,m$同阶，那么复杂度就是$\\Theta(n\\sqrt n)$，由于常数较小，可以卡过去…… 正解是$\\Theta(nm\\log ^2 n)$或$\\Theta(nm\\log n)$的。大概可能是将我$n>m$中用Trie树维护相同的行，同时在Trie树上的结点开set记录行号。从大到小枚举右边界就是合并Trie树，启发式合并就是$\\Theta(nm\\log ^2n)$的。然后将set改成Splay就可以做到$\\Theta(nm\\log n)$。 顺便附上出题人题解。 ![](http://www.dtenomde.com/wp-content/uploads/2019/03/F5643A71-0EAB-46B0-9ECD-9B8EBF20CCEB.jpg)

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
#define N 500005
#define ll long long
#define db double
#define lb(x) std::lower_bound(so+1,so+1+tot,x)-so
//#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
//#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,A\[N\],so\[N\],tot;
int get(int x,int y) {return A\[(x-1)*m+y\];}
namespace Solve1
{
	int tot,val\[N\],last\[N\],mark\[N\],q\[N\];ll ans;
	struct link{int pre,nex;}e\[N\];
	void work(int x,int y)
	{
		int qn=0;
		for(int i=x;i;i=e\[i\].nex) q\[++qn\]=i,mark\[i\]=y;
		for(int i=1;i<=qn;i++) e\[q\[i\]\].pre=e\[q\[i\]\].nex=0;
		for(int i=1,id;i<=qn;i++)
			id=q\[i\],val\[id\]=get(id,y+1),e\[id\].pre=last\[val\[id\]\],e\[e\[id\].pre\].nex=id,last\[val\[id\]\]=id;
		for(int i=1;i<=qn;i++) last\[val\[q\[i\]\]\]=0;
	}
	void Solve(int id)
	{
		for(int i=1;i<=n;i++) val\[i\]=get(i,id),e\[i\].pre=last\[val\[i\]\],e\[e\[i\].pre\].nex=i,last\[val\[i\]\]=i;
		for(int i=1;i<=n;i++) last\[val\[i\]\]=0;
		for(int j=id;j<=m;j++)
		{
			for(int i=1;i<=n;i++) ans+=(ll)(i-e\[i\].pre)*(n-i+1);
			for(int i=1;i<=n;i++) if(mark\[i\]^j) work(i,j);
		}
		for(int i=1;i<=n;i++) e\[i\].pre=e\[i\].nex=mark\[i\]=0;
	}
	void Main()
	{
		for(int i=1;i<=m;i++) Solve(i);
		printf("%lld\\n",ans);
	}
}
namespace Solve2
{
	int pos\[805\]\[805\];ll ans;
	void Solve(int id)
	{
		for(int i=1,now;i<=n;i++)
		{
			now=id-1;
			for(int j=i-1;j;j--)
			{
				if(pos\[i\]\[j\]==id-1)
					for(pos\[i\]\[j\]=id;pos\[i\]\[j\]<=m&&get(i,pos\[i\]\[j\])==get(j,pos\[i\]\[j\]);pos\[i\]\[j\]++);
				if(pos\[i\]\[j\]-1>now) ans+=(ll)(pos\[i\]\[j\]-1-now)*(i-j)*(n-i+1),now=pos\[i\]\[j\]-1; 
			}
			if(now<m) ans+=(ll)(m-now)\*i\*(n-i+1);
		}
	}
	void Main()
	{
		for(int i=1;i<=m;i++) Solve(i);
		printf("%lld\\n",ans);
	}
} 
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;i++) scanf("%d",&A\[i\]),so\[i\]=A\[i\];
	std::sort(so+1,so+1+n\*m),tot=std::unique(so+1,so+1+n\*m)-so-1;
	for(int i=1;i<=n*m;i++) A\[i\]=lb(A\[i\]);
	if(n>m) Solve1::Main();else Solve2::Main(),0;
	return 0;
}