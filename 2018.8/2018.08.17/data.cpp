#include<bits/stdc++.h>
int n=2000;
int main()
{
	srand(time(0));
	freopen("circle.in","w",stdout);
	printf("%d\n",n);
	for(int i=1;i<=n;i++) printf("%d\n",rand()*rand()%50000000+1);
}
