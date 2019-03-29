---
title: " BZOJ3190[JLOI2013]赛车\t\t"
tags:
  - 无标签
url: 6942.html
id: 6942
categories:
  - BZOJ
  - Solution
date: 2019-03-11 22:32:53
---

好像和BZOJ1007\[HNOI2008\]水平可见直线一样啊…… 其实这应该算是半平面交，但是只有半平面交只有一半。 随着时间的增加，在最前面的车的加速度是越来越快的。 我们将每辆车的速度随时间的变化看成一条直线，然后按斜率排序。 枚举一个$i$，同时拿一个单调栈维护前$i$条直线中领跑过的车有哪些。 插入一条直线就不断弹栈即可。 要注意完全相同的直线和只是斜率相同的直线。 具体细节参考代码。

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
#define N 10005
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,top,mark\[N\],ans\[N\];
struct line
{
	int id,k,b;
	friend bool operator<(line t1,line t2) {return t1.k<t2.k||t1.k==t2.k&&t1.b>t2.b;}
}A\[N\],sta\[N\];
db calc(line l1,line l2) {return (l1.b-l2.b)*1./(l2.k-l1.k);}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\].b),A\[i\].id=i;
	for(int i=1;i<=n;i++) scanf("%d",&A\[i\].k);
	std::sort(A+1,A+1+n);
	sta\[top=1\]=A\[1\];
	for(int i=2;i<=n;i++)
	{
		if(A\[i\].k==A\[i-1\].k) continue;
		for(;top>1&&calc(sta\[top-1\],sta\[top\])>calc(sta\[top-1\],A\[i\]);top--);
		if(top==1&&calc(sta\[top\],A\[i\])<0) top--;
		sta\[++top\]=A\[i\];
	}
	for(int i=1;i<=top;i++) mark\[sta\[i\].id\]=1;
	for(int i=1;i<=n;i++) if(mark\[i-1\]&&A\[i\].k==A\[i-1\].k&&A\[i\].b==A\[i-1\].b) mark\[i\]=1;
	for(int i=1;i<=n;i++) if(mark\[i\]) ans\[++ans\[0\]\]=i;
	printf("%d\\n",ans\[0\]);
	for(int i=1;i<=ans\[0\];i++) printf("%d%c",ans\[i\],i<ans\[0\]?' ':'\\n');
	return 0;
}