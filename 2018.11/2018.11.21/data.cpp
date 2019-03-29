#include<bits/stdc++.h>
int n=100000,m=100000,mod=1000000000;
int main()
{
	freopen("a.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
	{
		int l=rand()%mod+1,r=rand()%mod+1;
		if(l>r) std::swap(l,r);
		std::cout<<l<<" "<<r<<"\n";
	}
	for(int i=1;i<=m;i++) printf("%d\n",rand()%mod+1);
}
