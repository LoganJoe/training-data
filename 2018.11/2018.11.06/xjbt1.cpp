#include<bits/stdc++.h>
#define N 1000005
#define ll long long
int n,m;
ll S,totK,x,Sum;
struct node
{
	int k,b;
	friend bool operator <(node t1,node t2)
	{
		return 1ll*t1.k*x+t1.b<1ll*t2.k*x+t2.b;
	}
}A[N];
ll check(int x)
{
	std::sort(A+1,A+1+n);
	std::reverse(A+1,A+1+n);
	totK=0;Sum=-S;
	for(int i=1;i<=m;i++) 
	if(1ll*A[i].k*x+A[i].b>0 || i==1) 
	{
		Sum+=1ll*A[i].k*x+A[i].b,totK+=A[i].k;
		if(Sum>=1e18) return 1e18; 
	}
	return Sum;
}
int main()
{
	freopen("merchant.in","r",stdin);
	freopen("merchant.ans","w",stdout);
	scanf("%d%d%lld",&n,&m,&S);
	for(int i=1;i<=n;i++) scanf("%d%d",&A[i].k,&A[i].b);
	if(check(0)>=0) return puts("0");
	x=5e8;
	while(1)
	{
		ll re=check(x);
		if(re/totK==0 && re>=0) break;
		if(re<0) 
			x+=std::max((-re/totK),1ll);
		else x-=std::max((re/totK),1ll);
	}
	std::cout<<x<<"\n";
}
