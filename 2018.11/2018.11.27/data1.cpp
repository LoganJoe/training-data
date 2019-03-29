#include<bits/stdc++.h>
int N=200;
int main()
{
	freopen("a.in","w",stdout);
	srand(time(0));
	printf("%d\n",N);
	for(int i=1;i<=N;i++) printf("%d ",(rand()<<15ll)|rand()%1000000000+1);
	
	
}
