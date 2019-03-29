#include<bits/stdc++.h>
#define N 20

int n, c[N], p[N], l[N];

int gcd (int a, int b) { return !b ? a : gcd (b, a%b); }
void exgcd (int a, int b, int &x, int &y)
{
	if (!b) { x = 1, y = 0; return; }
	exgcd (b, a%b, x, y);
	int t=x,x=y,y-
}
int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d%d%d", &c[i], &p[i], &l[i]);

}
