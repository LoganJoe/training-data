#include<cstdio>
#define ll unsigned long long
#define MN 2000000
char s[MN+5];
ll z[MN+5],Z[MN+5];
int a[MN+5],b[MN+5],c[MN+5],d[MN+5];
inline ll ran()
{
	static ll x=23333;
	return x^=x<<13,x^=x>>17,x^=x<<5;
}
int main()
{
	freopen("operation.in","r",stdin);
	freopen("operation.out","w",stdout);
	int n,k,q,i,l,r,ans;
	scanf("%d%d%d%s",&n,&k,&q,s+1);
	for(i=0;i<k;++i)z[i]=ran();
	for(i=1;i<=n;++i)
	{
		a[i]=a[i-1];Z[i]=Z[i-1];
		if((s[i]-='0')^s[i-1])
		{
			Z[i]^=z[i%k];
			a[i]-=b[i%k];
			a[i]+=b[i%k]=i/k-b[i%k];
		}
		c[i]=b[(i+1)%k];d[i]=b[i%k];
	}
	while(q--)
	{
		scanf("%d%d",&l,&r);
		if(Z[r]^Z[l]^(s[r]*z[(r+1)%k])^(s[l]*z[l%k])){puts("-1");continue;}
		ans=a[r]-a[l];
		if(s[r])ans+=(r+1)/k-2*c[r];
		if(s[l])ans+=2*d[l]-l/k;
		printf("%d\n",ans);
	}
}
