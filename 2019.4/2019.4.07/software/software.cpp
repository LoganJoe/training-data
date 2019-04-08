#include<bits/stdc++.h>
#define ll long long
#define I128 __int128
std::string type;
namespace solve1
{
	const int mod = 998244353, base = 19;
	char s[100];
	ll Pow (ll x, ll k)
	{
		ll t = 1;
		for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x % mod;
		return t;
	}
	void Main ()
	{
		int n;
		for (scanf ("%d", &n); n--;)
		{
			scanf ("%s", s); int x = 0, len = strlen (s);
			for (int i = 0; i < len; i++) x = (10ll * x + s[i] - 48) % (mod - 1);
			printf ("%d\n", Pow (base, x));
		}
	}
}
namespace solve2
{
	const int mod = 1145141, base = 19;
	char s[100];
	ll Pow (ll x, ll k)
	{
		ll t = 1;
		for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x % mod;
		return t;
	}
	void Main ()
	{
		int n;
		for (scanf ("%d", &n); n--;)
		{
			scanf ("%s", s); int x = 0, len = strlen (s);
			for (int i = 0; i < len; i++) x = (10ll * x + s[i] - 48) % (mod - 1);
			printf ("%d\n", Pow (base, x));
		}
	}
}
namespace solve4
{
	const int mod = 998244353, base = 19;
	char s[100];
	int po[200000];
	int Pow (int x, int k)
	{
		if(k <= 100000) return po[k];
		int t = 1;
		for (; k; k >>= 1, x = x * x % mod) if (k & 1) t = t * x % mod;
		return t;
	}
	void Main ()
	{
		po[0] = 1;
		for (int i = 1;i <= 100000; i++) po[i] = (int)((unsigned)po[i - 1] * (unsigned)base) % mod; 
		int n;
		for (scanf ("%d", &n); n--;)
		{
			scanf ("%s", s); int x = 0, len = strlen (s);
			for (int i = 0; i < len; i++) x = (10ll * x + s[i] - 48) % (mod - 1);
			int ans = (int) Pow (base, x);
			printf ("%d\n", (int)ans);
		}
	}
}
int main (int argc, char* argv[])
{
	freopen ("software.in", "r", stdin);
	freopen ("software.out", "w", stdout);
	std::cin >> type;
	if (type == "1_998244353") solve1::Main ();
	if (type == "1?") solve2::Main ();
	if (type == "1wa_998244353") solve4::Main ();

}
