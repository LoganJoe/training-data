#include<bits/stdc++.h>
int n=2000,m=18,Q=2000;
int main()
{
	freopen("yukari.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++) printf("%d ",rand());
	printf("\n%d\n",Q);
	for(int i=1;i<=Q;i++)
	{
		int l=rand()%n+1,r=rand()%n+1;
		if(r<l) std::swap(l,r);
		printf("%d %d\n",l,r);
	}
}
