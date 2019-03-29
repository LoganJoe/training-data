#include<bits/stdc++.h>
int n;
int main()
{
	srand(time(0)+233);
	freopen("yuan1.in","r",stdin);
	freopen("park.in","w",stdout);
	scanf("%d",&n);
	printf("%d\n",n);
	for(int i=1,a;i<=n;i++) scanf("%d",&a),printf("%d ",a*8*(rand()%2?1:-1));
	puts("");
	for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b),printf("%d %d\n",a,b);
	printf("%d\n",1000);
	for(int i=1;i<=1000;i++)
	{
		int opt=rand()%2+1;printf("%d ",opt);
		//int opt=1;printf("%d ",opt);
		if(opt==1)printf("%d %d\n",rand()%n+1,rand()%n+1);
		else printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand()*(rand()%2?1:-1));
	}
}
