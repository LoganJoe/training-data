---
title: " BZOJ3871[Neerc2013 C]Cactus Automorphisms\t\t"
tags:
  - hash
  - 仙人掌
  - 圆方树
url: 5961.html
id: 5961
categories:
  - BZOJ
  - Solution
date: 2019-01-03 22:37:41
---

这题的弱化版是[BZOJ3899仙人掌树的同构](http://www.dtenomde.com/author=jiangyutong/article=5883/)。 （戳进去是题解） 不过我弱化版就写的是$\\Theta(n\\log n)$，所以题解就不再写一遍了。 没有取模的话把所有要乘的数被乘的次数都记下来，最后再一起做质因数分解。这部分我写错了无数次…… 哦这题的输入是给出了$m$条路径。 注意这题的数据强了很多。 还有如果根节点是我们手动加的重心，我们最好将这个点看成圆点。如果看成方点的话，环的自同构数量是$2$，不要求错了。

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
#define P1 19990213
#define P2 19260817
#define ll long long
#define ull unsigned long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K,a,b,tot,rt1,rt2,isp\[N\],Minp\[N\],ans\[N\],Ans;
class Tree
{
	int size\[N\],Maxsz\[N\];ull son\[N<<1\],ha\[N<<1\],po\[N<<1\];
	ull askhash(int l,int r) {return ha\[r\]-ha\[l-1\]*po\[r-l+1\];}
public:
	int ecnt,last\[N\];
	struct road{int to,nex;}e\[N<<1\];
	void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
	void getroot(int x,int fath=0)
	{
		size\[x\]=1;
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(e\[k\].to^fath)
			{
				getroot(e\[k\].to,x),size\[x\]+=size\[e\[k\].to\];
				Maxsz\[x\]=max(Maxsz\[x\],size\[e\[k\].to\]);
			}
		Maxsz\[x\]=max(Maxsz\[x\],tot-size\[x\]);
		if(!rt1||Maxsz\[x\]<Maxsz\[rt1\]) rt1=x,rt2=0;
		else if(Maxsz\[x\]==Maxsz\[rt1\]) rt2=x;
	}
	void dfs(int x,int fath=0)
	{
		size\[x\]=1;int cnt=0;
		for(int k=last\[x\];k;k=e\[k\].nex)
			if(e\[k\].to^fath) dfs(e\[k\].to,x),size\[x\]+=size\[e\[k\].to\];
		if(x<=n)
		{
			for(int k=last\[x\];k;k=e\[k\].nex) if(e\[k\].to^fath) son\[++cnt\]=ha\[e\[k\].to\];
			std::sort(son+1,son+1+cnt);
			for(int i=1,pre=0;i<=cnt;i++)
			{
				if(i==cnt||son\[i+1\]^son\[i\]) ans\[i-pre\]++,pre=i;
				ha\[x\]=ha\[x\]*P1+son\[i\];
			}
			ha\[x\]+=size\[x\];
			if(!fath) for(int i=n<<1;i;i--) ans\[i\]+=ans\[i+1\];
		}
		else if(x^rt1)
		{
			int id=0;ull ha1=0,ha2=0;
			for(int k=last\[x\];k&&!id;k=e\[k\].nex) if(e\[k\].to==fath) id=k;
			for(int k=e\[id\].nex;k;k=e\[k\].nex) son\[++cnt\]=ha\[e\[k\].to\];
			for(int k=last\[x\];k^id;k=e\[k\].nex) son\[++cnt\]=ha\[e\[k\].to\];
			for(int i=1;i<=cnt;i++) ha1=ha1*P2+son\[i\];ha1+=size\[x\];
			for(int i=cnt;i;i--) ha2=ha2*P2+son\[i\];ha2+=size\[x\];
			if(ha1==ha2) ans\[2\]++;
			ha\[x\]=min(ha1,ha2);
		}
		else
		{
			int ti=0;ull h;po\[0\]=1;
			for(int k=last\[x\];k;k=e\[k\].nex) son\[++cnt\]=ha\[e\[k\].to\];
			for(int i=1;i<=cnt;i++) son\[i+cnt\]=son\[i\];
			for(int i=1;i<=cnt<<1;i++) ha\[i\]=ha\[i-1\]\*P1+son\[i\],po\[i\]=po\[i-1\]\*P1;
			h=ha\[cnt\];
			for(int i=1;i<=cnt;i++) if(askhash(i,i+cnt-1)==h) ti++;
			std::reverse(son+1,son+1+cnt*2);
			for(int i=1;i<=cnt<<1;i++) ha\[i\]=ha\[i-1\]\*P1+son\[i\],po\[i\]=po\[i-1\]\*P1;
			for(int i=1;i<=cnt;i++) if(askhash(i,i+cnt-1)==h) ti++;
			for(int i=n<<1;i;i--) ans\[i\]+=ans\[i+1\];
			if(cnt>2) ans\[ti\]++;else ans\[2\]=1;
		}
	}
}T;
class Graph
{
	int ecnt,last\[N\],idx,dfn\[N\],low\[N\],sta\[N\],top;
	struct road{int to,nex;}e\[N<<1\];
public:
	void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt;}
	void tarjan(int x,int fath=0)
	{
		dfn\[x\]=low\[x\]=++idx,sta\[++top\]=x;
		for(int k=last\[x\],tmp;k;k=e\[k\].nex)
			if(!dfn\[e\[k\].to\])
			{
				tarjan(e\[k\].to,x),low\[x\]=min(low\[x\],low\[e\[k\].to\]);
				if(low\[e\[k\].to\]>=dfn\[x\])
				{
					if(sta\[top\]==e\[k\].to) {T.adde(x,sta\[top\]),T.adde(sta\[top\],x),top--;continue;}
					tot++,T.adde(tot,x),T.adde(x,tot);
					do tmp=sta\[top--\],T.adde(tot,tmp),T.adde(tmp,tot);
					while(tmp^e\[k\].to);
				}
			}
			else if(e\[k\].to^fath) low\[x\]=min(low\[x\],dfn\[e\[k\].to\]);
	}
}G;
int main()
{
	scanf("%d%d",&n,&m),tot=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&K,&a);
		for(int j=1;j<K;j++,a=b) scanf("%d",&b),G.adde(a,b),G.adde(b,a);
	}
	G.tarjan(1),T.getroot(1);
	if(rt2)
	{
		tot++;
		for(int k=T.last\[rt1\];k;k=T.e\[k\].nex) if(T.e\[k\].to==rt2) T.e\[k\].to=tot;
		for(int k=T.last\[rt2\];k;k=T.e\[k\].nex) if(T.e\[k\].to==rt1) T.e\[k\].to=tot;
		T.adde(tot,rt1),T.adde(tot,rt2),rt1=tot;
	}
	T.dfs(rt1);
	for(int i=2;i<=n<<1;i++) if(!isp\[i\])
	{
		Minp\[i\]=i;
		for(int j=i+i;j<=n<<1;j+=i) if(!isp\[j\]) isp\[j\]=1,Minp\[j\]=i;
	}
	for(int i=2;i<=n<<1;i++) if(isp\[i\])
		for(int j=i;j>1;j/=Minp\[j\]) ans\[Minp\[j\]\]+=ans\[i\];
	for(int i=2;i<=n<<1;i++) if(!isp\[i\]&&ans\[i\]) Ans++;
	printf("%d\\n",Ans);
	for(int i=2;i<=n<<1;i++) if(!isp\[i\]&&ans\[i\]) printf("%d %d\\n",i,ans\[i\]);
	return 0;
}