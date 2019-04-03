#include<bits/stdc++.h>
#define ll long long
#define N 1050005
#define inf 1e18
int n, tot; ll K, Min = 1e18, p[N], L = -1, mark[N], ans;
struct node
{
	ll l, r;int id;
}A[N], B[N];
bool cmpl (node t1, node t2) { return t1.l < t2.l; }
bool cmpr (node t1, node t2) { return t1.r < t2.r; }

void dfs (int x, ll num)
{
	if (num > 1e18) return;
	if (x > 1) p[++tot] = num;
	dfs (x + 1, num * 10 + 4), dfs (x + 1, num * 10 + 7);
}
ll add (ll x, ll y)
{
	if (x == -1 || y == -1) return -1;
	else return x + y > inf ? -1 : x + y;
}
ll mul (ll x, ll y)
{
	if (x == -1 || y == -1) return -1;
	else return 1.*x*y > inf ? -1 : x * y;

}
int main ()
{
	freopen ("number.in", "r", stdin);
	freopen ("number.out", "w", stdout);
	scanf ("%d%lld", &n, &K);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%lld%lld", &A[i].l, &A[i].r), A[i].id = i;
		B[i] = A[i], Min = std::min (Min, A[i].r - A[i].l);
	}
	std::sort (A + 1, A + 1 + n, cmpl);
	std::sort (B + 1, B + 1 + n, cmpr);
	dfs (1, 0);
	std::sort (p + 1, p + 1 + tot);
	int l = 1, r = 0, cnt = 0, j = 0;
	ll tA = 0;
	for (int i = 1; i <= tot; i++)
	{
		if (tA == -1) break;
		for (; l <= r && A[l].l <= p[i]; tA -= std::max (0ll, A[l].l - p[i - 1]), l++);
		tA -= 1ll * (r - l + 1) * (p[i] - p[i - 1]);
		tA = add (tA, mul (j , p[i] - p[i - 1]));
		for (; j < n && B[j + 1].r <= p[i]; tA = add (tA, p[i] - B[j + 1].r), j++);
		for (ll t; r < n && (t = add (tA, std::max (0ll, A[r + 1].l - p[i]))) != -1; r++, tA = t);
		if (r == n && tA != -1 && tA <= K)
		{
			L = i; break;
		}
	}
	if (L == -1) return puts ("0"), 0;
	int tB = j;
	for (int i = L, j = L; i <= tot; i++)
	{
		for (; j < tot && p[j + 1] - p[i] <= Min;)
		{
			int tp = tB; j++;
			if (mark[j] > 0)
			{
				if (add (tA, mark[j]) == -1) break;
				tA = add (tA, mark[j]);
				for (; tB < n && B[tB + 1].r <= p[j]; tB++);
			}
			else
			{
				mark[j] = mul (p[j] - p[j - 1], tB);
				for (; tB < n && B[tB + 1].r < p[j] && mark[j] != -1 && mark[j] <= K; 
					tB++, mark[j] = add (mark[j], p[j] - B[tB].r));
				if (add (tA, mark[j]) == -1 || add (tA, mark[j]) > K)
				{
					j--, tB = tp; break;
				}
				else tA = add (tA, mark[j]);
			}
		}
		if (tA <= K) ans = std::max (ans, j - i + 1ll);
		if (i ^ tot)
		{
			for (; l <= n && A[l].l <= p[i + 1]; tA -= std::max (0ll, A[l].l - p[i]), l++);
			tA -= 1ll * (n - l + 1) * (p[i + 1] - p[i]);
		}
	}
	std::cout << ans << "\n";
}
/*

*/
