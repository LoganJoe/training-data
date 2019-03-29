#include<bits/stdc++.h>
int n = 500000;
int Rand(){return 1ll * rand() << 15 | rand();}
std::map<int,int>mp;
int main()
{
	freopen("civilization.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,n/5);
	for(int i=2;i<=n;i++) 
		printf("%d %d\n",i,rand()%(i-1)+1);
	for(int i=1;i<=n/5;i++)
	{
		int m;
		printf("%d ", m = rand()% 20 + 1);
		for(int j=1;j<=m;j++)
		{
			int k = rand() % n + 1;
			if(mp[k]) j--;
			else mp[k] = 1, printf("%d ",k);
		}
		puts("");
		mp.clear();
			 
	}
} 	
