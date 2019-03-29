---
title: " DTOJ4122字符串\t\t"
tags:
  - Link-Cut Tree
  - 后缀自动机
  - 线段树
url: 6650.html
id: 6650
categories:
  - DTOJ
  - Solution
date: 2019-02-24 22:42:27
---

如果$S$是循环串，我们将$S$变成最短的循环节。记新的$S$长度为$n$。 题解中有一个结论： ![](http://www.dtenomde.com/wp-content/uploads/2019/02/6E2A09BD-855F-4DFC-88A4-06F4F4032F6A.jpg) 我们先考虑$l=1$的情况。因为这个结论，当$r\\geq 2n$时，$r$每增加$1$，答案就会增加$n$，因为左端点为$1\\sim n$右端点为$r$的子串与之前所有子串本质不同。 因此当$l=1$时，我们只用求出$r\\leq 2n$的询问的答案即可。 对于$l>1$的情况，显然我们可以将$l,r$一起减掉一个$n$的倍数使得$l\\leq n$。同样地我们只用处理$r<l+2n$的询问即可。 现在我们可以认为$l,r\\leq 3n$了。 考虑不断右移右端点$r$，同时维护$l$为$1\\sim r$时的答案。 对于一个本质不同的子串，我们在它最后一次出现（最靠右）对应的左端点的位置打上$+1$标记，询问时就是一个区间求和了。 考虑如何维护标记。 我们建出后缀自动机，后缀自动机上某个点的$right​$集合表示了这个点表示的子串的所有出现位置。那么一个节点表示的所有子串打的$+1​$标记是一段连续的区间，且区间位置与$right​$集合中的最大值有关。 考虑新加一个字符对$right$集合的最大值的影响。新加的这个点将这个点到根的路径上的所有$right$集合最大值都更新了。 这与LCT中的access操作类似，我们知道，LCT中access的时间复杂度是$\\Theta(n\\log n)$的。 更新$right$集合最大值时我们用线段树在对应区间上加减，就可以维护答案了。 时间复杂度$\\Theta(n\\log ^2 n)$。 具体细节参考代码。

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
#define P 19990213
#define ll long long
#define ull unsigned long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,pos\[N\];ll ans\[N\];
ull ha\[N\],po\[N\];char s\[N\];
struct info{int id,l,r;}A\[N\];
ull askhash(int l,int r) {return ha\[r\]-ha\[l-1\]*po\[r-l+1\];}
bool Judge(int x)
{
	ull h=ha\[x\];
	for(int i=x+1;i<=n;i+=x) if(askhash(i,i+x-1)^h) return 0;
	return 1;
}
class SegmentTree
{
#define lc x<<1
#define rc x<<1|1
#define mid (l+r>>1)
	struct node{int f;ll v;}t\[N<<2\];
public:
	void add(int x,int l,int r,int \_l,int \_r,int v)
	{
		t\[x\].v+=(ll)(min(\_r,r)-max(\_l,l)+1)*v;
		if(\_l<=l&&r<=\_r) return void(t\[x\].f+=v);
		if(\_l<=mid) add(lc,l,mid,\_l,_r,v);
		if(\_r>mid) add(rc,mid+1,r,\_l,_r,v);
	}
	ll ask(int x,int l,int r,int \_l,int \_r,int v=0)
	{
		if(\_l<=l&&r<=\_r) return t\[x\].v+(ll)(r-l+1)*v;
		ll res=0;v+=t\[x\].f;
		if(\_l<=mid) res=ask(lc,l,mid,\_l,_r,v);
		if(\_r>mid) res+=ask(rc,mid+1,r,\_l,_r,v);
		return res;
	}
#undef lc
#undef rc
}T;
class LinkCutTree
{
#define lc t\[x\].son\[0\]
#define rc t\[x\].son\[1\]
#define pa t\[x\].fa
	bool getson(int x) {return t\[t\[x\].fa\].son\[1\]==x;}
	bool isroot(int x) {return t\[pa\].son\[0\]!=x&&t\[pa\].son\[1\]!=x;}
	void pushup(int x)
	{
		t\[x\].Max=t\[x\].mx,t\[x\].Min=t\[x\].mn;
		if(lc) t\[x\].Max=max(t\[x\].Max,t\[lc\].Max),t\[x\].Min=min(t\[x\].Min,t\[lc\].Min);
		if(rc) t\[x\].Max=max(t\[x\].Max,t\[rc\].Max),t\[x\].Min=min(t\[x\].Min,t\[rc\].Min);
	}
	void pushdown(int x) {if(lc) t\[lc\].v=max(t\[lc\].v,t\[x\].v);if(rc) t\[rc\].v=max(t\[rc\].v,t\[x\].v);}
	void update(int x) {if(!isroot(x)) update(pa);pushdown(x);}
	void rotate(int x)
	{
		int y=pa,z=t\[y\].fa,k=getson(x);
		if(!isroot(y)) t\[z\].son\[t\[z\].son\[1\]==y\]=x;
		t\[y\].son\[k\]=t\[x\].son\[!k\],t\[t\[x\].son\[!k\]\].fa=y;
		t\[x\].son\[!k\]=y,t\[y\].fa=x,t\[x\].fa=z;
		pushup(y);
	}
	void splay(int x)
	{
		for(update(x);!isroot(x);rotate(x))
			if(!isroot(pa)) rotate(getson(x)^getson(pa)?x:pa);
		pushup(x);
	}
public:
	struct node{int fa,son\[2\],Max,Min,mx,mn,v;}t\[N<<1\];
	void access(int x,int v)
	{
		int y=0,p;
		for(;x;y=x,x=pa)
		{
			splay(x);
			if(x^1&&t\[x\].v) p=lc?t\[lc\].Min:t\[x\].mn,T.add(1,1,n,t\[x\].v-t\[x\].mx+1,t\[x\].v-p+1,-1);
			t\[rc\].v=t\[x\].v,rc=y,pushup(x);
		}
		t\[y\].v=v,T.add(1,1,n,v-t\[y\].Max+1,v,1);
	}
}LCT;
class SuffixAutomaton
{
	struct node{int fa,mx,ch\[26\];}t\[N<<1\];
public:
	int cntnode,last;
	void insert(int c)
	{
		int x=last,y=++cntnode,od,nw;last=y,t\[y\].mx=t\[x\].mx+1;
		for(;x&&!t\[x\].ch\[c\];x=t\[x\].fa) t\[x\].ch\[c\]=y;
		if(!x) return void(t\[y\].fa=1);
		od=t\[x\].ch\[c\];
		if(t\[od\].mx==t\[x\].mx+1) return void(t\[y\].fa=od);
		t\[nw=++cntnode\]=t\[od\],t\[nw\].mx=t\[x\].mx+1,t\[od\].fa=t\[y\].fa=nw;
		for(;t\[x\].ch\[c\]==od;x=t\[x\].fa) t\[x\].ch\[c\]=nw;
	}
	void Solve()
	{
		for(int i=1;i<=cntnode;i++)
			LCT.t\[i\]={t\[i\].fa,{0,0},t\[i\].mx,t\[t\[i\].fa\].mx+1,t\[i\].mx,t\[t\[i\].fa\].mx+1,0};
	}
}SAM;
int main()
{
	scanf("%s",s+1),n=strlen(s+1),po\[0\]=1;
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&A\[i\].l,&A\[i\].r),A\[i\].id=i;
	for(int i=1;i<=n;i++) ha\[i\]=ha\[i-1\]\*P+s\[i\],po\[i\]=po\[i-1\]\*P;
	for(int i=1;i<n;i++) if(n%i==0&&Judge(i)) {n=i;break;}
	for(int i=1;i<=n;i++) s\[i+n\]=s\[i+n+n\]=s\[i\];
	for(int i=1,v;i<=m;i++)
	{
		v=(A\[i\].l-1)/n*n,A\[i\].l-=v,A\[i\].r-=v;
		if(A\[i\].r>A\[i\].l+n\*2) ans\[i\]=(ll)(A\[i\].r-A\[i\].l-n\*2)\*n,A\[i\].r=A\[i\].l+n\*2; 
	}
	n*=3,SAM.last=SAM.cntnode=1;
	for(int i=1;i<=n;i++) SAM.insert(s\[i\]-97),pos\[i\]=SAM.last;
	SAM.Solve();
	std::sort(A+1,A+1+m,\[\](info t1,info t2){return t1.r<t2.r;});
	for(int i=1,j=1;i<=m;i++)
	{
		for(;j<=min(A\[i\].r,n);j++) LCT.access(pos\[j\],j);
		ans\[A\[i\].id\]+=T.ask(1,1,n,A\[i\].l,A\[i\].r);
	}
	for(int i=1;i<=m;i++) printf("%lld\\n",ans\[i\]);
	return 0;
}