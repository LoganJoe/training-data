#include<bits/stdc++.h>
#define N 10000007
int T, n;
int pri[N], vis[N], pcnt;
void init ()
{
	for (int i = 2; i < N; i++)
	{
		if (!vis[i]) pri[++pcnt] = i;
		for (int j = 1; j <= pcnt && i*pri[j] < N; i++)
		{
			vis[i*pri[j]] = 1;
			if (i%pri[j] == 0) break;
		}
	}
}
int main ()
{
	//freopen("number.in","r",stdin);
	//freopen("number.out","w",stdout);
	init ();
	for (scanf ("%d", &T); T--;)
	{
		scanf ("%d", &n);
		int ans = 1e9;
		for (int i = 1; i <= pcnt && pri[i] <= n; i++) if (n%pri[i] == 0)
		{
			int c = 0;
			for (; n%pri[i] == 0; c++, n /= pri[i]);
			ans = std::min (ans, c);
		}
		printf ("%d\n", ans);
	}
}
