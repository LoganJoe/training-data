#include<bits/stdc++.h>
#define DEBUG 0
#define $ if(DEBUG)
#define dbg1(x) $ std::cerr << #x << "=" << x << " ";
#define dbg2(x) $ std::cerr << #x << "=" << x << "\n";
#define dbg3(x) $ for(auto v:x) std::cerr<<v<<" ";std::cerr<<"\n"
#define dbg4(x) $ std::cerr<<__FUNCTION__<<"() L"<<__LINE__<<":->: "#x"="<<(x)<<"\n"
#define N 2000
#define mod 998244353
int n, a[N], b[N], mark1[N], mark2[N], pos[N], nxt[N], mark[N], cnt[N];
void calc ()
{
	int tot = 0;
	for (int i = 1; i <= n; i++) pos[b[i]] = i, mark[i] = 0;
	for (int i = 1; i <= n; i++) nxt[i] = pos[a[i]];
	for (int i = 1; i <= n; i++)
		if (!mark[i])
		{
			for (int j = nxt[i]; j != i; j = nxt[j]) mark[j] = 1, tot++;
			mark[i] = 1;
		}
	cnt[tot]++;
}
void dfs2 (int x)
{
	if (x > n) return calc ();
	if (b[x]) return dfs2 (x + 1);
	for (int i = 1; i <= n; i++) if (!mark2[i]) mark2[i] = 1, b[x] = i, dfs2 (x + 1), mark2[i] = b[x] = 0;
}
void dfs1 (int x)
{
	if (x > n) return dfs2 (1);
	if (a[x]) return dfs1 (x + 1);
	for (int i = 1; i <= n; i++) if (!mark1[i]) mark1[i] = 1, a[x] = i, dfs1 (x + 1), mark1[i] = a[x] = 0;
}
void solve1 ()
{
	for (int i = 1; i <= n; i++) mark1[a[i]] = mark2[b[i]] = 1;
	dfs1 (1);
	for (int i = 0; i < n; i++) printf ("%d ", cnt[i]);
	puts ("");
}
int s[N][N];
void solve3 ()
{
	s[0][0] = 1;
	int fac = 1; for (int i = 1; i <= n; i++) fac = 1ll * fac * i % mod;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++) s[i][j] = (1ll * s[i][j - 1] + 1ll * s[i - 1][j] * (i - 1)) % mod;
	for (int i = 1; i <= n; i++) printf ("%d ", s[n][n - i + 1] * fac);
}
void solve2 ()
{
	int sum = 0; for (int i = 1; i <= n; i++) sum += a[i] + b[i];
	if (sum == 0) return solve3 ();
	calc ();
	for (int i = 0; i < n; i++) printf ("%d ", cnt[i]);
	puts ("");
}
int main ()
{
	freopen("play.in","r",stdin);
	freopen("play.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf ("%d", &b[i]);
	if (n <= 8) solve1 ();
	else solve2 ();
}
