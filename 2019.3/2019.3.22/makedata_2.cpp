#include<bits/stdc++.h>
int n = 1000;
int main()
{
	freopen("tree.in", "w", stdout);
	srand(time(0));
	printf("%d %d\n", n, n*10);
	for(int i=2;i<=n;i++)
		printf("%d %d\n", i, rand() % (i - 1) + 1);
}