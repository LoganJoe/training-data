#include<bits/stdc++.h>
#define N 1000005
#define mod 998244353
int Case,n=1e6,m,k=1e6;
int main()
{
	freopen("path.in","w",stdout);
	srand(time(0));
	puts("1");
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%lld %d %d\n",1ll*rand()*rand()%(i-1)+1,i,rand());
	printf("%d\n",k);
	for(int i=1;i<=k;i++) printf("%d\n",1ll*rand()*rand()%n+1);
		
}
