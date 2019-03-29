#include<bits/stdc++.h>
int n=5000,lst;
int main()
{
	freopen("a.in","w",stdout);
	srand(time(0));
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		std::cout<<(lst+=rand()%300)<<" "<<1ll*rand()*rand()%1000000000<<"\n";
	}
}
