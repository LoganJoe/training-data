#include<bits/stdc++.h>
#define N 100005
int n, m, f[N], g[N], mark[N];
char A[N], B[N];
class BIT
{
	int t[N];
	int lowbit (int x) { return x & -x; }
public:
	void add (int x, int v) { for (;x && x <= n; x += lowbit (x)) t[x] = std::max (t[x], v); }
	int ask (int x) { int res = 0; for (; x > 0; x -= lowbit (x)) res = std::max (res, t[x]); return res; }
}T;
int main ()
{
	freopen("june.in","r",stdin);
	freopen("june.out","w",stdout);
	scanf ("%s%s", A + 1, B + 1);
	n = strlen (A + 1), m= strlen (B + 1);
	g[m + 1] = n + 1;
	for (int i = 1; i <= m; i++)
		for (f[i] = std::min (f[i - 1], n) + 1; f[i] <= n && A[f[i]] != B[i]; f[i]++);
	for (int i = m; i >= 1; i--)
		for (g[i] = std::max (g[i + 1], 1) - 1; g[i] >= 1 && A[g[i]] != B[i]; g[i]--);
	int ansl = 0, ansr = m + 1;
	for (int i = 0; i <= m + 1; i++)
	{
		if(!g[i]) {T.add(f[i], i); continue;}
		int p = T.ask (g[i] - 1); T.add (f[i], i);
		if (i - p - 1 < ansr - ansl - 1) ansl = p, ansr = i;
	}
	if (ansl<1 && ansr>m) return puts ("-");
	for (int i = 1; i <= ansl; i++) printf ("%c", B[i]);
	for (int i = ansr; i <= m; i++) printf ("%c", B[i]);
	puts ("");
	return 0;
}
/*
abca
accepted
*/



