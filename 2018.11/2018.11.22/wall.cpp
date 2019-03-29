#include<bits/stdc++.h>
#define ll long long
ll n, k, ans;
int main ()
{
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
	std::cin >> n;
	for (ll l = 0, r = n, mid; l <= r;)
		mid = (l + r) >> 1, (3ll * mid*(mid + 1) + 1 >= n) ? (r = mid - 1, k = mid) : l = mid + 1;
	ans = 3ll * (k + 1)*(k + 2) - 3ll * k*(k + 1);
	n = 3ll * k*(k + 1) + 1 - n;
	if (n >= k + 1)
	{
		ans--, n -= k + 1;
		while (n >= k) ans--, n -= k;
	}
	std::cout << ans << "\n";
}
