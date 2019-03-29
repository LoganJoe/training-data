#include<bits/stdc++.h>
#define N 105
int n,m,A[N][N*N*2],Min[N][N*N*2],sum[N*N],ans=1e9;
char s[N][N*N];
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			A[i][j]=A[i][j+m]=s[i][j]-'0',Min[i][j]=Min[i][j+m]=1e9;
	for(int i=1;i<=n;i++)
	{
		for(int j=1,lst=1e9;j<=m<<1;j++,lst++)
		{
			if(A[i][j]) lst=0;
			Min[i][j]=std::min(Min[i][j],lst);
		}
		for(int j=m<<1,lst=1e9;j>=1;j--,lst++)
		{
			if(A[i][j]) lst=0;
			Min[i][j]=std::min(Min[i][j],lst);
		}
		for(int j=1;j<=m;j++) 
			Min[i][j]=std::min(Min[i][j],Min[i][j+m]);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) sum[i]+=Min[j][i];
	for(int i=1;i<=m;i++) ans=std::min(ans,sum[i]);
	if(ans>=1e9) puts("-1");
	else printf("%d\n",ans);
}
/*
4 6
101010
000100
100000
000001
*/
