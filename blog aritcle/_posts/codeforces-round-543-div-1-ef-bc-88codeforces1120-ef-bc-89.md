---
title: " Codeforces Round #543 (Div. 1)（Codeforces1120）\t\t"
tags:
  - dp
  - hash
  - 思路
  - 最小生成树
  - 构造
url: 6974.html
id: 6974
categories:
  - Codeforces
  - Solution
date: 2019-03-14 23:40:21
---

[A:Diana and Liana](https://codeforces.com/contest/1120/problem/A)
------------------------------------------------------------------

### 题意

有一个长度为$m$的序列$A$和一个长度为$s$的序列$B$。 序列$A​$合法的条件是，$m\\geq k\\cdot n​$，并且将序列$A​$的前$k\\cdot n​$个数分成$n​$段，每段$k​$个数，至少有一段满足每种数的出现次数都$\\geq ​$这种数在序列$B​$中的出现次数。 你可以删掉序列$A​$中的某些数，请构造出一种使删完后的序列$A​$合法的方案。

### 题解

记$pos\_i$为使区间$\[i,pos\_i\]$满足序列$B$的要求的最小值。显然$pos\_i$随$i$的增加单调不降。 那么我们推推指针就能求出所有的$pos\_i​$。 然后我们枚举$i$，让$\[i,pos\_i\]$中的$k$个数作为一段（满足$B$要求的），那么前面最多能凑出$\\left \\lfloor \\frac{i-1}{k}\\right \\rfloor$段，后面最多能凑出$\\left \\lfloor \\frac{n-pos\_i}{k}\\right \\rfloor$段。 如果总共的段数$\\geq n​$，就找到了一组合法解，随便输出一下方案即可。  

[B:Once in a casino](https://codeforces.com/contest/1120/problem/B)
-------------------------------------------------------------------

### 题意

有两个数字串$A$和$B$，构造出一组操作使$A$变成$B​$。 操作是选择相邻的两位使它们一起$\\pm 1$，并且要满足$9$不能$+1$，$0$不能$-1$，最前面的$1$也不能$-1$。

### 题解

先考虑计算答案的事，再考虑输出方案。 记第$i​$位最后的增量为$x\_i​$，那么要满足 $$ \\begin{cases} a\_1+x\_1=b\_1\\newline a\_2+x\_1+x\_2=b\_2 \\newline a\_3+x\_2+x\_3=b\_3 \\newline …\\newline a_{n-1}+x_{n-2}+x_{n-1}=b_{n-1} \\newline a\_n+x\_{n-1}=b\_n \\end{cases} $$ 一共有$n$个方程，$n-1$个未知数。通过前$n-1$个方程我们可以解出 $$ \\begin{cases} x\_1=b\_1-a\_1\\newline x\_2=b\_2-a\_2-x\_1\\newline x\_3=b\_3-a\_3-x\_2\\newline …\\newline x_{n-1}=b_{n-1}-a_{n-1}-x_{n-2}\\newline \\end{cases} $$ 再检查一下是否满足最后一个方程，不满足即无解。 那么答案就是$\\sum\\limits _{i=1}^{n-1}|x_i|​$。 现在考虑构造方案。 考虑贪心，我们从前往后（从高位到低位）枚举每一位，如果当前位要加就加，要减就减。如果操作不合法的话，一定是当前位要加且下一位为$9$或者当前位要减且下一位为$0$。 不合法的情况我们就递归考虑下一位，回溯的时候再操作一定是合法的。 具体细节还是参考代码吧。

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
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,val\[N\],cnt;ll Sum;char A\[N\],B\[N\];
void Solve(int x,int v)
{
	if(v>0&&A\[x+1\]=='9') Solve(x+1,-1);
	if(v<0&&A\[x+1\]=='0') Solve(x+1,1);
	A\[x\]+=v,A\[x+1\]+=v;
	printf("%d %d\\n",x,v);
	if(++cnt==1e5) exit(0);
}
int main()
{
	scanf("%d%s%s",&n,A+1,B+1),val\[1\]=B\[1\]-A\[1\];
	for(int i=2;i<n;i++) val\[i\]=B\[i\]-A\[i\]-val\[i-1\];
	if(A\[n\]+val\[n-1\]!=B\[n\]) return puts("-1"),0;
	for(int i=1;i<=n;i++) Sum+=abs(val\[i\]);
	printf("%lld\\n",Sum);
	for(int i=1;i<n;i++)
	{
		for(;A\[i\]<B\[i\];) Solve(i,1);
		for(;A\[i\]>B\[i\];) Solve(i,-1);
	}
	return 0;
}

 

[C:Compress String](https://codeforces.com/contest/1120/problem/C)
------------------------------------------------------------------

### 题意

初始有一个空的字符串$S​$。往$S​$最后加一个字符的代价为$a​$，加一个$S​$的子串代价为$b​$。 问让$S​$变成给定字符串的最小代价。

### 题解

考虑dp。 记$f\[i\]$为$S$为给定字符串的前$i$个字符的最小代价。 我们枚举最后一次加的字符串，有 $$ f\[i\]=\\min \\begin{cases} f\[i-1\]+a\\newline f\[j\]+b & \[j+1,i\]在前j位出现过 \\end{cases} $$ 由于$n\\leq 5000​$，因此每次转移我们都可以暴力枚举$j​$，然后只要判断一下$\[j+1,i\]​$有没有出现过即可。 将每个子串hash起来，记下在给定字符串中第一次出现的右端点即可。 这题卡hash！！！不过如果一旦不是子串就break就不会被hack……  

[D:Power Tree](https://codeforces.com/contest/1120/problem/D)
-------------------------------------------------------------

### 题意

给一棵$n$个点的带权树。 Alice和Bob在玩游戏。Alice先购买一些点，代价为点权和。然后Bob放一些整数在某些叶子节点上。接着Alice可以选择一个购买过的点，然后将这个点子树中所有叶子上的数统一加上或减去某个数。 求Alice最终一定能把所有数变成$0$的最小代价。 同时输出所有在最优解中可能被购买的点。

### 题解

将树上的问题通过dfs序转换成序列上的问题。 序列上每个位置都对应着一个叶子节点，值就是Bob所放的值。那么购买点就变成了能对一段区间进行加减操作，要求让序列的数全为$0$的最小代价。 让所有数变成$0$就相当于我们对每个位置都能进行$\\pm 1$的修改。 我们将序列先做一个差分，考虑对差分的每个位置上进行$\\pm 1$的修改，这和原问题是等价的。 对$\[l,r\]$进行区间加减，相当于对差分的第$l$位和第$r+1$位同时操作，也就是说，如果我们能对第$l$位单独$\\pm 1$，也就能对第$r+1$位单独$\\pm 1$，反之同理。 差分的第$n+1$位是无意义的，因此对于形如$\[l,n\]$的区间，相当于差分的第$l$位可以单独$\\pm 1$。 将问题换一下，能对$\[l,r\]$区间加减，就在$l$和$r+1$之间连一条权值为这个区间对应的点的点权。那么最小的代价就是$n+1​$个点的最小生成树。 在最优解中可能被购买的点，就是可能在最小生成树中的边。 求可能在最小生成树中的边就是经典问题了，有多种解法，我所写的是较简单的一种：用Kruskal求最小生成树时将权值相同的边一起做，看看每条边是否能在最小生成树中。 具体细节参考代码。

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
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,A\[N\],a,b,ecnt,last\[N\],idx,vis\[N\],posl\[N\],posr\[N\],fa\[N\],ans\[N\];ll Sum;
struct edge{int id,fr,to,v;}E\[N\];
struct road{int to,nex;}e\[N<<1\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
int find(int x) {return fa\[x\]^x?fa\[x\]=find(fa\[x\]):x;}
void dfs(int x,int fath=0)
{
	int leaf=1;posl\[x\]=n;
	for(int k=last\[x\];k;k=e\[k\].nex)
		if(e\[k\].to^fath)
			dfs(e\[k\].to,x),leaf=0,posl\[x\]=min(posl\[x\],posl\[e\[k\].to\]),posr\[x\]=max(posr\[x\],posr\[e\[k\].to\]);
	if(leaf) vis\[++idx\]=x,posl\[x\]=posr\[x\]=idx;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]);
	for(int i=1;i<n;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	dfs(1);
	for(int i=1;i<=n;i++) E\[i\]={i,posl\[i\]-1,posr\[i\],A\[i\]};
	std::sort(E+1,E+1+n,\[\](edge t1,edge t2){return t1.v<t2.v;});
	for(int i=1;i<=idx;i++) fa\[i\]=i;
	for(int i=1,pre=1,f1,f2;i<=n;i++) if(E\[i\].v^E\[i+1\].v||i==n)
	{
		for(int j=pre;j<=i;j++)
		{
			f1=find(E\[j\].fr),f2=find(E\[j\].to);
			if(f1^f2) ans\[++ans\[0\]\]=E\[j\].id;
		}
		for(int j=pre;j<=i;j++)
		{
			f1=find(E\[j\].fr),f2=find(E\[j\].to);
			if(f1^f2) fa\[f1\]=f2,Sum+=E\[j\].v;
		}
		pre=i+1;
	}
	std::sort(ans+1,ans+1+ans\[0\]);
	printf("%lld %d\\n",Sum,ans\[0\]);
	for(int i=1;i<=ans\[0\];i++) printf("%d ",ans\[i\]);puts("");
	return 0;
}

 

[E:The very same Munchhausen](https://codeforc.es/contest/1120/problem/E)
-------------------------------------------------------------------------

（没写，留坑）

### 题意

### 题解

 

[F:Secret Letters](https://codeforc.es/contest/1120/problem/F)
--------------------------------------------------------------

（没写，留坑）

### 题意

### 题解