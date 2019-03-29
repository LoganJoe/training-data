#include<bits/stdc++.h>
int n,Q,T=3;
#define M 100005
int main()
{
	srand(time(0)+233);
	freopen("test.in","w",stdout);
	while(T--)
	{
		n=50000,Q=50000;
		printf("%d %d\n",n,Q);
		while(Q--)
		{
			int opt=rand()%2;
			printf("%d ",opt);
			if(opt==1)
			{
				printf("%d %d %d\n",rand()*rand()%M+1,rand()*rand()%M+1,rand()*rand()%M+1);
			}
			else printf("%d\n",rand()%n+1);
		}
	}
	puts("0 0");
}
