#include<bits/stdc++.h>
int n=200000,Q=200000;
long long R(){return 1ll*rand()*rand();}
int main()
{
	freopen("icekingdom.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,Q);
	for(int i=2;i<=n;i++) printf("%lld %d\n",R()%(i-1)+1,i);
	for(int i=1;i<=Q;i++) 
	{
		int l=R()%n+1,r=R()%n+1;
		if(l>r) std::swap(l,r);
		printf("%d %d\n",l,r);
	}
}
