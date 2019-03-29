---
title: " Codeforces Round #539 (Div. 1)（Codeforces1109）\t\t"
tags:
  - prufer序列
  - 二分
  - 思路
  - 数学
  - 线段树
url: 7056.html
id: 7056
categories:
  - Codeforces
  - Solution
date: 2019-03-17 22:38:51
---

[A:Sasha and a Bit of Relax](https://codeforces.com/contest/1109/problem/A)
---------------------------------------------------------------------------

### 题意

有一个长度为$n$的数组，问有多少个长度为偶数的连续区间，使得其前一半的异或和等于后一半的异或和。

### 题解

记前$i$个数的异或和为$Xor\_i$。那么我们就是要求有多少对奇偶性不同的$l,r$，使得$Xor\_r\\oplus Xor_{mid}=Xor_{mid}\\oplus Xor\_l$。 其中$mid=\\left \\lfloor \\frac {l+r}{2}\\right \\rfloor$，$\\oplus$表示异或。 两边同时异或$Xor\_{mid}$，就变成了$Xor\_l=Xor\_r$。 从小到大枚举$r$，同时开个数组记下前面所有奇数/偶数位置中每种$Xor$值出现了几次即可。  

[B:Sasha and One More Name](https://codeforces.com/contest/1109/problem/B)
--------------------------------------------------------------------------

### 题意

将一个长度为$n$的回文串切成若干份，并重组成一个和原串不同的回文串。求最少切几次。

### 题解

原串已经是回文了，因此答案只可能是无解和$1,2$。 无解的情况就是所有位都相同，或者$n$为奇数且除了最中间位都相同。 $1$的话我们可以暴力枚举切在哪，然后判断是否可行。 剩下的情况就都是$2$了。  

[C:Sasha and a Patient Friend](https://codeforces.com/contest/1109/problem/C)
-----------------------------------------------------------------------------

### 题意

有一个碗和一个水龙头。有三种事件。 一是在$t$时刻将水龙头的速率调成$v$，若$v>0$则每单位时间往碗里加$v$单位水，若$v<0$则每单位时间从碗里抽$-v$单位水。 二是删除$t$时刻的事件。 三是假设在时刻$l$碗里有$v$单位水，求时刻$r$之前碗里的水第一次为$0$的时刻。

### 题解

以时间为轴建线段树，对于每个节点，维护在这段时间里水相对初始的时候最多减少了多少。 在查询的时候，我们合并出$\[l,r\]$的信息，然后就可以在线段树上二分出答案。 为了合并节点信息，我们还要维护每个节点的水开始变化的时刻、最后一刻变化的速率和最后一刻水的体积。 具体细节参考代码。

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
#define eps 1e-9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,op,a,b,c;ll nowk,nowb;
class SegmentTree
{
#define lc t\[x\].ls
#define rc t\[x\].rs
#define mid (l+r>>1)
	struct node{int ls,rs,t,k;ll Min,b;}t\[N*32\];
	void cover(int x,int y) {int l=lc,r=rc;t\[x\]=t\[y\],lc=l,rc=r;}
	void pushup(int x,int l,int r)
	{
		if(!t\[lc\].t&&!t\[rc\].t) {t\[x\].t=t\[x\].k=t\[x\].Min=t\[x\].b=0;return;}
		if(!t\[lc\].t) return cover(x,rc);
		if(!t\[rc\].t)
		{
			cover(x,lc),t\[x\].b+=(ll)t\[x\].k*(r-mid),t\[x\].Min=min(t\[x\].Min,t\[x\].b);
			return;
		}
		cover(x,lc),t\[x\].b+=(ll)t\[x\].k*(t\[rc\].t-mid),t\[x\].Min=min(t\[x\].Min,t\[x\].b+t\[rc\].Min);
		t\[x\].k=t\[rc\].k,t\[x\].b+=t\[rc\].b,t\[x\].Min=min(t\[x\].Min,t\[x\].b);
	}
public:
	int root,cntnode;
	void change(int &x,int l,int r,int p,int v)
	{
		if(!x) x=++cntnode;
		if(l==r) {t\[x\].t=l,t\[x\].k=v;return;}
		p<=mid?change(lc,l,mid,p,v):change(rc,mid+1,r,p,v);
		pushup(x,l,r);
	}
	void Delete(int x,int l,int r,int p)
	{
		if(l==r) {t\[x\].t=t\[x\].k=t\[x\].Min=t\[x\].b=0;return;}
		p<=mid?Delete(lc,l,mid,p):Delete(rc,mid+1,r,p);
		pushup(x,l,r);
	}
	db ask(int x,int l,int r,int \_l,int \_r)
	{
		if(\_l<=l&&r<=\_r)
		{
			if(t\[x\].t)
			{
				if(nowb+(ll)(t\[x\].t-l+1)\*nowk<=0) return l-1-nowb\*1./nowk;
				if(nowb+(ll)(t\[x\].t-l+1)*nowk+t\[x\].Min<=0)
				{
					db res=ask(lc,l,mid,\_l,\_r);
					if(fabs(res+1)<eps) res=ask(rc,mid+1,r,\_l,\_r);
					return res;
				}
				nowb+=(ll)(t\[x\].t-l+1)*nowk;
				nowk=t\[x\].k,nowb+=t\[x\].b;
				return -1;
			}
			else
			{
				if(nowb+(ll)(r-l+1)\*nowk<=0) return l-1-nowb\*1./nowk;
				else return nowb+=(ll)(r-l+1)*nowk,-1;
			}
		}
		db res=-1;
		if(\_l<=mid) res=ask(lc,l,mid,\_l,_r);
		if(fabs(res+1)<eps&&\_r>mid) res=ask(rc,mid+1,r,\_l,_r);
		return res;
	}
}T;
int main()
{
	for(scanf("%d",&m);m--;)
	{
		scanf("%d%d",&op,&a);
		if(op==1) scanf("%d",&b),T.change(T.root,1,1e9,a,b);
		if(op==2) T.Delete(T.root,1,1e9,a);
		if(op==3)
		{
			scanf("%d%d",&b,&c),nowk=0,nowb=c;
			if(!c) {printf("%d\\n",a);continue;}
			printf("%.6lf\\n",T.ask(T.root,1,1e9,a,b));
		}
	}
	return 0;
}

 

[D:Sasha and Interesting Fact from Graph Theory](https://codeforces.com/contest/1109/problem/D)
-----------------------------------------------------------------------------------------------

### 题意

$n$个点的树，每条边有一个边权，边权范围$\[1,m\]$。 给定$a,b$，问有多少种树满足$a$和$b$之间的路径权值和为$m$。

### 题解

显然$a,b$的取值不影响答案。 枚举$a$到$b$的路径长度$i$（不含$a,b$）。我们要先确定是哪些点及顺序，方案数为$\\binom{n-2}{i}i!$。 考虑这$i+1$条边的权值有多少种可能，相当于将$m$分成$i+1$份，方案数为$\\binom{m-1}{i}$。 再考虑剩下$n-i-2$条边的权值，显然每条边有$m$种可能，总方案数为$m^{n-i-2}$。 现在就只用考虑连成一棵树的问题了。 将图看成两部分：$1$条有$i+2$个点的链和$n-i-2$个单独的点。 根据Prufer序列的性质，共$n$个点的$n-i-1$个块连接成一棵树的方案数为$n^{n-i-3}$。我们还要考虑代表链的块是哪个点连出去的，因此还要再$\\times (i+2)$。 综上所述，答案为 $$(n-2)!\\binom{m-1}{n-2}+\\sum_{i=0}^{n-3}\\binom{n-2}{i}i!\\binom{m-1}{i}m^{n-i-2}n^{n-i-3}(i+2)$$ 最前面实际上是$i=n-2$的情况，这种情况比较特殊，因为此时图只有一部分了，不用再计算连成一棵树的方案数了。

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
#define N 1000005
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,a,b,fac\[N\],inv\[N\],ans;
int cal(int x) {x-=x<mod?0:mod;return x;}
int C(int x,int y) {return x<y?0:(ll)fac\[x\]\*inv\[y\]%mod\*inv\[x-y\]%mod;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
int main()
{
	scanf("%d%d%d%d",&n,&m,&a,&b);
	fac\[0\]=inv\[0\]=inv\[1\]=1;
	for(int i=1;i<=max(n,m);i++) fac\[i\]=(ll)fac\[i-1\]*i%mod;
	for(int i=2;i<=max(n,m);i++) inv\[i\]=(ll)(mod-mod/i)*inv\[mod%i\]%mod;
	for(int i=2;i<=max(n,m);i++) inv\[i\]=(ll)inv\[i-1\]*inv\[i\]%mod;
	for(int i=0,v;i<=n-2;i++)
	{
		v=(ll)C(n-2,i)\*fac\[i\]%mod\*C(m-1,i)%mod*Pow(m,n-i-2)%mod;
		if(i<n-2) v=(ll)v*(i+2)%mod;
		if(n-i-3>=0) v=(ll)v*Pow(n,n-i-3)%mod;
		ans=cal(ans+v);
	}
	printf("%d\\n",ans);
	return 0;
}

 

[E:Sasha and a Very Easy Test](https://codeforces.com/contest/1109/problem/E)
-----------------------------------------------------------------------------

### 题意

给定$mod$，维护一个序列，要支持模$mod$的意义下区间乘，单点除和区间求和。保证除完一定是整数。

### 题解

问题在于如何做除法，要除的数可能没有逆元。 没有逆元的数都是和$mod$不互质的数。考虑将$mod$质因数分解，然后维护每个数这些质因子的次数。 区间乘相当于某些质因子的次数区间加，除就是单点减。 同时我们要维护区间和，乘的时候直接维护即可。 具体细节参考代码。

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
#define pb push_back
//#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
//#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,mod,A\[N\],op,a,b,c,q\[15\],qn,B\[15\];
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
void exgcd(int a,int b,int &x,int &y)
{
	if(!b) {x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	int t=x;x=y,y=t-a/b*y;
}
int inverse(int v)
{
	int x,y;
	exgcd(v,mod,x,y),x=cal(x%mod+mod);
//	dbg1(v),dbg1(x),dbg2((ll)v*x%mod);
	return x;
}
class SegmentTree
{
#define lc x<<1
#define rc x<<1|1
#define mid (l+r>>1)
	struct node{int cnt\[15\],f,f2,v,Sum;}t\[N<<2\];
	void pushup(int x) {t\[x\].Sum=cal(t\[lc\].Sum+t\[rc\].Sum);}
	void pushdown(int x)
	{
		for(int i=1;i<=qn;i++) t\[lc\].cnt\[i\]+=t\[x\].cnt\[i\],t\[rc\].cnt\[i\]+=t\[x\].cnt\[i\],t\[x\].cnt\[i\]=0;
		if(t\[x\].f^1)
		{
			t\[lc\].Sum=(ll)t\[lc\].Sum\*t\[x\].f%mod,t\[rc\].Sum=(ll)t\[rc\].Sum\*t\[x\].f%mod;
			t\[lc\].f=(ll)t\[lc\].f\*t\[x\].f%mod,t\[rc\].f=(ll)t\[rc\].f\*t\[x\].f%mod,t\[x\].f=1;
		}
		if(t\[x\].f2^1)
		{
			t\[lc\].v=(ll)t\[lc\].v\*t\[x\].f2%mod,t\[rc\].v=(ll)t\[rc\].v\*t\[x\].f2%mod;
			t\[lc\].f2=(ll)t\[lc\].f2\*t\[x\].f2%mod,t\[rc\].f2=(ll)t\[rc\].f2\*t\[x\].f2%mod,t\[x\].f2=1;
		}
	}
public:
	void build(int x,int l,int r)
	{
		t\[x\].f=t\[x\].f2=1;
		if(l==r)
		{
			int tmp=A\[l\];t\[x\].Sum=A\[l\]%mod;
			for(int i=1;i<=qn;i++)
				for(;tmp%q\[i\]==0;tmp/=q\[i\]) t\[x\].cnt\[i\]++;
			t\[x\].v=tmp%mod;
			return;
		}
		build(lc,l,mid),build(rc,mid+1,r);
		pushup(x);
	}
	void multiply(int x,int l,int r,int \_l,int \_r,int v1,int v2)
	{
		if(\_l<=l&&r<=\_r)
		{
			t\[x\].Sum=(ll)t\[x\].Sum\*v1%mod,t\[x\].f=(ll)t\[x\].f\*v1%mod;
			t\[x\].v=(ll)t\[x\].v\*v2%mod,t\[x\].f2=(ll)t\[x\].f2\*v2%mod;
			for(int i=1;i<=qn;i++) t\[x\].cnt\[i\]+=B\[i\];
			return;
		}
		pushdown(x);
		if(\_l<=mid) multiply(lc,l,mid,\_l,_r,v1,v2);
		if(\_r>mid) multiply(rc,mid+1,r,\_l,_r,v1,v2);
		pushup(x);
	}
	void divide(int x,int l,int r,int p,int v)
	{
		if(l==r)
		{
			int inv=inverse(v);
			t\[x\].v=(ll)t\[x\].v*inv%mod,t\[x\].Sum=t\[x\].v;
			for(int i=1;i<=qn;i++) t\[x\].cnt\[i\]-=B\[i\],t\[x\].Sum=(ll)t\[x\].Sum*Pow(q\[i\],t\[x\].cnt\[i\])%mod;
			return;
		}
		pushdown(x);
		p<=mid?divide(lc,l,mid,p,v):divide(rc,mid+1,r,p,v);
		pushup(x); 
	}
	int ask(int x,int l,int r,int \_l,int \_r)
	{
		if(\_l<=l&&r<=\_r) return t\[x\].Sum;
		pushdown(x);int res=0;
		if(\_l<=mid) res=ask(lc,l,mid,\_l,_r);
		if(\_r>mid) res=cal(res+ask(rc,mid+1,r,\_l,_r));
		return res;
	}
}T;
int main()
{
	scanf("%d%d",&n,&mod);
	int tmp=mod;
	for(int i=2;i*i<=tmp;i++) if(tmp%i==0)
		for(q\[++qn\]=i;tmp%i==0;tmp/=i);
	if(tmp>1) q\[++qn\]=tmp;
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]);
	T.build(1,1,n);
	for(scanf("%d",&m);m--;)
	{
		scanf("%d%d%d",&op,&a,&b);
		if(op==1)
		{
			scanf("%d",&c),tmp=c;
			for(int i=1;i<=qn;i++)
				for(B\[i\]=0;tmp%q\[i\]==0;tmp/=q\[i\]) B\[i\]++;
			T.multiply(1,1,n,a,b,c,tmp);
		}
		if(op==2)
		{
			tmp=b;
			for(int i=1;i<=qn;i++)
				for(B\[i\]=0;tmp%q\[i\]==0;tmp/=q\[i\]) B\[i\]++;
			T.divide(1,1,n,a,tmp);
		}
		if(op==3) printf("%d\\n",T.ask(1,1,n,a,b));
	}
	return 0;
}

 

[F:Sasha and Algorithm of Silence's Sounds](https://codeforces.com/contest/1109/problem/F)
------------------------------------------------------------------------------------------

（没写，留坑）

### 题意

### 题解