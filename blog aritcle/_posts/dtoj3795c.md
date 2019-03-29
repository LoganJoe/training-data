---
title: " DTOJ3795c\t\t"
tags:
  - 思路
url: 7144.html
id: 7144
categories:
  - DTOJ
  - Solution
date: 2019-03-26 23:25:49
---

对于每一个$a\_i$，分别考虑它对答案的贡献。 考虑满足$j<i$且$a\_j<a\_i$的$j$对$a\_i$的贡献次数的影响，记我们选择的连续子序列为$\[l,r\]$。 当$l\\leq j$且$r\\geq i$时，$a\_i$就会被多计算一次，那么一共就被计算了$j(n-i+1)$次。 考虑满足$j>i$且$a\_j<a\_i$的$j$对$a\_i$的贡献次数的影响。 当$l\\leq i$且$r\\geq j$时，$a\_i$就会被多计算一次，那么一共就被计算了$i(n-j+1)$次。 我们将$a\_i$从小到大排序，然后用树状数组维护每个位置前的$\\sum j$和每个位置后的$\\sum n-j+1$，计算答案即可。 具体细节参考代码。

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
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,A\[N\],id\[N\],ans;
int cal(int x) {x-=x<mod?0:mod;return x;}
class BIT
{
	int t\[N\];
public:
	void add(int x,int v) {for(;x<=n;x+=x&-x) t\[x\]=cal(t\[x\]+v);}
	int ask(int x) {int res=0;for(;x;x-=x&-x) res=cal(res+t\[x\]);return res;}
}B1,B2;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\]),id\[i\]=i;
	std::sort(id+1,id+1+n,\[\](int t1,int t2){return A\[t1\]<A\[t2\];});
	for(int i=1,x,res;i<=n;i++)
	{
		x=id\[i\],B1.add(x,x),B2.add(n-x+1,n-x+1);
		res=B1.ask(x),ans=cal(ans+(ll)res*(n-x+1)%mod*A\[x\]%mod);
		res=B2.ask(n-x),ans=cal(ans+(ll)x\*res%mod\*A\[x\]%mod);
	}
	printf("%d\\n",ans);
	return 0;
}