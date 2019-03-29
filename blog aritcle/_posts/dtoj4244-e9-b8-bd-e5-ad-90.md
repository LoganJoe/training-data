---
title: " DTOJ4244鸽子\t\t"
tags:
  - 二分
  - 计算几何
url: 7138.html
id: 7138
categories:
  - DTOJ
  - Solution
date: 2019-03-26 22:46:40
---

考虑第一只鸽子和第二只鸽子的距离随着时间变化的图像。 先考虑第一只鸽子的横轴坐标随着时间$t$变化的图像。当第一只鸽子在某一条边上移动时，横坐标/纵坐标关于$t$的图像都是一条直线，也就是一个一次函数。一共有$n$条边，因此横坐标/纵坐标关于$t$的图像是一个分段一次函数，一共有$n$段。 再考虑第一只鸽子和第二只鸽子的距离。 我们将两只鸽子的坐标都用$t$表示出来，分别都是关于$t$的分段一次函数。那么代进欧几里得距离的式子里面后，距离的平方就是关于$t$的分段二次函数，段数是$\\Theta(n)$的。 考虑二分答案$mid$。 如果$mid$是可行的，那么一定存在一个时刻$t$，使得相邻两只鸽子的距离都$\\leq mid$。 由于$n$只鸽子是匀速移动的，那么等价于存在一个时刻$t\\in\[0,\\frac C m)$，使得在时刻$t,t+\\frac C m,t+2\\frac C m,…,t+(m-1)\\frac C m$，第一只鸽子和第二只鸽子的距离都$\\leq mid$。 我们第一只鸽子和第二只鸽子的距离的平方关于$t$的分段二次函数求出来，并求出纵坐标$\\leq mid$时横坐标的范围。 这些范围由若干个不相交的区间组成，我们将$ \\geq \\frac C m$的部分映射到$\[0,\\frac C m)$（也可以理解成对$\\frac C m$取模）。那么如果存在一个位置$\\in\[0,\\frac C m)$被$\\geq m$个区间覆盖了，就说明存在一个合法的$t\\in\[0,\\frac C m)$，也就是说$mid$是可行的。 将区间取个补集，就变成判断是否存在一个位置没有被任何区间覆盖，将区间排序后扫一遍即可。 具体细节参考代码。

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
#define N 60005
#define eps 1e-7
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,Cn,flag;db D,Sumd\[N\];
struct point
{
	db x,y;
	friend point operator+(point t1,point t2) {return {t1.x+t2.x,t1.y+t2.y};}
	friend point operator-(point t1,point t2) {return {t1.x-t2.x,t1.y-t2.y};}
	friend point operator*(point t1,db t2) {return {t1.x\*t2,t1.y\*t2};}
}A\[N\],B\[N\];
struct info{db l,r;}C\[N<<1\];
db F(db x) {return x*x;}
db Dist(point p1,point p2) {return sqrt(F(p1.x-p2.x)+F(p1.y-p2.y));}
void insert(db l,db r)
{
	if(r-l<eps) return;
	if(r-l>D) return void(flag=1);
	int x=floor(l/D),y=floor(r/D);l-=x\*D,r-=y\*D;
	if(x^y) C\[++Cn\]={0,r},C\[++Cn\]={l,D};else C\[++Cn\]={l,r};
}
bool Judge(db mid)
{
	db t=0,Lim1,Lim2,Min,a,b,c,kx,ky,bx,by,delta,x1,x2;
	int i=1,j;point now1=A\[1\],now2;flag=Cn=0;
	for(j=1;Sumd\[j+1\]<D+eps;j++);
	now2=A\[j\]+B\[j\]*(D-Sumd\[j\]);
	for(;i<=n;t=Min)
	{
		Lim1=Sumd\[i+1\],Lim2=Sumd\[j+1\]-D,Min=min(Lim1,Lim2);
		kx=B\[i\].x-B\[j\].x,ky=B\[i\].y-B\[j\].y,bx=now1.x-now2.x,by=now1.y-now2.y;
		a=F(kx)+F(ky),b=2\*kx\*bx+2\*ky\*by,c=F(bx)+F(by)-F(mid);
		if(a>eps)
		{
			delta=F(b)-4\*a\*c;
			if(delta>0)
			{
				delta=sqrt(delta),x1=(-b-delta)*.5/a,x2=(-b+delta)*.5/a;
				insert(t,min(Min,t+x1)),insert(max(t,t+x2),Min);
			}
			else insert(t,Min);
		}
		else
		{
			if(fabs(b)>eps)
			{
				x1=-c/b;
				if(b>eps) insert(max(t,t+x1),Min);
				else insert(t,min(Min,t+x1));
			}
			else if(c>eps) insert(t,Min);
		}
		if(Lim1<Min+eps) now1=A\[++i\];else now1=now1+B\[i\]*(Min-t);
		if(Lim2<Min+eps) now2=A\[++j\];else now2=now2+B\[j\]*(Min-t);
		if(flag) return 0;
	}
	std::sort(C+1,C+1+Cn,\[\](info t1,info t2){return t1.l<t2.l;}),t=0;
	for(int i=1;i<=Cn;i++)
	{
		if(C\[i\].l-t>eps) return 1;
		t=max(t,C\[i\].r);
	}
	if(D-t>eps) return 1;
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lf%lf",&A\[i\].x,&A\[i\].y);
	for(int i=1;i<=n;i++)
	{
		A\[i+n\]=A\[i\],B\[i\]=B\[i+n\]=(A\[i+1\]-A\[i\])*(1./Dist(A\[i\],A\[i+1\]));
		Sumd\[i+1\]=Sumd\[i\]+Dist(A\[i\],A\[i+1\]);
	}
	for(int i=2;i<=n;i++) Sumd\[i+n\]=Sumd\[i\]+Sumd\[n+1\];
	D=Sumd\[n+1\]/m;db l=0,r=D,mid;
	for(;r-l>eps;) mid=(l+r)*.5,Judge(mid)?r=mid:l=mid;
	printf("%lf\\n",l);
	return 0;
}