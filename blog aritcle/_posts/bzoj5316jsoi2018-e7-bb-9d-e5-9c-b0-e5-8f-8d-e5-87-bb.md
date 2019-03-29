---
title: " BZOJ5316[Jsoi2018]绝地反击\t\t"
tags:
  - 奇技淫巧
  - 最大流
  - 计算几何
url: 7065.html
id: 7065
categories:
  - BZOJ
  - Solution
date: 2019-03-19 21:36:29
---

考虑二分答案，那么每个飞船能移到圆上的哪些位置就可以求出来（注意无法移到圆上的情况），显然是一段圆弧。 如果有解的话，那么一定有一组解中存在某个飞船匹配的是自己匹配范围的边界，那么我们枚举这个点，这样圆上剩下$n-1$个点的位置就能求出来了。剩下的就是一个匹配的问题了，可以用网络流求解，时间复杂度应该是$\\Theta(n^4\\log)$的。 考虑优化。 圆上的$n$个待匹配的点，随着枚举的边界而移动，角度最多只会移动$\\frac{2\\pi}{n}$。 那么这个过程中，每个点能匹配的点最多只会减少一个或者增加一个，也就是说每次只会删去一条匹配边或者增加一条匹配边。 将事件按时间排序后，我们只要维护加/删一条边的网络流。 加很好维护。由于是二分图，删只会影响到三条边，暴力删掉并退流即可。 时间复杂度$\\Theta(n^3\\log)$。 具体细节参考代码。

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
#define N 405
#define inf 1e9
#define eps 1e-9
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
const db pi=acos(-1);
int n,m,Bn;db ang;
struct point{int x,y;db d;}A\[N\];
struct info
{
	int x,y,v;db ang;
	friend bool operator<(info t1,info t2) {return t1.ang<t2.ang-eps||fabs(t1.ang-t2.ang)<eps&&t1.v<t2.v;}
}B\[N\];
class Flow
{
	int last\[N\],cur\[N\],lev\[N\];
	struct road{int to,f,nex;}e\[N*N\];
	bool bfs()
	{
		std::queue<int>q;
		for(int i=S;i<=T;i++) lev\[i\]=0,cur\[i\]=last\[i\];
		for(lev\[S\]=1,q.push(S);!q.empty();)
		{
			int top=q.front();q.pop();
			if(top==T) return 1;
			for(int k=last\[top\];k;k=e\[k\].nex)
				if(!lev\[e\[k\].to\]&&e\[k\].f) lev\[e\[k\].to\]=lev\[top\]+1,q.push(e\[k\].to);
		}
		return 0;
	}
	int dfs(int x,int Max)
	{
		if(x==T||!Max) return Max;
		int flow,res=0;
		for(int &k=cur\[x\];k;k=e\[k\].nex)
			if(lev\[e\[k\].to\]==lev\[x\]+1)
			{
				flow=dfs(e\[k\].to,min(Max-res,e\[k\].f));
				e\[k\].f-=flow,e\[k^1\].f+=flow,res+=flow;
				if(res==Max) break;
			}
		return res;
	}
public:
	int S,T,ecnt,ans;
	void adde(int u,int v,int w)
	{
		e\[++ecnt\]=(road){v,w,last\[u\]},last\[u\]=ecnt;
		e\[++ecnt\]=(road){u,0,last\[v\]},last\[v\]=ecnt;
	}
	void Maxflow(int op)
	{
		if(op) while(bfs()) ans+=dfs(S,inf);
		else if(bfs()) ans+=dfs(S,inf);
	}
	void Delete(int x,int y)
	{
		int flag=0;
		for(int k=last\[x\];k;k=e\[k\].nex) if(e\[k\].to==y)
		{
			if(e\[k\].f) flag=1;else ans--;
			e\[k\].f=e\[k^1\].f=0;break;
		}
		if(flag) return;
		for(int k=last\[S\];k;k=e\[k\].nex) if(e\[k\].to==x) {e\[k\].f=1,e\[k^1\].f=0;break;}
		for(int k=last\[T\];k;k=e\[k\].nex) if(e\[k\].to==y) {e\[k\].f=0,e\[k^1\].f=1;break;}
		Maxflow(0);
	}
	void clear() {for(int i=S;i<=T;i++) last\[i\]=0;ecnt=1,S=ans=0,T=n<<1|1;}
}F;
bool Judge(db x)
{
	db ang1,ang2,tmp;F.clear(),Bn=0;
	for(int i=1,l,r;i<=n;i++)
	{
		if(x+A\[i\].d<m-eps||x+m<A\[i\].d-eps) return 0;
		F.adde(F.S,i,1),F.adde(i+n,F.T,1);
		if(A\[i\].d+m<x+eps)
		{
			for(int j=1;j<=n;j++) F.adde(i,j+n,1);
			continue;
		}
		ang1=atan2(A\[i\].y,A\[i\].x),ang2=acos((A\[i\].d\*A\[i\].d+m\*m-x\*x)\*.5/A\[i\].d/m);
		tmp=ang1,ang1-=ang2,ang2+=tmp;
		if(ang1<0) ang1+=pi+pi;if(ang2<0) ang2+=pi+pi;
		l=ang1/ang,r=ang2/ang;
		B\[++Bn\]={i,l+1,1,ang1-l\*ang},B\[++Bn\]={i,r+1,-1,ang2-r\*ang};
		l++,r++;
		if(l<=r) for(int j=l+1;j<=r;j++) F.adde(i,j+n,1);
		else
		{
			for(int j=l+1;j<=n;j++) F.adde(i,j+n,1);
			for(int j=1;j<=r;j++) F.adde(i,j+n,1);
		}
	}
	std::sort(B+1,B+1+Bn);
	F.Maxflow(1);
	if(F.ans==n) return 1;
	for(int i=1;i<=Bn;i++)
		if(B\[i\].v>0)
		{
			F.adde(B\[i\].x,B\[i\].y+n,1),F.Maxflow(0);
			if(F.ans==n) return 1;
		}
		else F.Delete(B\[i\].x,B\[i\].y+n);
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m),ang=(pi+pi)/n;
	for(int i=1;i<=n;i++) scanf("%d%d",&A\[i\].x,&A\[i\].y),A\[i\].d=sqrt(A\[i\].x\*A\[i\].x+A\[i\].y\*A\[i\].y);
	db l=0,r=200,mid;
	for(;r-l>eps;) mid=(l+r)*.5,Judge(mid)?r=mid:l=mid;
	printf("%.8lf\\n",l);
	return 0;
}