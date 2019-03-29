#include<bits/stdc++.h>
#define N 10005
int T,n,A[N],sum1[N],sum2[N],st[N];
int main()
{
	freopen("come.in","r",stdin);
	freopen("come.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&A[i]);
		sum1[0]=sum2[n+1]=0;
		for(int i=1;i<=n;i++) sum1[i]=sum1[i-1]+A[i];
		for(int i=n;i>=1;i--) sum2[i]=sum2[i+1]+A[i];
		for(int i=1;i<=n;i++) 
		{
			if(sum1[i]-sum2[i]>0) st[i]=1;
			if(sum1[i]-sum2[i]==0) st[i]=0;
			if(sum1[i]-sum2[i]<0) st[i]=-1;
		}
		if(st[n/2+1]==1) puts("win");
		if(st[n/2+1]==0) puts("tie");
		if(st[n/2+1]==-1) puts("lose");
	}
}
