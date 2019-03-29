#include<bits/stdc++.h>
int n=100,m=10000;
struct node
{
	int op,x,y;
}t[10050];
int main()
{
	freopen("journey.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<n;j++) printf("%d ",(i^j)?rand()+1:0);
	for(int i=1;i<=200;i++) 
		t[i]={1,rand()%n+1,rand()%n+1};
	for(int i=201;i<=m;i++) t[i]={2,rand()%n+1,rand()%n+1};
	std::random_shuffle(t+1,t+1+m);
	for(int i=1;i<=m;i++)
	{
		while(t[i].x==t[i].y) t[i].y=rand()%n+1;
		printf("%d %d %d\n",t[i].op,t[i].x,t[i].y);
	}
}
