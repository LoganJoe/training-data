#include<bits/stdc++.h>
int d=20,n=5000,m=1000000;
int main()
{
	srand(time(0));
	freopen("C.in","w",stdout);
	printf("%d %d %d\n",d,n,m);
	for(int i=1;i<=m;i++)
	{
		printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand()%d+1);
	}
}
