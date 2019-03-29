#include<bits/stdc++.h>
#define N 1000005
int n,p,q,r,ans;
char s[N];
namespace solve1
{
	int sum3[N];
	void Main()
	{
		for(int i=n,t=1;i;i--,t=t*10%r) sum3[i]=(sum3[i+1]+(s[i]-'0')*t)%r;
		for(int i=1,sum=0;i<=n;i++) 
		{
			sum=(sum*10+(s[i]-'0'))%p;
			if(!sum && (s[i]!=0 || i==1))
				for(int j=i+1,t=0;j<=n;j++)
				{
					t=(t*10+(s[j]-'0'))%q;
					if(!t && !sum3[j+1] &&(s[j+1]!='0' || j+1==n)) ans++;
				}
		}
		printf("%d\n",ans);
	}
}
namespace solve2
{
	int sum1[N],sum2[N],sum3[N],tot[N];
	void Main()
	{	
		//for(int i=n,t=1;i;i--,t=t*10%p) sum1[i]=(sum1[i+1]+(s[i]-'0')*t)%p;
		for(int i=1;i<=n;i++) sum1[i]=(sum1[i-1]*10+(s[i]-'0'))%p;
		for(int i=n,t=1;i;i--,t=t*10%q) sum2[i]=(sum2[i+1]+(s[i]-'0')*t)%q;
		for(int i=n,t=1;i;i--,t=t*10%r) sum3[i]=(sum3[i+1]+(s[i]-'0')*t)%r;
		for(int i=2;i<=n;i++) 
				if(!sum3[i] &&(s[i]!='0' || i==n)) tot[sum2[i]]++;
		for(int i=1;i<n;i++)
		{
			if(!sum3[i+1] && (s[i+1]!='0' || i+1==n)) tot[sum2[i+1]]--;
			if(!sum1[i] && (s[i]!='0' || i==1)) ans+=tot[sum2[i+1]];
		}
		printf("%d\n",ans);
	}
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d%d%d",&n,&p,&q,&r);
	scanf("%s",s+1);
	//if(n<=1000) return solve1::Main(),0;
	//else 
	return solve2::Main(),0;

}
