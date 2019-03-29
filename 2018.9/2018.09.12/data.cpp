#include<bits/stdc++.h>
int n,A[3];
int main()
{
	freopen("B.in","w",stdout);
	srand(time(0));
	n=2000;printf("%d\n",n);
	for(int i=1;i<=n;i++) 
	{
		for(int j=0;j<3;j++) A[j]=rand()&1;
		for(int j=0;j<3;j++)putchar(j+'0');
		puts("");
	}
}
