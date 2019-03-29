#include<cstdio>
#include<cstring>
#define MN 24
int mod,f[2][(1<<MN)+5],v[MN+5],ps[MN+5];
const int ANS[25]={0,1,2,3,3,3,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6};
void rw(int&a,int b){a+=b;if(a>=mod)a-=mod;}
int inv(int x)
{
	int r=1,y=mod-2;
	for(;y;y>>=1,x=1LL*x*x%mod)if(y&1)r=1LL*r*x%mod;
	return r;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,i,j,k,p,q,s,ans=0,cnt=1;
	scanf("%d%d",&n,&mod);
	for(f[p=0][q=i=1]=1;i<n;++i,p^=1,q^=1)
	{
		memset(f[q],0,sizeof(int)*(1<<i+1));
		for(j=1;j<1<<i;++j)if(f[p][j])
		{
			for(s=k=0;k<i;++v[s],++k)if(j&(1<<k))ps[++s]=k;
			for(k=1;k<s;++k)
			{
				int t=(1<<ps[k+1]+1)-1;
				rw(f[q][((j^(j&t))<<1)+(j&t)],1LL*f[p][j]*v[k]%mod);
			}
			rw(f[q][j|(1<<i)],1LL*f[p][j]*v[s]%mod);
			memset(v,0,sizeof(int)*(s+1));
		}
	}
	for(i=1;i<1<<n;++i)if(f[p][i])
	{
		for(s=j=0;j<n;++j)if(i&(1<<j))++s;
		rw(ans,1LL*f[p][i]*s%mod);
	}
	for(i=1;i<n;++i)cnt=1LL*cnt*i%mod;
	printf("%d\n%d",ANS[n],1LL*ans*inv(cnt)%mod);
}
