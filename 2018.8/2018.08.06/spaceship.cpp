#include<bits/stdc++.h>
#define N 600005
#define M 1005
#define ll long long

int n, m, a[N], b[N], top;
ll f[22][M], ans = 1e18, avg, sum[N];
struct node
{
	ll x, y; int id;
}s[M];
double calc (node a, node b)
{
	return 1.0 * (a.y - b.y) / (a.x - b.x);
}
ll solve ()
{
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= n; j++) f[i][j] = 1e18;
	f[0][0] = 0;
	for (int i = 1; i <= m; i++)
	{
		int l = 1, r = 1;
		s[1] = { sum[i - 1] + avg, f[i - 1][i - 1] + (sum[i - 1] + avg)*(sum[i - 1] + avg), i - 1 };
		for (int j = i; j <= n; j++)
		{
			while (l < r && calc (s[l], s[l + 1]) < 2 * sum[j]) l++;
			int k = s[l].id;
			f[i][j] = f[i - 1][k] + (sum[j] - sum[k] - avg)*(sum[j] - sum[k] - avg);
			node now = { sum[j] + avg, f[i - 1][j] + (sum[j] + avg)*(sum[j] + avg), j };
			while (l < r && calc (s[r], s[r - 1])>calc (now, s[r - 1])) r--;
			s[++r] = now;
		}
	}
	return f[m][n];
}
void solve1 ()
{
	for (int i = 1; i <= n; i++)
	{
		top = 0;
		for (int j = i; j <= n; j++) b[++top] = a[j];
		for (int j = 1; j < i; j++) b[++top] = a[j];
		for (int j = 1; j <= n; j++) sum[j] = sum[j - 1] + b[j];
		for (int j = 1; j <= n; j++) sum[j] *= m;
		ans = std::min (ans, solve ());
	}
	std::cout << ans << "\n";
}
ll sqr (ll x) { return x * x; }
ll cal_ans (int l, int r, int mid)
{
	return sqr (sum[r - 1] - sum[l - 1] - avg) + sqr (sum[l + n - 1] - sum[mid] - avg) + sqr (sum[mid] - sum[r - 1] - avg);
}
ll binary (int L, int R)
{
	int l = R, r = L + n - 2;
	while (r - l > 3)
	{
		int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
		if (cal_ans (L, R, lmid) >= cal_ans (L, R, rmid)) l = lmid;
		else r = rmid;
	}
	ll res = 1e18;
	for (int i = l; i <= r; i++) res = std::min (res, cal_ans (L, R, i));
	return res;
}
void solve3 ()
{
	for (int i = 1, j = 2; i <= n; i++)
	{
		ll tmp = binary(i, j);
		while (j < i + n - 1 && binary (i, j + 1) <= tmp) tmp = binary (i, ++j);
		ans = std::min (ans, tmp);
	}
}
void solve2 ()
{
	for (int i = 1; i <= n; i++) a[i + n] = a[i];
	for (int i = 1; i <= n << 1; i++) sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n << 1; i++) sum[i] *= m;
	if (m == 3) solve3 ();
	for (int i = 1; i <= n; i++)
	{
		int l = i + 1, r = n + i - 2;
		while (l < r)
		{
			int mid = (l + r + 1) >> 1;
			if (sum[mid] - sum[i - 1] <= sum[n + i - 1] - sum[mid]) l = mid;
			else r = mid - 1;
		}
		ans = std::min (ans, std::min (sqr (sum[l] - sum[i - 1] - avg) + sqr (sum[n + i - 1] - sum[l] - avg), sqr (sum[l + 1] - sum[i - 1] - avg) + sqr (sum[n + i - 1] - sum[l + 1] - avg)));
	}
	std::cout << ans << "\n";
}
int main ()
{
//	freopen ("spaceship.in", "r", stdin);
//	freopen ("spaceship.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &a[i]), avg += a[i];
	if (n <= 1000) solve1 ();
	else 
	solve2 ();
}
