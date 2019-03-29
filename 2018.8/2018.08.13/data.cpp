#include<bits/stdc++.h>
int n=200000,Q=20000;
int main()
{
	freopen("message.in","w",stdout);
	srand(time(0));
	printf("%d\n",n);
	for(int i=1;i<=n;i++) 
	{
		if(i==8) printf("0 ");
		else if(i==1) printf("8 ");
		else printf("%d ",rand()%(i-1)+1);
	}
	printf("%d\n",Q);
	while(Q--)
	{
		int opt,a,b,c;
		opt=rand()%2+1,a=rand()%n+1,b=rand()%n+1,c=rand()%(n/2);
		if(opt==1) printf("%d %d %d %d\n",opt,a,b,c);
		else printf("%d %d\n",opt,a);
	}
}
