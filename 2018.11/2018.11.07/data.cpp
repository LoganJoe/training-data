#include<bits/stdc++.h>
int n=1000000;
int R(){return 1ll*rand()<<15ll|rand();}
int main()
{
	freopen("equation.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,n);
	for(int i=2;i<=n;i++)
	{
		printf("%d %d\n",R()%(i-1)+1,R()%1002+1);
	}
	for(int i=1;i<=n;i++)
	{
		int op=R()%2;
		if(op==1) printf("%d %d %d\n",R()%n+1,R()%n+1,R()%1002+1);
		else printf("%d %d\n",R()%n+1,R()%1002+1);
	}
}
