#include<bits/stdc++.h>
#define db double
#define N 1000005
#define eps 1e-7
int n, sum[N], ans = 1e9;
char s[N];
struct node
{
	int x; db y;
	friend bool operator <(node t1, node t2)
	{
		return t1.y < t2.y || t1.y == t2.y && t1.x < t2.x;
	}
}A[N];
db f, Min = 1e18;
int main ()
{
	freopen ("real.in", "r", stdin);
	freopen ("real.out", "w", stdout);
	scanf ("%lf", &f);
	scanf ("%s", s + 1); n = strlen (s + 1);
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (s[i] == '1');
	for (int i = 1; i <= n; i++) A[i] = { i,1.*i*f - sum[i] };
	std::sort (A + 1, A + 1 + n);
	for (int i = 1; i < n; i++)
	{
		db slope = (A[i].y - A[i + 1].y) / (1.*A[i].x - A[i + 1].x);
		slope = fabs (slope);
		if (Min - slope > eps || (fabs (Min - slope) < eps && ans > A[i].x)) 
			Min = slope, ans = std::min(A[i].x, A[i+1].x);
	}
	printf ("%d\n", ans);
}
