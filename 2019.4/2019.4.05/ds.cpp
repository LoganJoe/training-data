#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, Q;
ll A[N], B[N];
namespace solve1
{
	void Main ()
	{
		while (Q--)
		{
			int op, l, r, res = 0; ll v;;
			scanf ("%d%d%d%lld", &op, &l, &r, &v);
			if (op == 1)
				for (int i = l; i <= r; i++) A[i] += v;
			else
				for (int i = l; i <= r; i++) if (A[i] <= v) res++;
			if (op == 2) printf ("%d\n", res);
		}
	}
}
namespace solve2
{
	int blo, bel[N]; ll tag[N];
	void build (int id)
	{
		int l = (id - 1) * blo + 1, r = std::min (id * blo, n);
		for (int i = l; i <= r; i++) B[i] += tag[id], A[i] = B[i];
		tag[id] = 0;
		std::sort (A + l, A + 1 + r);
	}
	void change (int l, int r, ll v)
	{
		if (bel[l] == bel[r])
		{
			for (int i = l; i <= r; i++) B[i] += v;
			build (bel[l]); return;
		}
		for (int i = l; i <= std::min (n, bel[l] * blo); i++) B[i] += v;
		build (bel[l]);
		for (int i = (bel[r] - 1) * blo + 1; i <= r; i++) B[i] += v;
		build (bel[r]);
		for (int i = bel[l] + 1; i < bel[r]; i++) tag[i] += v;
	}
	int query (int l, int r, ll v)
	{
		int res = 0;
		if (bel[l] == bel[r])
		{
			for (int i = l; i <= r; i++)
				if (B[i] + tag[bel[l]] <= v) res++;
			return res;
		}
		for (int i = l; i <= std::min (n, bel[l] * blo); i++)
			if (B[i] + tag[bel[l]] <= v) res++;
		for (int i = (bel[r] - 1) * blo + 1; i <= r; i++)
			if (B[i] + tag[bel[r]] <= v) res++;
		for (int i = bel[l] + 1; i < bel[r]; i++)
		{
			int L = (i - 1) * blo + 1, R = i * blo;
			if (A[L] + tag[i] > v) continue;
			for (int mid; L < R; mid = L + R + 1 >> 1, A[mid] + tag[i] <= v ? L = mid : R = mid - 1);
			res += L - (i - 1) * blo;
		}
		return res;
	}
	void Main ()
	{
		blo = sqrt (n);
		for (int i = 1; i <= n; i++) bel[i] = (i - 1) / blo + 1, B[i] = A[i];
		for (int i = 1; i <= bel[n]; i++) build (i);
		while (Q--)
		{
			int op, l, r, res = 0; ll v;
			scanf ("%d%d%d%lld", &op, &l, &r, &v);
			if (op == 1) change (l, r, v);
			else printf ("%d\n", query (l, r, v));
		}
	}
}
int main ()
{
	freopen ("ds.in", "r", stdin);
	freopen ("ds.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%lld", &A[i]);
	scanf ("%d", &Q);
	if (n <= 1000 && Q <= 1000) return solve1::Main (), 0;
	else return solve2::Main (), 0;
}
/*
5
2 2 4 1 2
3
2 1 5 3
1 3 4 1
2 1 5 3
*/