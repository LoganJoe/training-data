#include<bits/stdc++.h>
#define DEBUG 0
#define $ if(DEBUG)
#define dbg1(x) $ std::cerr << #x << "=" << x << " "
#define dbg2(x) $ std::cerr << #x << "=" << x << "\n"
#define dbg3(x) $ for(auto v:x) std::cerr<<v<<" ";std::cerr<<"\n"
#define dbg4(x) $ std::cerr<<__FUNCTION__<<"() L"<<__LINE__<<":->: "#x"="<<(x)<<"\n"
#define N 1000005
#define mod 998244353
#define ll long long

ll n, m, ans, Max;
int pri[N], mu[N], vis[N], cnt;
int mul (int x) { return x >= mod ? x - mod : x; }
std::map<ll, int> D;
void init ()
{
	mu[1] = 1;
	for (int i = 2; i < N; i++)
	{
		if (!vis[i]) pri[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i*pri[j] < N; j++)
		{
			vis[i*pri[j]] = 1;
			if (i%pri[j] == 0) break;
			mu[i*pri[j]] = -mu[i];
		}
	}
}
int Sumd (ll x)
{
	if (D[x]) return D[x];
	ll res = 0;
	for (ll i = 1, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		res += (j - i + 1) * (x / i);
	}
	return D[x]=(res % mod);
}
int main ()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	init ();
	std::cin >> n; m = sqrt (n);
	for (int i = 1; i <= m; i++)
	{
		ans = mul (ans + mu[i] * Sumd (n / i / i));
		ans = mul (ans + mod);
	}
	std::cout << ans << "\n";
}
