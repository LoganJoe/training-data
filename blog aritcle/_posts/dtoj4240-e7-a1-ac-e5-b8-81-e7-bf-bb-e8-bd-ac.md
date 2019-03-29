---
title: " DTOJ4240硬币翻转\t\t"
tags:
  - 思路
url: 7079.html
id: 7079
categories:
  - DTOJ
  - Solution
date: 2019-03-21 23:01:20
---

发现猜对的位置可能被改变，但是猜错的位置不会。求出猜对数量为$0$的序列同样是求出了答案。 随机一个初始局面，期望猜错$50$个。 依次枚举每一位，考虑将每一位都变成猜错的状态。 我们先取反这位的状态，然后询问交互库。 如果猜错数量增加了，那么现在这位就是猜错的，不用改变。 如果猜错数量减小了，那么现在这位就是猜对的，我们再取反回去。 如果猜错数量不变。那么现在这位是猜对的，但是上一次询问后某个其他猜对的硬币被蒜头翻转了。 按理来说此时我们应该取反当前位。但是在这次询问中，当前位猜对了，说明蒜头有概率翻转当前位，如果发生了这种情况再取反当前位就是错误的了。 发现这种情况的发生的概率很小，期望只会发生一次。那么我们当做这次查询是无效的，再取反当前位重新做一次即可。如果运气够差的话可能重做一次还不够……所以还是写个while好。 具体细节参考代码。

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
#include "coin.h"
#include "grader.cpp"
using std::cin;using std::cerr;
using std::max;using std::min;
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
void guess()
{
	srand(123);
	std::string s="";int res,now;
	for(int x=0;x<100;++x) s+='0';
	for(int i=0,a;i<100;i++) a=rand()%100,s\[a\]^=1;
	now=100-ask(s);
	for(int i=0;i<100;i++)
	{
		for(;;now=res)
		{
			s\[i\]^=1,res=100-ask(s);
			if(res>now) break;
		}
		now=res;
		if(now==100) break;
	}
	for(int i=0;i<100;i++) s\[i\]^=1;
	ask(s);
}