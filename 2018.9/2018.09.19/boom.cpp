#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n,top1,top2;
ll ans,tim;
struct node
{
	int a,b,c;
	friend bool operator <(node t1,node t2)
	{
		return t1.a+t1.b<t2.a+t2.b;
	}
}s[N];
struct info
{
	ll t;int id;
	friend bool operator <(info t1,info t2)
	{
		return t1.t<t2.t;
	}
}p1[N],p2[N];
int main()
{
	freopen("boom.in","r",stdin);
	freopen("boom.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&s[i].a,&s[i].b,&s[i].c);
	std::sort(s+1,s+1+n);
	tim=0;
	for(int i=1;i<=n;i++) tim+=s[i].a,p1[++top1]={tim,i};
	std::sort(p1+1,p1+1+n);
	tim=0;
	for(int i=1;i<=n;i++) tim=std::max(tim+s[p1[i].id].b,p1[i].t+s[p1[i].id].b),p2[++top2]={tim,i};
	std::sort(p2+1,p2+1+n);
	tim=0;
	for(int i=1;i<=n;i++) tim=std::max(tim+s[p2[i].id].c,p2[i].t+s[p2[i].id].c),ans=std::max(ans,tim);
	std::cout<<ans<<"\n";
}
