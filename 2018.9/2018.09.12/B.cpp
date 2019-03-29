#include<bits/stdc++.h>
#define N 2005
#define mod 998244353
int n, A[N][3];
char ch[10];
int mul (int x) { return x >= mod ? x - mod : x; }
namespace solve1
{
	int s[N], ans[N];
	void check ()
	{
		int res = 0, cnt = 0;
		for (int i = 1, p = 0; i <= n; i++) if (s[i] == p) cnt++, p = (p + 1) % 3;
		res = std::max (res, cnt), cnt = 0;
		for (int i = 1, p = 1; i <= n; i++) if (s[i] == p) cnt++, p = (p + 1) % 3;
		res = std::max (res, cnt), cnt = 0;
		for (int i = 1, p = 2; i <= n; i++) if (s[i] == p) cnt++, p = (p + 1) % 3;
		res = std::max (res, cnt), cnt = 0;
		ans[res]++;
	}
	void dfs (int x)
	{
		if (x > n) return check ();
		for (int i = 0; i < 3; i++) if (A[x][i]) s[x] = i, dfs (x + 1);
	}
	void Main ()
	{
		dfs (1);for (int i = 1; i <= n; i++) printf ("%d ", ans[i]);
	}
}
namespace solve2
{
	int f[N][N][27], ans[N];
	int stau (int a, int b, int c) { return a + 3 * b + 9 * c; }
	#define M stau (staf[0], staf[1],staf[2])
	void Main ()
	{	
		for (int i = 0; i < 3; i++) 
			if (A[1][i]) f[1][1][stau (1 + (i == 0), 1 + (i == 1), 1 + (i == 2))] = 1;
		for (int i = 1; i < n; i++)
			for (int j = 1; j <= i; j++)
				for (int k = 0; k < 27; k++)
					for (int s = 0; s < 3; s++)
					{
						int mark = 0, staf[3];
						for (int s = 0, x = k; s < 3; s++) staf[s] = x % 3, x /= 3;
						staf[s] = staf[(s - 1 + 3) % 3] + 1;
						if (staf[s] == 3) mark = 1, staf[0]--, staf[1]--, staf[2]--;
						if (!A[i + 1][s]) continue;
						if(M >= 0) f[i + 1][j + mark][M] = (f[i + 1][j + mark][M] + f[i][j][k])%mod;
						//printf ("To:%d %d %d %d\n", i + 1, j + mark, M, f[i + 1][j + mark][M]);
					}
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 27; j++) ans[i] = (ans[i] + f[n][i][j])%mod;
		for (int i = 1; i <= n; i++) printf ("%d ", ans[i]);			
	}
}
int main ()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%s", ch); int k = strlen (ch);
		for (int j = 0; j < k; j++) A[i][ch[j] - '0'] = 1;
	}
	if (n < 20) return solve1::Main (), 0;
	else return solve2::Main (), 0;

}
