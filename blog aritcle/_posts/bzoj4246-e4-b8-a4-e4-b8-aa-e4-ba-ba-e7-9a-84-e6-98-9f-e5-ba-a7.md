---
title: " BZOJ4246两个人的星座\t\t"
tags:
  - 思路
url: 6961.html
id: 6961
categories:
  - BZOJ
  - Solution
date: 2019-03-13 20:51:49
---

考虑怎么判断两个三角形不相交。 我们在两个三角形上各取一个点，然后连出一条直线。容易发现，在$9$种选法中，有$2$种选法得到的直线会将两个三角形分隔在两侧。此时这条直线应该是叫做三角形的内公切线。 我们枚举按斜率从小到大枚举内公切线，分别维护在公切线两侧每种颜色的点的数量，维护的话只需要考虑当前直线上的两个点的影响即可。 然后用乘法原理计算一下三角形的对数即可。 最后答案要$\\div 4$，因为一对合法的三角形会被计算四次。 具体细节参考代码。

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
#define N 3005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
const db pi=acos(-1);
int n,Bn,mark\[N\],cnt\[2\]\[3\];ll ans;
struct point
{
	int x,y,c;db k;
	friend bool operator<(point t1,point t2) {return t1.k<t2.k;}
}A\[N\],B\[N\];
int ask(int x,int y)
{
	int res=1;
	for(int i=0;i<3;i++) if(i^y) res*=cnt\[x\]\[i\];
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&A\[i\].x,&A\[i\].y,&A\[i\].c);
	for(int i=1;i<=n;i++)
	{
		Bn=0;
		for(int j=1;j<=n;j++)
			if(i^j) B\[++Bn\]=A\[j\],B\[Bn\].x-=A\[i\].x,B\[Bn\].y-=A\[i\].y,B\[Bn\].k=atan2(B\[Bn\].y,B\[Bn\].x),B\[Bn\].k+=B\[Bn\].k<0?pi:0;
		std::sort(B+1,B+n);
		for(int j=1;j<n;j++) mark\[j\]=B\[j\].y<0?0:1,cnt\[mark\[j\]\]\[B\[j\].c\]++;
		for(int j=1;j<n;j++)
		{
			cnt\[mark\[j\]\]\[B\[j\].c\]--;
			ans+=(ll)ask(0,A\[i\].c)\*ask(1,B\[j\].c)+(ll)ask(0,B\[j\].c)\*ask(1,A\[i\].c);
			cnt\[mark\[j\]^1\]\[B\[j\].c\]++;
		}
		for(int j=0;j<3;j++) cnt\[0\]\[j\]=cnt\[1\]\[j\]=0;
	}
	printf("%lld\\n",ans>>2);
	return 0;
}