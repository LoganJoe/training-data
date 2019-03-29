---
title: " DTOJ4231Convex\t\t"
tags:
  - 思路
  - 计算几何
url: 6982.html
id: 6982
categories:
  - DTOJ
  - Solution
date: 2019-03-16 11:37:39
---

记凸包面积为$S$，两部分面积中小的为$S1$，大的为$S2$。 我们要计算的是$\\sum S2-S1$，由于$S1+S2=S$，我们计算$\\sum S-2S1$即可。 现在的问题就是求$\\sum S1$。 我们枚举对角线的一个点$i$，同时可以维护顺时针过去最远的一个$j$，使得$P\_i,P\_j$连线左侧的面积比右侧小，也就是$i$的对踵点。两侧面积相当的情况要注意特判一下，否则可能多算一次面积。 显然$j$是单调的，可以不断推过去。 考虑计算对角线另一个端点在$i\\sim j$中的所有$S1$的和。 每个$S1$可以看出若干个三角形的有向面积和，也就是从$i$开始的一些点和原点的叉积和。 我们将叉积的式子化开，变成横纵坐标的乘积。 我们维护所有点横坐标和纵坐标的前缀和，就可以在$i,j$移动时维护出所有$S1$的和了。 具体细节参考代码。

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
#define N 4000005
#define mod 1000000007
#define ll long long
#define db double
#define _(d) while(d((ch=getchar()-48)>=0))
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,ans,Sumx\[N\],Sumy\[N\];ll S,S1,S2,res;
struct point
{
	int x,y;
	friend point operator-(point t1,point t2) {return {t1.x-t2.x,t1.y-t2.y};}
	friend ll operator*(point t1,point t2) {return (ll)t1.x\*t2.y-(ll)t2.x\*t1.y;}
}A\[N\];
int cal(int x) {x-=x<mod?0:mod;return x;}
int get() {char ch;int f=1,v;_(!)if(ch==-3) f=-1;v=ch;_()v=v\*10+ch;return f\*v;}
int main()
{
	n=get();
	for(int i=1;i<=n;i++) A\[i\].x=get(),A\[i\].y=get(),A\[i+n\]=A\[i\];
	for(int i=1;i<=n<<1;i++) Sumx\[i\]=cal(Sumx\[i-1\]+cal(A\[i\].x+mod)),Sumy\[i\]=cal(Sumy\[i-1\]+cal(A\[i\].y+mod));
	A\[0\]=A\[n\];
	for(int i=1;i<=n;i++) S+=A\[i\]*A\[i-1\];
	for(int i=1,j=2,tmp;i<=n;i++)
	{
		for(;S2=(A\[j+1\]-A\[i\])*(A\[j\]-A\[i\]),S1+S2<S-S1-S2||(S1+S2==S-S1-S2&&j<n);j++) S1+=S2,res=cal(res+S1%mod);
		ans=cal(ans+res);
		tmp=cal((Sumx\[j\]-Sumx\[i+1\]-(ll)(j-i-1)*A\[i\].x)%mod+mod);
		res=cal(res-cal((ll)tmp*(A\[i+1\].y-A\[i\].y)%mod+mod)+mod);
		tmp=cal((Sumy\[j\]-Sumy\[i+1\]-(ll)(j-i-1)*A\[i\].y)%mod+mod);
		res=cal(res+cal((ll)tmp*(A\[i+1\].x-A\[i\].x)%mod+mod));
		S1-=(A\[j\]-A\[i\])*(A\[i+1\]-A\[i\]);
	}
	ans=cal(ans+ans),S%=mod,ans=cal((ll)n*(n-3)/2%mod*S%mod-ans+mod);
	printf("%d\\n",ans);
	return 0;
}