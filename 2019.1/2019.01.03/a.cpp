#include<bits/stdc++.h>
#define N 505
#define mod 1000000007
int n, f[N][N << 1][2][2][3];
char s[N];
int mul (int x) { return x >= mod ? x - mod : x; }
//  solve (now_pos, switch_time, last_reach_to_limit, last_same_to_not_g, period)
int solve (int x, int val, int s1, int s2, int p)
{
	if (x > n) return p & 1 ? 0 : val;
	if (f[x][val][s1][s2][p]) return f[x][val][s1][s2][p];
	int L = s1 ? s[x] - '0' : 1, res = 0;
	for (int i = 0; i <= L; i++)
		for (int j = 0; j <= 1; j++)
		{
			if (i < j && (s2 || !p) || i > j && p == 1) continue;
			int t = val + (p ? ((i == 1) + (j == 0)) : (i > j));
			if (i > j && p == 0) res = mul (res + solve (x + 1, t, s1&(i == L), s2&(i == j), 1));
			if (i < j && p == 1) res = mul (res + solve (x + 1, t, s1&(i == L), s2&(i == j), 2));
			else res = mul (res + solve (x + 1, t, s1&(i == L), s2&(i == j), p));
		}
	return f[x][val][s1][s2][p] = res;
}
int main ()
{
	freopen ("a.in", "r", stdin);
	freopen ("a.out", "w", stdout);
	scanf ("%s", s + 1); n = strlen (s + 1);
	std::cout << solve (1, 0, 1, 1, 0) << "\n";
}
