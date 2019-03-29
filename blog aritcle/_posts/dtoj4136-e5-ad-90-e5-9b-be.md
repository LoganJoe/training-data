---
title: " DTOJ4136子图\t\t"
tags:
  - 奇技淫巧
url: 6556.html
id: 6556
categories:
  - DTOJ
  - Solution
date: 2019-02-22 23:07:05
---

$k=1$时答案为$m$。 $k=2$时答案为$\\sum\\limits_{i=1}^n \\binom{deg\_i}2$，其中$deg\_i$表示第$i$个点的度数。 $k=3$时有两种情况，一种是菊花，一种是链。 菊花的方案数是$\\sum\\limits_{i=1}^n\\binom{deg\_i}{3}$。 链的方案数很容易想到枚举中间的边，然后分别从两个端点再选一条边出来。也就是$\\sum\\limits\_{(x,y)\\in E}(deg\_x-1)\\cdot (deg\_y-1)$。但这样会计算到三元环，一个三元环会被计算$3$次，因此每个三元环要减去$2$次。 考虑如何求三元环的个数。 对于三元环$(a,b,c)$，我们枚举$a$，以及$a$的一条出边，即枚举$b$。然后再枚举一条$b$的出边，即枚举$c$。同时我们对之前枚举过的$b$打个标记。如果枚举到的$c$是被标记过的点，就说明$(a,b,c)$是一个三元环。 为了避免算重，我们在枚举的时候强制令$a$标号最小即可。 这样计算很容易就发现效率炸了…… 容易发现枚举的效率和点的度数有关，我们要让度数大的点作为$b$的次数尽可能少（因为$b$每次都要枚举一遍所有出边）。 我们按度数从大到小排序，然后给点重标号，显然这是不影响正确性的。 考虑复杂度。对于重标号后一条$x,y$之间的边，考虑$x,y$作为$b$的次数。 这里仅考虑$x​$。 如果$deg\_x\\leq \\sqrt{m}$，由于至多$deg\_x$次，那么时间复杂度就是$\\Theta(m\\sqrt{m})$。 如果$deg\_x>\\sqrt{m}$，那么度数比$x$大的点不超过$\\sqrt{m}$个，也就是说$x\\leq \\sqrt{m}$。由于枚举时保证了$a<b$，那么$x$作为$b$的次数至多$\\sqrt{m}$次，时间复杂度也是$\\Theta(m\\sqrt m)$。 总时间复杂度$\\Theta(m\\sqrt m)​$。 最后考虑$k=4$的情况。 先把菊花的情况算掉，也就是$\\sum\\limits \_{i=1}^n\\binom{deg_i}{4}$。 考虑剩下的情况。 情况$1$ ![](http://www.dtenomde.com/wp-content/uploads/2019/02/5FA35E0A-A356-497B-83BB-4C76A5B1A4E3.jpg) 情况$2$ ![](http://www.dtenomde.com/wp-content/uploads/2019/02/D64F3AFE-DFED-4F96-B5AA-6EFC284D39E2.jpg) 情况$3$ ![](http://www.dtenomde.com/wp-content/uploads/2019/02/8B4D7592-B075-4F39-A76F-67CE05153798-271x300.jpg) 情况$4$ ![](http://www.dtenomde.com/wp-content/uploads/2019/02/EBA8B6EE-83F7-4F0E-9A47-9390072BE007.jpg) 情况$1$我们在上文所说的三元环计数的同时统计一下每个点在几个三元环中，然后枚举$2$号点就可以计算了。 情况$2$是四元环计数，考虑在上文所说的三元环计数的基础上再做些修改。 对于四元环$(a,b,c,d)$，我们枚举$a$以及一条出边，也就是$b$，再枚举$b$的一条出边，也就是$c$。在枚举$a$的时候，我们对每个点开个计数器$cnt\_i$，记下这个点作为$c$出现了几次，然后每次增加的四元环的个数就是$cnt\_c$，然后再$cnt\_c++$即可。 同样要对点重标号，并且保证$a$是标号最小的点。 时间复杂度和三元环计数是一样的，也是$\\Theta(m\\sqrt{m})$。 情况$3$我们可以枚举$2,3$之间的边，然后用度数计算。此时可能出现$1,4$重合或者$1,5$重合的情况，也就是情况$1$。对于每一个情况$1$会被计算两次，减掉即可。 情况$4$我们可以枚举$3,4$之间的边。记当前枚举的$4$号点为$x$，那么$2$号点就可以在之前枚举过的$x$中选，我们只要开个累加器计算一下$deg\_x-1$的和即可。 但这时可能出现$1,4$重合或者$2,5$重合，形成情况$1$；也可能$1,5$重合，形成情况$2$；还有可能$1,4$重合且$2,5$重合，形成一个三元环。 每个情况$1$会被计算$2$次，每个情况$2$会被计算$4$次，每个三元环会被计算$3$次，分别减掉即可。 这样总算计算完了，具体细节参考代码。

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<bitset>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 100005
#define mod 1000000007
#define ll long long
#define db double
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\\n"
int n,m,K,a,b,ecnt,last\[N\],fac\[N\],inv\[N\],deg\[N\],id\[N\],pos\[N\],ans;
int mark\[N\],cnt3\[N\],cnt4\[N\],tot3,tot4,num;
struct road{int to,nex;}e\[N<<2\];
void adde(int u,int v) {e\[++ecnt\]=(road){v,last\[u\]},last\[u\]=ecnt,deg\[u\]++;}
int cal(int x) {x-=x<mod?0:mod;return x;}
int C(int x,int y) {return x<y?0:(ll)fac\[x\]\*inv\[y\]%mod\*inv\[x-y\]%mod;}
void Solve()
{
	for(int i=1;i<=n;i++) id\[i\]=i;
	std::sort(id+1,id+1+n,\[\](int t1,int t2){return deg\[t1\]>deg\[t2\];});
	for(int i=1;i<=n;i++) pos\[id\[i\]\]=i;
	for(int i=1,x,y;i<=n;i++)
	{
		x=id\[i\];
		for(int j=last\[x\];j;j=e\[j\].nex)
		{
			if(pos\[y=e\[j\].to\]<i) continue;
			for(int k=last\[y\];k;k=e\[k\].nex)
			{
				if(pos\[e\[k\].to\]<=i) continue;
				if(mark\[e\[k\].to\]) cnt3\[x\]++,cnt3\[y\]++,cnt3\[e\[k\].to\]++,tot3++;
				tot4=cal(tot4+cnt4\[e\[k\].to\]),cnt4\[e\[k\].to\]++;
			}
			mark\[y\]=1;
		}
		for(int j=last\[x\];j;j=e\[j\].nex)
		{
			if(pos\[y=e\[j\].to\]<i) continue;
			for(int k=last\[y\];k;k=e\[k\].nex) cnt4\[e\[k\].to\]=0;
			mark\[y\]=0;
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&K),fac\[0\]=inv\[0\]=inv\[1\]=1;
	for(int i=1;i<=m;i++) scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
	for(int i=1;i<=n;i++) fac\[i\]=(ll)fac\[i-1\]*i%mod;
	for(int i=2;i<=n;i++) inv\[i\]=(ll)(mod-mod/i)*inv\[mod%i\]%mod;
	for(int i=2;i<=n;i++) inv\[i\]=(ll)inv\[i-1\]*inv\[i\]%mod;
	if(K==1) return !printf("%d\\n",m);
	if(K==2)
	{
		for(int i=1;i<=n;i++) ans=cal(ans+C(deg\[i\],2));
		return !printf("%d\\n",ans);
	}
	Solve();
	if(K==3)
	{
		for(int i=1;i<=n;i++)
		{
			ans=cal(ans+C(deg\[i\],3));
			for(int k=last\[i\];k;k=e\[k\].nex)
				if(e\[k\].to>i) ans=cal(ans+(ll)(deg\[i\]-1)*(deg\[e\[k\].to\]-1)%mod);
		}
		return !printf("%d\\n",cal(ans-2ll*tot3%mod));
	}
	for(int i=1;i<=n;i++) if(deg\[i\]>2) num=cal(num+(ll)(deg\[i\]-2)*cnt3\[i\]%mod);
	for(int i=1;i<=n;i++) ans=cal(ans+C(deg\[i\],4));
	for(int i=1;i<=n;i++) if(deg\[i\]>2)
		for(int k=last\[i\];k;k=e\[k\].nex) ans=cal(ans+(ll)C(deg\[i\]-1,2)*(deg\[e\[k\].to\]-1)%mod);
	for(int i=1,v;i<=n;i++)
		for(int k=last\[i\],v=0;k;k=e\[k\].nex)
			ans=cal(ans+(ll)(deg\[e\[k\].to\]-1)*v%mod),v=cal(v+deg\[e\[k\].to\]-1);
	ans=cal(ans-3ll*((ll)num+tot3+tot4)%mod+mod);
	printf("%d\\n",ans);
	return 0;
}