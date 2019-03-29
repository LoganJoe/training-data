#include<bits/stdc++.h>
int T=100,n;
int main()
{
	freopen("coin.in","w",stdout);
	srand(time(0));
	std::cout<<"1513543247857 1788945558754"<<"\n";
	printf("%d\n",T);
	while(T--)
	{
		for(int i=1;i<=100;i++) printf("%c",rand()%2?'1':'0');
		puts("");
	}
}
