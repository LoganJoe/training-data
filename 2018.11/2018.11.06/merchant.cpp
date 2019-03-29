#include<bits/stdc++.h>
#define N 1000005
#define ll long long
int n,m,k[N],b[N];
ll S,A[N];
bool check(int x)
{
	int cnt=0;
	for(int i=1;i<=n;i++) 
	{
		A[++cnt]=1ll*k[i]*x+b[i];
		if(A[cnt]<0) cnt--;
	}
	std::sort(A+1,A+1+cnt);
	ll Sum=0;
	for(int i=1;i<=m && i<=cnt;i++) 
	{
		if(A[cnt-i+1]>0) Sum+=A[cnt-i+1];
		if(Sum>=1e18) return 1;
	}
	return Sum>=S;
}
int main()
{
	freopen("merchant.in","r",stdin);
	freopen("merchant.out","w",stdout);
	scanf("%d%d%lld",&n,&m,&S);
	for(int i=1;i<=n;i++) scanf("%d%d",&k[i],&b[i]);
	if(check(0)) return puts("0");
	int l=0,r=1e9,res=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	std::cout<<res<<"\n";
	
}
