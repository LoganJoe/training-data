#include<bits/stdc++.h>
#define ll long long
ll L, R, ans;
int cnt[10];
void slove1 ()
{
	std::map<ll, int> mp;
	for (int i = L; i <= R; i++)
	{
		for (int x = i; x; x /= 10) cnt[x % 10]++;
		ll ha = 0;
		for (int j = 1; j < 10; j++) while (cnt[j]) ha = ha * 10 + j, cnt[j]--;
		if (!mp[ha]) mp[ha] = ++ans;
	}
	std::cout << ans << "\n";
}

int main ()
{
	freopen("litchi.in","r",stdin);
	freopen("litchi.out","w",stdout);
	std::cin >> L >> R;
	if (R <= 1e6 || R-L<=1e6) return slove1 (), 0;

}
