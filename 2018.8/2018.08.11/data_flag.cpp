#include<bits/stdc++.h>
int n=180000,m=1e9;
int main()
{
	srand(time(0));
	freopen("flag.in","w",stdout);
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++) 
	{
		printf("%d %d\n",rand()*rand()%m+1,rand()*rand()%m+1);
	}
}
