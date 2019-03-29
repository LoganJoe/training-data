#include<bits/stdc++.h>
#define ll long long
#define N 200005
ll n, Min, cnt; int m;
std::vector<std::pair<std::string, int> > A;
int main ()
{
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		std::string S; ll k;
		std::cin >> S >> k;
		A.push_back ({ S,k });
	}
	for (int i = m - 1; ~i; i--)
	{
		std::string &S = A[i].first; ll k = A[i].second;
		ll tot = 0, low = 0;
		for (int j = S.size () - 1; ~j; j--)
			tot += S[j] == 'F' ? 1 : -1, low = std::min (low, tot);
		Min = std::min (Min, cnt + std::min (low, (k - 1)*tot + low));
		cnt += k * tot;
	}
	if (cnt < 0) return puts ("-1"), 0;
	else std::cout << std::max (0ll, -Min - 1) << "\n";
}
