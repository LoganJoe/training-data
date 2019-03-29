---
title: " DTOJ1286体育课\t\t"
tags:
  - 凸包
  - 分块
url: 6795.html
id: 6795
categories:
  - DTOJ
  - Solution
date: 2019-03-03 18:42:16
---

记第$i$个人的身高为$h\_i$，记$a\_i=h\_i-h\_1$，考虑直接维护序列$A$。 先考虑$h_1$不变的情况。 那么就是区间加等差数列和查询区间最大值的问题。 这是一个经典问题，具体做法可以看[这](http://www.dtenomde.com/author=jiangyutong/article=6792/)。 考虑到涉及到$h_1$的操作。 如果是区间加等差数列的操作，那么$>r$的位置都会被$-t$，$\\leq r$的位置从位置$2$开始加首项为$t$，公差为$t$的等差数列。 如果是交换操作，更新一下两个位置的$a$，然后暴力重建一下两块的凸包。 有一点细节，参考代码食用。

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
#define M 1500
#define inf 1e18
#define ll long long
#define db double
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,op,a,b,c,block,bel\[N\],sta\[M\],top;ll K,val,A\[N\],tag1\[M\],tag2\[M\],ans;
std::vector<int>S\[M\];
ll calc(int x) {return A\[x\]+tag1\[bel\[x\]\]*x+tag2\[bel\[x\]\];}
db getk(int x,int y) {return (A\[x\]-A\[y\])*1./(x-y);}
void update(int x)
{
	int l=(x-1)\*block+1,r=min(l+block-1,n);ll v=l\*tag1\[x\]+tag2\[x\]; 
	for(int i=l;i<=r;i++) A\[i\]+=v,v+=tag1\[x\];
	tag1\[x\]=tag2\[x\]=0;
}
void build(int x)
{
	int l=(x-1)*block+1,r=min(l+block-1,n);
	sta\[top=1\]=l;
	for(int i=l+1;i<=r;i++)
	{
		for(;top>1&&getk(sta\[top-1\],sta\[top\])<getk(sta\[top-1\],i);top--);
		sta\[++top\]=i;
	}
	S\[x\].resize(top+1);
	for(int i=1;i<=top;i++) S\[x\]\[i\]=sta\[i\];
}
ll ask(int x)
{
	int l=1,r=S\[x\].size()-1,mid;
	if(l>r) return calc(S\[x\]\[1\]);
	for(;l<r;) mid=l+r>>1,calc(S\[x\]\[mid\])<calc(S\[x\]\[mid+1\])?l=mid+1:r=mid;
	return calc(S\[x\]\[l\]);
}
int main()
{
	scanf("%d%d",&n,&m),block=(int)sqrt(n/3);
	for(int i=1;i<=n;i++) scanf("%lld",&A\[i\]),bel\[i\]=(i-1)/block+1;
	for(int i=2;i<=n;i++) A\[i\]-=A\[1\];
	K=A\[1\],A\[1\]=0;
	for(int i=1;i<=bel\[n\];i++) build(i);
	for(;m--;)
	{
		scanf("%d%d%d",&op,&a,&b);
		if(op==1)
		{
			ans=0;
			if(bel\[a\]^bel\[b\])
			{
				for(int i=a;i<=bel\[a\]*block;i++) ans=max(ans,calc(i));
				for(int i=(bel\[b\]-1)*block+1;i<=b;i++) ans=max(ans,calc(i));
				for(int i=bel\[a\]+1;i<bel\[b\];i++) ans=max(ans,ask(i)); 
			}
			else for(int i=a;i<=b;i++) ans=max(ans,calc(i));
			printf("%lld\\n",ans);
		}
		if(op==2)
		{
			if(a>b) std::swap(a,b);
			update(bel\[a\]);
			if(bel\[a\]^bel\[b\]) update(bel\[b\]);
			std::swap(A\[a\],A\[b\]);
			if(a==1)
			{
				for(int i=1;i<=bel\[n\];i++) tag2\[i\]-=A\[a\];
				K+=A\[a\];
			}
			update(bel\[a\]),build(bel\[a\]);
			if(bel\[a\]^bel\[b\]) update(bel\[b\]),build(bel\[b\]);
		} 
		if(op==3)
		{
			scanf("%d",&c);
			if(a==1)
			{
				K+=c,a++;
				for(int i=b+1;i<=min(bel\[b\]*block,n);i++) A\[i\]-=c;
				for(int i=bel\[b\]+1;i<=bel\[n\];i++) tag2\[i\]-=c;
			}
			if(a>b) continue;
			if(bel\[a\]^bel\[b\])
			{
				val=0;
				for(int i=a;i<=bel\[a\]*block;i++) val+=c,A\[i\]+=val;
				val=(ll)((bel\[b\]-1)\*block+1-a)\*c;
				for(int i=(bel\[b\]-1)*block+1;i<=b;i++) val+=c,A\[i\]+=val;
				update(bel\[a\]),build(bel\[a\]),update(bel\[b\]),build(bel\[b\]);
				val=-(ll)(a-1)*c;
				for(int i=bel\[a\]+1;i<bel\[b\];i++) tag1\[i\]+=c,tag2\[i\]+=val; 
			}
			else
			{
				val=0;
				for(int i=a;i<=b;i++) val+=c,A\[i\]+=val;
				update(bel\[a\]),build(bel\[a\]);
			}
		}
	}
	return 0;
}