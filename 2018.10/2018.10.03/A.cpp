#include<bits/stdc++.h>
#define N 3005
int n,m,k,f[N][N],g[N][N],A[N],B[N],C[N],t1[N],t2[N],ans;
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&B[i]);
	scanf("%d",&k);
	for(int i=1;i<=k;i++) scanf("%d",&C[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(A[i]==B[j]) f[i][j]=f[i-1][j-1]+1;
			else f[i][j]=std::max(f[i][j-1],f[i-1][j]);
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			if(A[i]==B[j]) g[i][j]=g[i+1][j+1]+1;
			else g[i][j]=std::max(g[i][j+1],g[i+1][j]);
	if(!k) return printf("%d\n",f[n][m]),0;
	for(int i=1;i<=n;i++) 
		for(int j=i,pos1=1,pos2=1;j<=n;j++)
		{
			if(A[j]==C[pos1]) pos1++;
			if(B[j]==C[pos2]) pos2++;
			if(pos1==k+1) t1[i]=j;
			if(pos2==k+1) t2[i]=j;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
			if(t1[i] && t2[j])
				ans=std::max(ans,f[i-1][j-1]+g[t1[i]+1][t2[j]+1]+k);
	printf("%d\n",ans==0?-1:ans);
}
