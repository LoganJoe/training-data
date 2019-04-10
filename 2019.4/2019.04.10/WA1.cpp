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
namespace solve2
{
	struct node//my_permutation_vector
	{
		int A[N], n;
		int size() { return n; }
		int unique ()
		{
			static int b[N], tot;
			for (int i = 1; i <= n; i++) b[i] = A[i];
			std::sort (b + 1, b + 1 + n);
			tot = std::unique (b + 1, b + 1 + n) - b - 1;
			for (int i = 1; i <= n; i++) 
			A[i] = std::lower_bound (b + 1, b + 1 + tot, A[i]) - b;
			return tot;
		}
		ull getha ()
		{
			ull ha = 0;
			for (int i = 1; i <= n; i++) ha = ha * P + A[i];
			return ha;
		}
		bool check()
		{
			static int Min[N], Max[N];
			Max[1] = A[1], Min[n] = A[n];
			for (int i = 2; i <= n; i++) Max[i] = std::max (Max[i - 1], A[i]);
			for (int i = n - 1; i; i--) Min[i] = std::min (Min[i + 1], A[i]);
			for (int i = 1; i <= n; i++) 
				if(Max[i] <= A[i] && A[i] <= Min[i]) return 1;
			return 0;
		}
	};
	std::unordered_map<ull, int> f;
	int solve (node &p)
	{
		if(!p.n) return 0;
		p.unique ();
		ull ha = p.getha (); 
		if(f.find(ha) != f.end()) return f[ha];
		if (p.check()) return f[ha] = 1;
		int res = 0;
		node v = p;
		for (int i = 1;i <= n; i++)
			for(int j = i + 1; j <= n; j++)
				if(v.A[i] > v.A[j]) std::swap(v.A[i], v.A[j]), res=(res + solve(v)) % mod, std::swap(v.A[i], v.A[j]);
		return f[ha] = res;
	}
	void Main()
	{
		node p;
		for (int i = 1; i <= n; i++) p.A[i] = A[i];
		p.n = n;
		std::cout << solve(p) << "\n";
	}
}
int main()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
//	if(n <= 8) return solve1::Main(), 0;
//	else 
	return solve2::Main(), 0;
}
/*
15
12 2 9 4 1 11 8 14 6 3 15 10 7 5 13
*/
