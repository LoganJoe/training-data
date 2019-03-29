#include<bits/stdc++.h>
#define ll long long
int T,mark;
ll n,k,cnt;
struct node
{
	ll x,tot;
	friend bool operator <(node t1,node t2) {return t1.x<t2.x;}
};
ll divide()
{
	std::priority_queue<node> q;
	q.push({n,1});
	while(!q.empty())
	{
		node t=q.top();q.pop();
		cnt+=t.tot;if(cnt>=k) return t.x;
		if(t.x&1) q.push({(t.x>>1)+1,t.tot}),q.push({t.x>>1,t.tot});
		else q.push({t.x>>1,t.tot<<1});
	}
}
int main()
{
	freopen("segment.in","r",stdin);
	freopen("segment.out","w",stdout);
	for(scanf("%d",&T);T--;)
	{
		scanf("%lld%lld",&n,&k);
		cnt=mark=0;printf("%lld\n",divide());
	}
}

