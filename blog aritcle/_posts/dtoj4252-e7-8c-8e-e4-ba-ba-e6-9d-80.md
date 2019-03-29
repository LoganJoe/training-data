---
title: " DTOJ4252猎人杀\t\t"
tags:
  - 概率dp
url: 7157.html
id: 7157
categories:
  - DTOJ
  - Solution
date: 2019-03-27 23:18:46
---

记$f\[i\]\[j\]$为当前剩余$i$个人，最后中弹的人为第$j$个人（死活还未确定），第$1$个人存活的概率。 记$next(i,j)$为一共有$i$个人，第$j$个人逆时针方向的第$k$个人。显然$nex(i,j)=(j+k-1)\\%i+1$。 那么有 $$ f\[i\]\[j\]=\\frac 1 2(f\[i-1\]\[nex(i-1,j-1)\]+f\[i\]\[nex(i,j)\]) $$ 前者是第$j$个人死亡的情况，后者是第$j$个人存活的情况。 $f\[i\]\[1\]$要特殊考虑一下，因为第$1$个人得存活到最后。 容易发现，若将$(i,j)​$看成点的话，构成了一个分层图。 我们从小到大枚举$i$，那么$f\[i-1\]\[nex(i-1,j-1)\]$就是已知的了，可以直接得到。 但同层的状态会形成环，不能直接求出。 如果用高斯消元的话就$\\Theta(n^3)$了，还要做$n$次。 发现这个图比较特殊，每个点一定只有一条出边和一条入边（$j$向$nex(i,j)$连边）。 整张图由若干个环组成，对于每个环，我们分开考虑。 一条$i\\rightarrow j$的边，代表着形如$x\_i=\\frac 1 2(x\_j+v\_i)$的方程，其中$v\_i=f\[i-1\]\[nex(i-1,j-1)\]$，是已知的。我们将$x\_j$用$j$的出边$k$的$x\_k$表示，$x\_k$再继续用出边表示，直到再次走到$i$，我们就可以解出$x\_i$了。 试着手模一下就可以发现，系数和$2$的幂有关，可以直接求出，这样就可以直接解出$x_i$了。 求出一个后剩下的都可以直接推出来了。 时间复杂度$\\Theta(n^2)$。 具体细节参考代码。

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
#define N 2005
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,f\[N\]\[N\],inv,po\[N\],mark\[N\],sta\[N\],top;
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
int main()
{
	scanf("%d%d",&n,&m),po\[0\]=f\[1\]\[1\]=1,inv=mod+1>>1;
	for(int i=1;i<=n;i++) po\[i\]=cal(po\[i-1\]+po\[i-1\]);
	for(int i=2,v;i<=n;i++)
	{
		for(int j=2;j<=i;j++) f\[i\]\[j\]=f\[i-1\]\[(j+m-2)%(i-1)+1\];
		for(int j=1;j<=i;j++) if(!mark\[j\])
		{
			top=v=0;
			for(int k=j;!mark\[k\];k=(k+m-1)%i+1) mark\[k\]=1,sta\[++top\]=k;
			for(int k=top;k;k--) v=cal((ll)inv*v%mod+f\[i\]\[sta\[k\]\]);
			f\[i\]\[sta\[1\]\]=(ll)v\*po\[top-1\]%mod\*Pow(po\[top\]-1,mod-2)%mod;
			f\[i\]\[sta\[top\]\]=(ll)cal(f\[i\]\[sta\[top\]\]+f\[i\]\[sta\[1\]\])*inv%mod;
			for(int k=top-1;k>1;k--) f\[i\]\[sta\[k\]\]=(ll)cal(f\[i\]\[sta\[k\]\]+f\[i\]\[sta\[k+1\]\])*inv%mod;
		}
		for(int j=1;j<=i;j++) mark\[j\]=0;
	}
	printf("%d\\n",f\[n\]\[(m-1)%n+1\]);
	return 0;
}