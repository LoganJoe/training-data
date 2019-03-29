#include<cstdio>
#define MN 200000
#define MOD 998244353
int c[MN+5],f[MN+5][2][2][2],p[MN+5];
inline void rw(int&x,int y){if((x+=y)>=MOD)x-=MOD;}
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int n,m,i,j,k,l,ans=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d",&c[i]);
	for(p[0]=i=1;i<=n;++i)p[i]=(p[i-1]+p[i-1])%MOD;
	f[0][0][0][0]=1;
	for(i=0;i<n;++i)for(j=0;j<2;++j)for(k=0;k<2;++k)for(l=0;l<2;++l)if(f[i][j][k][l])
	{
		if(c[i+1]!=0)
			rw(f[i+1][j|1][k][l^1],1LL*f[i][j][k][l]*(k?p[i-1]:p[i])%MOD),
			rw(f[i+1][j  ][k][l  ],1LL*f[i][j][k][l]*(k?p[i-1]:0)%MOD);
		if(c[i+1]!=1)
			rw(f[i+1][j][k|1][l^1],1LL*f[i][j][k][l]*(j?p[i-1]:p[i])%MOD),
			rw(f[i+1][j][k  ][l  ],1LL*f[i][j][k][l]*(j?p[i-1]:0)%MOD);
	}
	for(i=0;i<2;++i)for(j=0;j<2;++j)rw(ans,f[n][i][j][m]);
	printf("%d",ans);
}
