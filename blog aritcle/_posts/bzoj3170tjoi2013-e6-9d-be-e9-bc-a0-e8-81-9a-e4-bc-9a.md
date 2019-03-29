---
title: " BZOJ3170[Tjoi2013]松鼠聚会\t\t"
tags:
  - 无标签
url: 6940.html
id: 6940
categories:
  - BZOJ
  - Solution
date: 2019-03-10 23:14:57
---

这个距离就是曼哈顿距离。 对于一个点，所有点到它的曼哈顿距离可以分成四部分：左上方、右上方、左下方和右下方。每个部分的点到它的曼哈顿距离的表达式都可以去掉绝对值。 并且曼哈顿距离的横纵坐标的贡献是可以分开算的，左方/右方的点对横坐标的贡献的形式是一样的，上方/下方的点对纵坐标的贡献的形式是一样的。 那么我们可以枚举中心点，然后计算所有点到它的距离和，横纵坐标的贡献分开算，只要预处理出一些前缀和即可。 具体细节参考代码。

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
#define lb(x) std::lower_bound(so+1,so+1+tot,x)-so
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,so\[N\],tot,cnt\[N\];ll Sumx\[N\],Sumy\[N\],res,ans=1e18;
struct point
{
	int x,y;
	friend bool operator<(point t1,point t2) {return t1.x<t2.x;}
}A\[N\];
int main()
{
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;i++) scanf("%d%d",&a,&b),A\[i\]={a+b,a-b},so\[i\]=A\[i\].y;
	std::sort(A+1,A+1+n),std::sort(so+1,so+1+n),tot=std::unique(so+1,so+1+n)-so-1;
	for(int i=1;i<=n;i++) A\[i\].y=lb(A\[i\].y),Sumx\[i\]=Sumx\[i-1\]+A\[i\].x,Sumy\[A\[i\].y\]+=so\[A\[i\].y\],cnt\[A\[i\].y\]++;
	for(int i=1;i<=tot;i++) Sumy\[i\]+=Sumy\[i-1\],cnt\[i\]+=cnt\[i-1\];
	for(int i=1;i<=n;i++)
	{
		res=(ll)A\[i\].x*(i-n+i)+Sumx\[n\]-2*Sumx\[i\];
		res+=(ll)so\[A\[i\].y\]*(2\*cnt\[A\[i\].y\]-n)+Sumy\[tot\]-2\*Sumy\[A\[i\].y\];
		ans=min(ans,res);
	}
	printf("%lld\\n",ans>>1);
	return 0;
}