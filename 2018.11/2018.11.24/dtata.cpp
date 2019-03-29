#include<bits/stdc++.h>
int n=250000,m=500000,c=500000,p[500005];
int main()
{
	freopen("sub.in","w",stdout);
	srand(time(0));
	printf("%d %d %d\n",n,m,c);
	for(int i=1;i<=n;i++) p[i]=i;
	std::random_shuffle(p+1,p+1+n);
	for(int i=1;i<=n;i++) printf("%d ",p[i]);
	puts("");
	for(int i=1;i<=m;i++) printf("%d ",rand()%c+1);
	puts("");
}
