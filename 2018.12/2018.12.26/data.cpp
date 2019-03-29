#include<bits/stdc++.h>
int n=2000;
int main()
{
	srand(time(0));
	freopen("a.in","w",stdout);
	printf("%d\n",n);
	for(int i=1;i<=n;i++) 
	{
		int L=1e9-rand(),R=1+rand();
		std::cout<<R<<" "<<L<<"\n";
	}
}
