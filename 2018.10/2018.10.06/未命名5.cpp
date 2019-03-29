#include<bits/stdc++.h>
#define N 1000005
#define ll long long
int n,m,k;
ll A[N];
bool check(int x)
{
	for(int i=1;i+x-1<=n;i++) if(A[i+x-1]-A[i-1]>=1ll*k*x) return 1;
	return 0;
}
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&A[i]),A[i]=A[i-1]+A[i];
	while(m--)
	{
		scanf("%d",&k);
		int l=1,r=n,ans=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		printf("%d ",ans);
	}
	return puts(""),0;
}
