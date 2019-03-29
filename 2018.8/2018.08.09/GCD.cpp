#include<bits/stdc++.h>
#define N 50005
#define M 200005
#define ll long long

int n, Q, a[N], Case;
class BIT
{
	ll t[N];
	int lowbit (int x) { return x & -x; }
public:
	void add (int x, int y) { for (int i = x; i <= n; i += lowbit (i)) t[i] += y; }
	ll ask (int x) { ll res = 0; for (int i = x; i; i -= lowbit (i)) res += t[i]; return res; }
	void clear () { for (int i = 0; i <= n; i++) t[i] = 0; }
}T;

int vis[M], pri[N], mu[M], pcnt;
std::vector<int> s[M];
void init ()
{
	mu[1] = 1;
	for (int i = 2; i < M; i++)
	{
		if (!vis[i]) pri[++pcnt] = i, mu[i] = -1;
		for (int j = 1; j <= pcnt && i*pri[j] < M; j++)
		{
			vis[i*pri[j]] = 1;
			if (i%pri[j] == 0) { mu[i*pri[j]] = 0; break; }
			mu[i*pri[j]] = -mu[i];
		}
	}
	for(int i=1;i<M;i++) s[i].clear();
	for (int i = 1; i < M; i++)
		for (int j = i; j < M; j += i) s[j].push_back (i);
}
int main ()
{
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	init ();
	while (scanf ("%d%d", &n, &Q))
	{
		if (!n && !Q) break;
		printf ("Case #%d:\n", ++Case);
		while (Q--)
		{
			int opt, a, b, v;
			scanf ("%d", &opt);
			if (opt == 1)
			{
				scanf ("%d%d%d", &a, &b, &v);
				if (a%b) continue;
				for (auto p : s[a / b]) T.add (b * p, v * mu[p]);
			}
			else
			{
				scanf ("%d", &a);
				ll ans = 0;
				for (int i = 1, nxt; i <= a; i = nxt + 1)
				{
					nxt = a / (a / i);
					ans += (T.ask (nxt) - T.ask (i - 1))*(a / i);
				}
				printf ("%lld\n", ans);
			}
		}
		T.clear ();
	}
}
