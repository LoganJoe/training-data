#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
ll n, tn, p[10], cnt[10], tot, totS, size[100], ans, mark[100];
void add(ll x)
{
	int S = 0;
	for (int i = 1; i <= tot; i++)
		if (x % p[i] == 0)
			S |= 1 << i - 1;
	size[S]++;
}
std::vector<int> S;
void solve(int x, int val, std::vector<int> S)
{
	if (x > 1)
		ans = (ans + val) % mod;
	if (S.size() == 0)
		return;
	std::vector<int> T;
	for (int sub : S)
	{
		for (int j = totS ^ sub; j; j = (j - 1) & (totS ^ sub))
			mark[j]++;
		T.clear();
		for (int j : S)
			if (x - mark[j] < 2)
				T.push_back(j);
		solve(x + 1, 1ll * val * size[sub] % mod, T);
		for (int j = totS ^ sub; j; j = (j - 1) & (totS ^ sub))
			mark[j]--;
	}
}
int main()
{
	freopen("six.in", "r", stdin);
	freopen("six.out", "w", stdout);
	std::cin >> n;
	tn = n;
	for (ll i = 2; i * i <= tn; i++)
		if (tn % i == 0)
			for (p[++tot] = i; tn % i == 0; tn /= i, cnt[tot]++)
				;
	if (tn > 1)
		p[++tot] = tn, cnt[tot] = 1;
	totS = (1 << tot) - 1;
	for (ll i = 1; i * i <= n; i++)
		if (n % i == 0)
		{
			add(i);
			if (i * i < n)
				add(n / i);
		}
	for (int i = 1; i <= totS; i++)
		S.push_back(i);
	solve(1, 1, S);
	std::cout << ans << "\n";
}