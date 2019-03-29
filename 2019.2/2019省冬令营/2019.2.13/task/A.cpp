#include <bits/stdc++.h>

int k, a, b, c;

void solve () {
	printf ("%d\n", a + b + c + 4);
	puts ("1 2 1");
	puts ("1 3 1");
	puts ("1 4 1");
	int n = 4;
	for (int i = 1; i <= a; ++i)
		printf ("2 %d 100000\n", ++n);
	for (int i = 1; i <= b; ++i)
		printf ("3 %d 100000\n", ++n);
	for (int i = 1; i <= c; ++i)
		printf ("4 %d 100000\n", ++n);
}

int main () {
	freopen ("diameter.in", "r", stdin);
	freopen ("diameter.out", "w", stdout);
	scanf ("%d", &k);
	for (int i = 1; i <= 4996; ++i)
		for (int j = 1; i + j <= 4996; ++j)
			if (k >= (i * j) && (k - i * j) % (i + j) == 0) {
				a = (k - i * j) / (i + j);
				b = i;
				c = j;
				if (a + b + c <= 4996) {
					solve ();
					return 0;
				}
			}
}
