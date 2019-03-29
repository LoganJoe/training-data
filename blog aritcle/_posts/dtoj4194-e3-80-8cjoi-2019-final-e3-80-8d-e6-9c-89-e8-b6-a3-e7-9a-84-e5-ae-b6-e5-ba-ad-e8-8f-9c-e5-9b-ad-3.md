---
title: " DTOJ4194「JOI 2019 Final」有趣的家庭菜园 3\t\t"
tags:
  - dp
url: 6735.html
id: 6735
categories:
  - DTOJ
  - Solution
date: 2019-03-03 12:06:53
---

考虑dp。 记$f\[i\]\[j\]\[k\]\[0/1/2\]$为前$i$个位置中有$j$个\`R\`，有$k$个\`G\`，并且第$i$个是\`R\`/\`G\`/\`Y\`的最小代价。 显然通过dp状态我们可以计算出前$i$个位置中\`Y\`的个数是$i-j-k$个。 我们可以枚举第$i+1$个位置要放哪种，通过$0/1/2$我们可以保证相同的颜色不会相邻。 现在的问题就是转移的代价了。 假设我们要在第$i+1$个位置放\`R\`，这个\`R\`是第$j+1$个。 那么我们就是要求将第$j+1$个\`R\`移到第$i+1$个位置的代价。 假设第$j+1$个\`R\`在原序列的位置为$p$，我们可以通过原本序列中前$p$个位置中有多少个\`R\`，\`G\`，\`Y\`计算出位置$p$后面有多少个数被移动到了位置$p$的前面，这样就可以计算出现在第$j+1$个\`R\`的真实位置了。拿真实位置和$i+1$作差就得到了移动的代价。 最后答案就是$\\min\\{f\[n\]\[i\]\[j\]\[0/1/2\]\\}$。 时间复杂度$\\Theta(n^3)$，具体细节参考代码。

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
#define ll long long
#define db double
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,cnt\[3\],sz\[3\],Sum\[N\]\[3\],f\[2\]\[N\]\[N\]\[3\],ans=inf;char s\[N\];
std::vector<int>S\[3\];
void update(int &x,int v) {x=min(x,v);}
int main()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<3;j++) Sum\[i\]\[j\]=Sum\[i-1\]\[j\];
		if(s\[i\]=='R') S\[0\].pb(i),Sum\[i\]\[0\]++;
		if(s\[i\]=='G') S\[1\].pb(i),Sum\[i\]\[1\]++;
		if(s\[i\]=='Y') S\[2\].pb(i),Sum\[i\]\[2\]++;
	}
	sz\[0\]=S\[0\].size(),sz\[1\]=S\[1\].size(),sz\[2\]=S\[2\].size();
	for(int i=0;i<=sz\[0\];i++)
		for(int j=0;j<=sz\[1\];j++)
			for(int k=0;k<3;k++) f\[0\]\[i\]\[j\]\[k\]=f\[1\]\[i\]\[j\]\[k\]=1e9;
	if(sz\[0\]) f\[1\]\[1\]\[0\]\[0\]=S\[0\]\[0\]-1;
	if(sz\[1\]) f\[1\]\[0\]\[1\]\[1\]=S\[1\]\[0\]-1;
	if(sz\[2\]) f\[1\]\[0\]\[0\]\[2\]=S\[2\]\[0\]-1;
	for(int i=1,p;i<n;i++)
		for(int j=0;j<=min(sz\[0\],i);j++)
			for(int k=0;k<=sz\[1\]&&j+k<=i;k++)
			{
				if(i-j-k>sz\[2\]) continue;
				cnt\[0\]=j,cnt\[1\]=k,cnt\[2\]=i-j-k;
				for(int l=0;l<3;l++) if(f\[i&1\]\[j\]\[k\]\[l\]<inf)
				{
					for(int s=0;s<3;s++) if(l^s&&cnt\[s\]<sz\[s\])
					{
						p=S\[s\]\[cnt\[s\]\];
						for(int t=0;t<3;t++) if(t^s) p+=max(cnt\[t\]-Sum\[S\[s\]\[cnt\[s\]\]\]\[t\],0);
						update(f\[~i&1\]\[j+(s==0)\]\[k+(s==1)\]\[s\],f\[i&1\]\[j\]\[k\]\[l\]+abs(p-i-1));
					}
					f\[i&1\]\[j\]\[k\]\[l\]=inf;
				}
			}
	for(int i=0;i<=sz\[0\];i++)
		for(int j=0;j<=sz\[1\];j++)
			for(int k=0;k<3;k++) ans=min(ans,f\[n&1\]\[i\]\[j\]\[k\]);
	printf("%d\\n",ans<inf?ans:-1);
	return 0;
}