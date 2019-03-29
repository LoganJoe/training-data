#include<bits/stdc++.h>
#define N 30
#define mod 1000003
int n,m,G[N][N],A[N],ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),G[u][v]=G[v][u]=1;
	for(int i=1;i<=n;i++) A[i]=i;
	do
	{
		int mark=1;
		for(int i=1;i<=n;i++) if(A[A[i]]!=i || G[i][A[i]]==0 ){mark=0;continue;}
		ans+=mark;
		if(ans>=mod) ans-=mod;
	}while(std::next_permutation(A+1,A+1+n));
	printf("%d\n",ans%mod);
}
