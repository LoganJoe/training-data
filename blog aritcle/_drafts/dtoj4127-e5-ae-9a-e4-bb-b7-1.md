---
title: " DTOJ4127定价\t\t"
tags:
  - 思路
url: 6507.html
id: 6507
categories:
  - DTOJ
  - Solution
---

zzq：“由于太懒了，数据造的挺烂的，希望不要有莫名其妙的水法水过去。” flag高高挂起，于是大家都是暴力水过去的。 因此只能讲讲暴力了。 显然定价策略就是每次找到第一个合法的比之前大的价格。 我们对于每个数用一个set维护它哪些位可以为$1$。显然第一个数我们是可以直接确定价格的，考虑如何找到第一个合法的比当前大的数。 我们再用一个set维护当前数哪些位为$1$。 我们找到最高的当前为$1$不能继续为$1$的位，然后我们要找到比这位高的一位$0$，把它变成$1$（找不到合法的就$-1$了），然后把后面的全部变成$0$。 如果当前为$1$的位都能继续为$1$，那么我们看看能不能在最后一个（最靠低位）$1$后面再加一个$1$，能加就加能加中最靠后的$1$，否则仍然是要把前面的某个$0$变成$1$，然后把后面都变成$0$。 以上操作都可以用set实现，具体细节参考代码。 时间复杂度$\\Theta(10^3n^2)$，但是常数比较小，就过了（在FZOJ过了，DTOJ已被我添加了一组hack数据ha掉了）。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 1005
#define M 500005
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,Q,op,a,b,ans,Sum;
std::set<int>S\[N\],S2;std::set<int>::iterator it,it2;
int cal(int x) {x-=x<mod?0:mod;return x;}
int Pow(int x,int y) {int res=1;for(;y;x=(ll)x\*x%mod,y>>=1) if(y&1) res=(ll)res\*x%mod;return res;}
void Solve()
{
	for(int i=1;i<=n;i++) if(S\[i\].empty()) return void(puts("-1"));
	S2.clear(),it=S\[1\].begin(),S2.insert(\*it),ans=Sum=Pow(2,(\*it)-1);
	for(int i=2;i<=n;i++)
	{
		for(it=S2.end(),it--;it!=S2.begin();it--) if(!S\[i\].count(*it)) break;
		for(it2=S2.begin();it2!=it;S2.erase(it2++)) Sum=cal(Sum-Pow(2,(*it2)-1)+mod);
		if(S\[i\].count(*it))
		{
			it2=S\[i\].begin();
			if((\*it2)<(\*it)) {S2.insert(\*it2),Sum=cal(Sum+Pow(2,(\*it2)-1)),ans=cal(ans+Sum);continue;}
		}
		it2=S\[i\].upper_bound(\*it),Sum=cal(Sum-Pow(2,(\*it)-1)+mod),S2.erase(it);
		if(it2==S\[i\].end()) return void(puts("-1"));
		while(S2.count(*it2))
		{
			Sum=cal(Sum-Pow(2,(\*it2)-1)+mod),S2.erase(\*it2),it2++;
			if(it2==S\[i\].end()) return void(puts("-1"));
		}
		S2.insert(\*it2),Sum=cal(Sum+Pow(2,(\*it2)-1)),ans=cal(ans+Sum);
	}
	printf("%d\\n",ans);
}
int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	for(;Q--;)
	{
		scanf("%d",&op);
		if(op<2)
		{
			scanf("%d%d",&a,&b),b=m-b+1;
			if(S\[a\].count(b)) S\[a\].erase(b);else S\[a\].insert(b);
		}
		else Solve();
	}
	return 0;
}

顺便附上正解。 ![](http://www.dtenomde.com/wp-content/uploads/2019/02/67462974-5417-4F6E-B04C-FE4177D7E59E.jpg) ![](http://www.dtenomde.com/wp-content/uploads/2019/02/72C234D7-B140-4126-9B46-7F01B26D8C45.jpg) ![](http://www.dtenomde.com/wp-content/uploads/2019/02/4FADDE50-5F84-4248-B942-F046CADEE35F.jpg)