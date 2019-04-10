#include<bits/stdc++.h>
#include<unordered_map>
#define N 22
#define ull unsigned long long
#define P 19260817
#define mod 1000000007
int n, A[N];
namespace solve1
{
	std::unordered_map<ull, int> mp;
	int ans;
	void dfs ()
	{
		ull ha = 0;
		for (int i = 1; i <= n; i++) ha = ha * P + A[i];
		if(mp.find(ha) != mp.end()) return ;
		mp[ha] = 1, ans ++;
		for (int i = 1;i <= n; i++)
			for(int j = i + 1; j <= n; j++)
				if (A[i] > A[j]) std::swap(A[i], A[j]), dfs(), std::swap(A[i], A[j]);
	}
	void Main()
	{
		dfs ();
		std::cout << ans << "\n";
	}
}
int main()
{
	freopen ("perm.in", "r", stdin);
	freopen ("perm.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	return solve1::Main(), 0;
//	if(n <= 10) return solve1::Main(), 0;
//	else return solve2::Main(), 0;
}
/*
11
2 9 4 1 8 6 11 3 10 7 5 
*/
