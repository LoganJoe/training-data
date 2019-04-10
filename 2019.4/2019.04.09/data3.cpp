#include<bits/stdc++.h>
int n=1000;
int main()
{
	freopen("fittest.in","w", stdout);
	srand(time(0));
	printf("%d %d\n", n, rand()%8000);
	for(int i=1;i<=n;i++) 
	{
		printf("%d %d\n", rand(), rand()/2);
	}
}
