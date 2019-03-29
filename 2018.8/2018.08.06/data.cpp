#include<bits/stdc++.h>
int n,m;
int main()
{
	freopen("spaceship.in","w",stdout);
	srand(time(0));
//	n=rand()%400+1;m=rand()%20+1;
	n=rand()%400+1,m=rand()%2+2;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++) printf("%d ",rand()%1000+1);
	puts("");
}
