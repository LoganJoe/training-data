---
title: " DTOJ4112per\t\t"
tags:
  - Trie树
  - 思路
  - 构造
  - 贪心
url: 6065.html
id: 6065
categories:
  - DTOJ
  - Solution
date: 2019-01-16 19:16:01
---

全文中的$\\oplus $表示异或。 我们先考虑$\\max_{i=1}^{n-1}a_{p\_i} \\oplus a\_{p_{i+1}}$最小是多少。 我们找到可能被异或出来的最高位，即至少有一对数在这位上不同。记是二进制从低到高第$Max​$位（从$0​$开始）。 那么$\\max_{i=1}^{n-1}a_{p\_i} \\oplus a\_{p_{i+1}}$一定$\\geq 2^{Max}$。 我们将所有数根据第$Max​$位为$0/1​$分成两个部分，分别称为$0​$部和$1​$部。 显然同一部分的数可以随便相邻，因为最大值一定在两个部分的数相邻时取到。 我们要令最大值最小，也就是要从两个部分中分别取一个数，使得它们异或最小。然后我们可以把剩下的数放在这两个数的两侧，就构造出了一组合法的方案。 具体实现可以用Trie树，我们将$0$部的数插入Trie树，对于$1$部的每个数在Trie树上找到最小的异或值。 记这个最小的异或值为$val$。 如果想到这一步是不是觉得自己稳了？！ 然后就发现要字典序最小…… 我们转换一下问题，我们将每个数看成一个点，如果两个数能相邻就在两个点之间连一条边。 那么$0$部和$1$部都是一个团，然后$0$部和$1$部之间有连边。记$0$部和$1$部之间的边数为$tot$。 考虑贪心地构造答案。 考虑如果上一位的数为$a$，这位放$b$是否可行。 首先要保证$a\\oplus b\\leq val$，即$a,b$要么属于同一部分，要么$a\\oplus b=val$。 （注意下文的边和$tot$都是指删掉了和已经填的数相邻的边。） 其次，如果从$b$出发连向另一部分的边，有$tot$条（且$tot\\neq 0$），也就是说$b$是图的割点，并且和$b$同一部分的还有其他点，那么放$b$就是不可行的。 我们可以将填数看作在图上走，如果从$a$走到$b$，那么$b$如果走到另一部分，就再也回不去了。 显然不合法的$b$至多只有一个。 那么$b$只可能是和$a$同一部分中的没用过的最小值或小值，或者是$val\\oplus a$。 我们从小到大试，试到第一个合法的就填。 第一个位置可以枚举要放哪个数，用同样的方法判断即可。 查询边数同样可以使用Trie树，当然其他数据结构也行。维护最小值和次小值可以用set，也可以推指针。 具体细节参考代码。 时间复杂度$\\Theta(n\\log n)$。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 300005
#define inf 2e9
#define ll long long
#define db double
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,Max,A\[N\],B\[9\],Bn,cnt\[35\],val=inf,sz\[2\],mark\[N\],ans\[N\];ll tote;
std::set<int>S\[2\];std::set<int>::iterator it;
struct info
{
	int id,v,f;
	friend bool operator<(info t1,info t2) {return t1.v<t2.v||t1.v==t2.v&&t1.id<t2.id;}
}C\[N\];
class Trie
{
	struct node{int son\[2\],v;}t\[N*32\];
public:
	int root,cntnode;
	void insert(int num,int v)
	{
		t\[1\].v++;
		for(int i=Max,x=root,k;~i;i--)
		{
			k=num>>i&1;
			if(!t\[x\].son\[k\]) t\[x\].son\[k\]=++cntnode;
			x=t\[x\].son\[k\],t\[x\].v+=v;
		}
	}
	int ask(int v)
	{
		int res=0;
		for(int i=Max,x=root,k;~i;i--)
		{
			k=v>>i&1;
			if(t\[x\].son\[k\]) x=t\[x\].son\[k\];
			else x=t\[x\].son\[k^1\],res|=1<<i;
		}
		return res;
	}
	int find(int v)
	{
		int x=root;
		for(int i=Max,k;~i&&x;i--) k=v>>i&1,x=t\[x\].son\[k\];
		return t\[x\].v;
	}
}T;
bool Judge(int id) {int v=T.find(val^A\[id\]);return !v||v<tote||(v==tote&&sz\[A\[id\]>>Max&1\]==1)?1:0;}
int find(int x)
{
	int l=1,r=n,mid;
	for(;l<r;) mid=l+r>>1,C\[mid\].v<x?l=mid+1:r=mid;
	for(r=n;l<r;)
	{
		mid=l+r>>1;
		if(C\[mid\].v>x) r=mid-1;
		else if(mark\[C\[mid\].id\]) l=mid+1;else r=mid;
	}
	return C\[l\].id;
}
int main()
{
	scanf("%d",&n),T.root=T.cntnode=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A\[i\]),C\[i\]={i,A\[i\],0};
		for(int j=0;j<31;j++) cnt\[j\]+=A\[i\]>>j&1;
	}
	std::sort(C+1,C+1+n);
	for(int i=30;~i&&!Max;i--) if(cnt\[i\]&&cnt\[i\]<n) Max=i;
	if(!Max&&cnt\[0\]==n)
	{
		for(int i=1;i<=n;i++) printf("%d ",i);
		return 0;
	}
	for(int i=1;i<=n;i++) if(!(A\[i\]>>Max&1)) T.insert(A\[i\],1),S\[0\].insert(i);
	for(int i=1;i<=n;i++) if(A\[i\]>>Max&1) val=min(val,T.ask(A\[i\])),S\[1\].insert(i);
	sz\[0\]=S\[0\].size(),sz\[1\]=S\[1\].size();
	for(int i:S\[1\]) tote+=T.find(val^A\[i\]),T.insert(A\[i\],1);
	for(int i=1;i<=n&&!ans\[1\];i++) if(Judge(i)) ans\[1\]=i;
	for(int i=2,bel,now,cnt;i<=n;i++)
	{
		now=ans\[i-1\],bel=A\[now\]>>Max&1,mark\[now\]=1;
		S\[bel\].erase(now),sz\[bel\]--,cnt=T.find(val^A\[now\]),tote-=cnt,T.insert(A\[now\],-1);
		Bn=0,it=S\[bel\].begin();
		if(it!=S\[bel\].end()) B\[++Bn\]=*it,it++;
		if(it!=S\[bel\].end()) B\[++Bn\]=*it;
		if(cnt) B\[++Bn\]=find(val^A\[now\]);
		std::sort(B+1,B+1+Bn);
		for(int j=1;j<=Bn&&!ans\[i\];j++) if(Judge(B\[j\])) ans\[i\]=B\[j\];
	}
	for(int i=1;i<=n;i++) printf("%d ",ans\[i\]);
	return 0;
}