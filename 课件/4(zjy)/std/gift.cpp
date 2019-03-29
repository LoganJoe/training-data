#include <cstdio>
#include <cstring>
#define LL long long 
using namespace std;
const int mod=1e9+7;
int c[10][10],row[10],col[10];
LL ksm(LL a,LL k)
{
	LL ans=1;
	for (;k;k>>=1,a=a*a%mod)
	  if (k&1) ans=ans*a%mod;
	return ans;
}
void work(int n,int m,int h,int w)
{
	memset(c,0,sizeof(c));
	for (int i=0;i<=5;i++)
	{
		c[i][0]=1;
		for (int j=1;j<=i;j++) c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	int all=h*w;LL res=0;
	for (int i=0;i<(1<<all);i++)
	{
		for (int j=0;j<=3;j++) row[j]=col[j]=0;
		for (int j=0;j<all;j++) if (i&(1<<j)) row[j/w]++,col[j%w]++;
		LL ans=1;
		for (int j=0;j<=w-1;j++)
		{
			int z=(m-j+w-1)/w;
			LL x=0;
			for (int k=0;k<=col[j];k++) x=(x+ksm(c[col[j]][k],z))%mod;
			ans=ans*x%mod;
		}
		for (int j=0;j<=h-1;j++) row[j]=w-row[j];
	    for (int j=0;j<=h-1;j++)
	    {
	    	int z=(n-j+h-1)/h;
			LL x=0;
			switch (row[j])
			{
				case 0:x=1;break;
				case 1:x=0;break;
				case 2:x=ksm(2,z)-2;break;
				case 3:x=2*ksm(3,z)-6*ksm(2,z)+6;break;
				default:x=ksm(6,z)+ksm(4,z)*2-16*ksm(3,z)+24*ksm(2,z)-14;
			}
			x=(x%mod+mod)%mod;
			ans=ans*x%mod;
		}
		res=(res+ans)%mod;
	}
	printf("%lld",res);
}
int main()
{
	int n,m,h,w;scanf("%d%d%d%d",&n,&m,&h,&w);
	work(n,m,h,w);
}
