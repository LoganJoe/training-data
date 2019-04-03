#include<bits/stdc++.h>
int n, a, A[1000];
int rd (int x) { return (rand () ^ (rand () << 15)) % x; }
int main ()
{
	srand (time (0));
	freopen ("lcs.in", "w", stdout);
	//	n=rd(1000)+1000;
	n = 1000;
	printf ("%d\n", n);
	int P = rand () % 400 + 1;
	for (int i = 1; i <= n; i++) A[i] = i << 1;
	for (int i = 1; i <= P; i++) std::swap (A[i], A[rand () % n + 1]);
	for (int i = 1; i <= n; i++) printf ("%d ", A[i]);
	puts ("");
	for (int i = 1; i <= n; i++) A[i] = i << 1;
	for (int i = 1; i <= P-57; i++) std::swap (A[i], A[rand () % n + 1]);
	for (int i = 1; i <= n; i++) printf ("%d ", A[i]);
	puts ("");
	for (int i = 1; i <= n; i++) A[i] = i << 1;
	for (int i = 1; i <= P+27; i++) std::swap (A[i], A[rand () % n + 1]);
	for (int i = 1; i <= n; i++) printf ("%d ", A[i]);
	puts ("");
	for (int i = 1; i <= n; i++) A[i] = i << 1;
	for (int i = 1; i <= P+47; i++) std::swap (A[i], A[rand () % n + 1]);
	for (int i = 1; i <= n; i++) printf ("%d ", A[i]);
	puts ("");
	return 0;
}
