---
title: " DTOJ3957The Staging\t\t"
tags:
  - 奇技淫巧
  - 线段树
url: 4546.html
id: 4546
categories:
  - DTOJ
  - Solution
date: 2018-10-25 14:17:32
---

注意题目中有说每个人的目标不同。 每个人的目标是不会改的，如果每个人向目标连一条边，那么每个环都是独立的。我们单独考虑每个环。 先考虑没有修改的情况。 我们将一个环从最先开枪的人那里断开，环就变成了一个序列，我们要处理有多少人活着。 直接求很难求。考虑线段树，从叶子节点的信息推到根节点的信息。 线段树上的节点，我们维护对应区间的左端点的人活/死，右端点的目标活/死以及整段区间活的人数。 这样一个点的信息就可以从左右儿子合并过来了。具体实现细节参考代码。 再考虑如果有修改的情况。 修改这个人对应叶子节点的信息，这个直接改掉即可。但是他还会影响到最先开枪的人，即我们环断开的位置变了。 注意到其实我们环从哪里断开是不影响的，我们只要把线段树上的两段区间拼起来，就可以求出任何人最先开枪的情况了。 那么我们线段树上顺便维护一下每个人开枪时间的最小值，然后从第一个开枪的人那里开始，将线段树上两段区间拼起来得到我们要的信息即可。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 200005 
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,A\[N\],to\[N\],ti\[N\],tp\[N\],tot,cnt,End\[N\],bel\[N\],pos\[N\],pre\[N\],ans\[N\],Ans; 
int qmin(int x,int y) {return x&&y?(ti\[x\]<ti\[y\]?x:y):(x?x:y);}
struct node
{
	int s\[2\],v\[2\],mn;
	void init() {s\[0\]=v\[0\]=v\[1\]=mn=0,s\[1\]=1;}
	friend node operator+(node t1,node t2)
	{
		node res;res.mn=qmin(t1.mn,t2.mn);
		for(int i=0;i<2;i++) res.s\[i\]=t2.s\[t1.s\[i\]\],res.v\[i\]=t1.v\[i\]+t2.v\[t1.s\[i\]\];
		return res;
	}
}t\[N<<2\];
class SegmentTree
{
#define lc x<<1
#define rc x<<1|1
#define mid (l+r>>1)
	void pushup(int x) {t\[x\]=t\[lc\]+t\[rc\];}
public:
	void build(int x,int l,int r)
	{
		if(l==r) {t\[x\].s\[0\]=t\[x\].v\[0\]=1,t\[x\].s\[1\]=ti\[l\]<ti\[pre\[l\]\],t\[x\].mn=l;return;}
		build(lc,l,mid),build(rc,mid+1,r);
		pushup(x);
	}
	void change(int x,int l,int r,int p)
	{
		if(l==r) return void(t\[x\].s\[1\]=ti\[l\]<ti\[pre\[l\]\]);
		p<=mid?change(lc,l,mid,p):change(rc,mid+1,r,p);
		pushup(x);
	}
	int askMin(int x,int l,int r,int \_l,int \_r)
	{
		if(\_l<=l&&r<=\_r) return t\[x\].mn;
		int res=0;
		if(\_l<=mid) res=askMin(lc,l,mid,\_l,_r);
		if(\_r>mid) res=qmin(res,askMin(rc,mid+1,r,\_l,_r));
		return res;
	}
	node ask(int x,int l,int r,int \_l,int \_r)
	{
		if(\_l<=l&&r<=\_r) return t\[x\];
		node res;res.init();
		if(\_l<=mid) res=ask(lc,l,mid,\_l,_r);
		if(\_r>mid) res=res+ask(rc,mid+1,r,\_l,_r);
		return res;
	}
}T;
void Solve(int id)
{
	int l=End\[id-1\]+1,r=End\[id\],p=T.askMin(1,1,n,l,r);
	node res=T.ask(1,1,n,p,r);if(p>l) res=res+T.ask(1,1,n,l,p-1);
	ans\[id\]=res.v\[0\]-res.s\[0\];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&to\[i\]);
	for(int i=1;i<=n;i++) scanf("%d",&ti\[i\]),tp\[i\]=ti\[i\];
	for(int i=1;i<=n;i++)
		if(!pos\[i\])
		{
			tot++;
			for(int j=i;!pos\[j\];j=to\[j\]) A\[pos\[j\]=++cnt\]=j,bel\[j\]=tot,pre\[cnt\]=cnt-1;
			pre\[End\[tot-1\]+1\]=End\[tot\]=cnt;
		}
	for(int i=1;i<=n;i++) ti\[i\]=tp\[A\[i\]\];
	T.build(1,1,n);
	for(int i=1;i<=tot;i++) Solve(i),Ans+=ans\[i\];
	printf("%d\\n",Ans);
	for(scanf("%d",&m);m--;)
	{
		scanf("%d%d",&a,&b),a=pos\[a\],ti\[a\]=b,b=bel\[A\[a\]\];
		T.change(1,1,n,a),T.change(1,1,n,pos\[to\[A\[a\]\]\]);
		Ans-=ans\[b\],Solve(b),Ans+=ans\[b\],printf("%d\\n",Ans);
	}
	return 0;
}