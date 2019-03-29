#include<bits/stdc++.h>
#define mod 1000000007
int n,K;
int mul(int x){return x>=mod?x-mod:x;}
namespace solve1
{
	const int N=100;
	int f[2][N<<1|1][N<<1|1][N<<1|1],ans;
	void Main()
	{
		f[0][N][N][N]=1;
		int now=0;
		for(int i=0;i<n;i++,now^=1)
			for(int j=std::max(N-K,N-i);j<=N;j++)
				for(int k=N;k<=std::min(j+K,N+2*i);k++)
					for(int l=j;l<=k;l++)
					{
						f[now^1][std::min(j,l+1)][std::max(k,l+1)][l+1]=mul(f[now^1][std::min(j,l+1)][std::max(k,l+1)][l+1]+f[now][j][k][l]);
						f[now^1][std::min(j,l+2)][std::max(k,l+2)][l+2]=mul(f[now^1][std::min(j,l+2)][std::max(k,l+2)][l+2]+f[now][j][k][l]);
						f[now^1][std::min(j,l-1)][std::max(k,l-1)][l-1]=mul(f[now^1][std::min(j,l-1)][std::max(k,l-1)][l-1]+f[now][j][k][l]);
						f[now][j][k][l]=0;
						//printf("%d\n",now);
					}
			for(int j=std::max(N-K,N-n);j<=N;j++)
				for(int k=N;k<=std::min(j+K,N+2*n);k++)
					for(int l=j;l<=k;l++) if(k-j<=K) ans=mul(ans+f[now][j][k][l]);
		printf("%d\n",ans);
	}
}
namespace solve2
{
	const int N=300;
	int f[2][N<<1|1][N<<1|1],ans=0;
	void Main()
	{
		f[0][N][N]=1;
		int now=0;
		for(int i=0;i<n;i++,now^=1)
			for(int j=std::max(N-K,N-i);j<=N;j++)
				for(int k=j;k<=std::min(j+K,N+2*i);k++)
				{
					if(k+1<=j+K) f[now^1][j][k+1]=mul(f[now^1][j][k+1]+f[now][j][k]);
					if(k+2<=j+K) f[now^1][j][k+2]=mul(f[now^1][j][k+2]+f[now][j][k]);
					if(k-1>=N-K) f[now^1][std::min(j,k-1)][k-1]=mul(f[now^1][std::min(j,k-1)][k-1]+f[now][j][k]);
					f[now][j][k]=0;
				}
		for(int j=std::max(N-K,N-n);j<=N;j++)
			for(int k=j;k<=std::min(j+K,N+2*n);k++) ans=mul(ans+f[now][j][k]);		
		printf("%d\n",ans);
	}		
}
int main()
{
	freopen("val.in","r",stdin);
	freopen("val.out","w",stdout);
	scanf("%d%d",&n,&K);
	if(K==1) return puts("2"),0;
	if(n<=100 && K<=100) 
	return solve1::Main(),0;
	else return solve2::Main(),0;
}
