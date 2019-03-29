#include<bits/stdc++.h>
#define ll long long
int n=1e5,m=5e4;
int main()
{
	freopen("merchant.in","w",stdout);
	srand(time(0));
	printf("%d %d ",n,m);
	ll S=1ll*rand()*rand()*rand()*rand();
	std::cout<<S<<"\n";
	for(int i=1;i<=n;i++)
	{
		int k=rand()<<15ll|rand();
		int b=rand()<<15ll|rand();
		k=k%2000000-1000000,b=b%200000000-100000000;
		printf("%d %d\n",k,b);
	}
}
