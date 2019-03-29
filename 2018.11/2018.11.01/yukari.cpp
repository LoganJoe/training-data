#include<bits/stdc++.h>
const int N = 200005, M = 450, mod = 1000000007;
int n, m, A[N], block[N], kuai, MaxB;
int mul (int x) { return x >= mod ? x - mod : x; }
int calm (int x) { return x >= m ? x - m : x; }
struct node
{
	int s[22];
	friend node operator *(node a, node b)
	{
		node c;
		for (int i = 0; i < m; i++)
		{
			unsigned long long res = 0;
			for (int j = 0; j < m; j++)
			{
				res += 1ll * a.s[j] * b.s[calm (i - j + m)];
				if (res >= 1e19) res %= mod;
			}
			c.s[i] = res % mod;
		}
		/*
		for (int i = 0; i < m; i++) c.s[i] = 0;
		for (int i = 0; i < m; i++) if(a.s[i])
			for (int j = 0; j < m; j++) if(b.s[j])
				c.s[calm (i + j)] = mul (c.s[calm (i + j)] + 1ll * a.s[i] * b.s[j] % mod);
		*/
		return c;
	}
}f[M][M], g[M][M], t[M][M];
int main ()
{
	freopen ("yukari.in", "r", stdin);
	freopen ("yukari.out", "w", stdout);
	std::cout<<"***"<<"\n";
	scanf ("%d%d", &n, &m); kuai = sqrt (n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), A[i] %= m;
	for (int i = 1; i <= n; i++) block[i] = (i - 1) / kuai + 1;
	MaxB = (n - kuai * (block[n] - 1));
	for (int i = 1; i <= block[n]; i++)  f[i][0].s[0] = 1;
	for (int i = 1; i <= block[n]; i++) g[i][i < n ? (kuai + 1) : (MaxB + 1)].s[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		int bel = block[i], p = i - kuai * (block[i] - 1);
		for (int j = 0; j < m; j++)
			f[bel][p].s[j] = mul (f[bel][p - 1].s[j] + f[bel][p - 1].s[calm (j - A[i] + m)]);
		//f[bel][p].s[A[i]]++;
	}
	for (int i = n; i >= 1; i--)
	{
		int bel = block[i], p = i - kuai * (block[i] - 1);
		for (int j = 0; j < m; j++)
			g[bel][p].s[j] = mul (g[bel][p + 1].s[j] + g[bel][p + 1].s[calm (j - A[i] + m)]);
		//g[bel][p].s[A[i]]++;
		//for (int j = 0; j < m; j++) printf ("%d ", g[bel][p].s[j]); puts ("");
	}

	for (int i = 1; i <= block[n]; i++)
		for (int j = 0, p = (i < block[n]) ? kuai : MaxB; j < m; j++) t[i][i].s[j] = f[i][p].s[j];
	for (int i = 1; i <= block[n]; i++)
		for (int j = i + 1; j <= block[n]; j++) t[i][j] = t[i][j - 1] * t[j][j];
	int Q; scanf ("%d", &Q);
	while (Q--)
	{
		int l, r;
		scanf ("%d%d", &l, &r);
		if (block[l] == block[r])
		{

			node tp[2]; for (int i = 0; i < m; i++) tp[0].s[i] = tp[1].s[i] = 0;
			tp[0].s[0] = 1;
			for (int i = l, k = 1; i <= r; i++, k ^= 1)
			{
				for (int j = 0; j < m; j++)
					tp[k].s[j] = mul (tp[k ^ 1].s[j] + tp[k ^ 1].s[calm (j - A[i] + m)]);
				//tp[k].s[A[i]]++;
			}
			printf ("%d\n", tp[(r - l + 1) & 1].s[0]);
		}
		else
		{
			node tp = g[block[l]][l - kuai * (block[l] - 1)];
			tp = tp * f[block[r]][r - kuai * (block[r] - 1)];
			if (block[l] + 1 <= block[r] - 1) tp = tp * t[block[l] + 1][block[r] - 1];
			printf ("%d\n", tp.s[0]);
		}
	}
}
/*
4 3
5 1 3 2
2
1 2
1 3
*/
