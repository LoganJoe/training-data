#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, A[N], b[N], tot, f[N][2], g[N][2], totl, totr; ll ans;
class BIT
{
	int t[N];
public:
	void add (int x, int v) { for (; x <= tot; x += x & -x) t[x] += v; }
	int ask (int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }
	void clear () { for (int i = 1; i <= tot; i++) t[i] = 0; }
}T, S[2];
int main ()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), b[i] = A[i];
	std::sort (b + 1, b + 1 + n);
	tot = std::unique (b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; i++) 
		A[i] = std::lower_bound (b + 1, b + 1 + tot, A[i]) - b;
	for (int i = 1; i <= n; i++) f[i][0] = T.ask (A[i] - 1), T.add (A[i], 1);
	T.clear ();
	for (int i = n; i >= 1; i--) f[i][1] = T.ask (A[i] - 1), T.add (A[i], 1);
	T.clear ();
	for (int i = 1; i <= n; i++) g[i][0] = T.ask (tot - A[i]), T.add (tot - A[i] + 1, 1);
	T.clear ();
	for (int i = n; i >= 1; i--) g[i][1] = T.ask (tot - A[i]), T.add (tot - A[i] + 1, 1);
	for (int i = 1; i <= n; i++) totl += f[i][0], totr += g[i][0];
	ans = 1ll * totl * totr;
	for (int i = 1; i <= n; i++) 
		ans -= 1ll * f[i][0] * f[i][1] + 1ll * g[i][0] * g[i][1] + 1ll * f[i][0] * g[i][0] + 1ll * f[i][1] * g[i][1];
	std::cout << ans << "\n";
}
