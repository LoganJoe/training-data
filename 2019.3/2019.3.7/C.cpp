#include<bits/stdc++.h>
#define ll long long
#define N 2000005
#define mod 1000000007
#define inv2 500000004
int n;
ll sum, ans;
struct point
{
	ll x, y;
	point operator +(const point &a) const { return { x + a.x, y + a.y }; }
	point operator -(const point &a) const { return { x - a.x, y - a.y }; }
	point operator *(const ll &a) const { return { x*a, y*a }; }
	ll operator *(const point &a) const { return x * a.y - y * a.x; }
}A[N << 1];
int main ()
{
	freopen ("convex.in", "r", stdin);
	freopen ("convex.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%lld%lld", &A[i].x, &A[i].y);
	for (int i = 1; i <= n; i++) A[i + n] = A[i];
	for (int i = 1; i <= n; i++)
		sum -= A[i] * (A[i + 1] - A[i]);
	for (int i = 1; i <= n; i++)
	{
		ll res = -(A[i] * (A[i + 1] - A[i]) + A[i + 1] * (A[i + 2] - A[i + 1]));
		for (int j = i + 2; j <= n + i - 2; j++)
		{
			ll mult = res - A[j] * (A[i] - A[j]);
			ans = (ans + llabs (sum - 2 * mult)) % mod;
			res -= A[j] * (A[j + 1] - A[j]);
		}
	}
	printf ("%lld\n", ans * inv2 % mod);

}