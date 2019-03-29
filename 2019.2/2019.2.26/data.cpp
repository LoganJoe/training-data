#include<bits/stdc++.h>
int n = 100000;
int main ()
{
	srand (time (0));
	freopen ("array.in", "w", stdout);
	printf ("%d\n", n);
	for (int i = 1; i <= n; i++) printf ("%d ", rand ()%50000 + 50000);
}
