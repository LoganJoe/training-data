#include<bits/stdc++.h>
int n=100000;
int r (int n) { return (1ll * (rand () << 15ll) + rand ()) % n ;}
int main ()
{
	freopen("sequence.in","w",stdout);
	srand (time (0));
	printf ("%d %d %d\n", n, n * 5, 3);
	for (int i = 1; i <= n; i++) printf ("%d\n", rand ());
	for (int i = 1; i <= n * 5; i++)
	{
		printf ("%d %d\n", r (n) + 1, r (n) + 1);
	}
}
