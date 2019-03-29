#include<bits/stdc++.h>
#define mod 1000000007
#define N 205
int n, R, G, B;
//     0  1  2 
int f[2][N][N][3][3], ans;
int mul (int x) { return x >= mod ? x - mod : x; }
int main ()
{
	freopen ("dec.in", "r", stdin);
	freopen ("dec.out" , "w", stdout);
	scanf ("%d%d%d%d", &n, &R, &G, &B);
	if (R > n || G > n || B > n) return puts ("0");
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) 
			if (i ^ j) f[1][(i == 0) + (j == 0)][(i == 1) + (j == 1)][i][j] = 1;
	for (int i = 1, k = 1; i < n; i++, k ^= 1)
		for (int s0 = 0; s0 <= std::min (R, i); s0++)
			for (int s1 = 0; s1 <= std::min (G, i); s1++)
			{
				if ((i << 1) - s0 - s1 > B) continue;
				for (int t0 = 0; t0 < 3; t0++)
					for (int t1 = 0; t1 < 3; t1++) if ((t0^t1) && f[k][s0][s1][t0][t1])
						for (int f0 = 0; f0 < 3; f0++) if (f0 ^ t0)
							for (int f1 = 0; f1 < 3; f1++) if ((f0 ^ f1) && (f1 ^ t1))
							{
								if (((1 << t0) | (1 << t1) | (1 << f0) | (1 << f1)) != 7) continue;
								f[k ^ 1][s0 + (f0 == 0) + (f1 == 0)][s1 + (f0 == 1) + (f1 == 1)][f0][f1]
									= mul (f[k ^ 1][s0 + (f0 == 0) + (f1 == 0)][s1 + (f0 == 1) + (f1 == 1)][f0][f1]
										+ f[k][s0][s1][t0][t1]);
							}
			}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) if (i^j) ans = mul (ans + f[n & 1][R][G][i][j]);
	std::cout << ans << "\n";
}
