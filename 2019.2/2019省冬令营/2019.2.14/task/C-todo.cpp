#include<bits/stdc++.h>
#define mod 1000000007
#define N 6005
int n, fac[N], inv[N], sum[N], tot[N], f[N / 3][N][2], ans;
char A[3][N];
void mul (int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
int P (int a, int b) { return 1ll * fac[a] * inv[a - b] % mod; }
int main ()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf ("%d", &n);
	scanf ("%s%s%s", A[0] + 1, A[1] + 1, A[2] + 1);
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i < N; i++) fac[i] = 1ll * fac[i - 1] * i%mod;
	for (int i = 2; i < N; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod%i] % mod;
	for (int i = 2; i < N; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	for (int i = 1;i <= n; i++)
		if(A[0][i] == 'x' && ())
	for (int i = 1; i <= n; i++)
		tot[i] = (A[0][i] == 'x') + (A[1][i] == 'x') + (A[2][i] == 'x'), sum[i] = sum[i - 1] + tot[i];
	ans = fac[sum[n]];
	for (int i = 1, nxt = 1; i <= n; i = nxt + 1)
	{
		if (A[1][i] == 'o') { nxt++; continue; }
		for (nxt = i; nxt < n && A[1][nxt + 1] == 'x'; nxt++);
		for (int j = 1; j <= tot[i]; j++) f[i][j][1] = 1ll * j * fac[tot[i] - 1] % mod;
		f[i][1][0] = fac[tot[i] - 1];
		for (int j = i + 1; j <= nxt; j++)
		{
			for (int k = 1; k <= sum[j - 1] - sum[i - 1]; k++)
			{
				mul (f[j][k + 1][1], 1ll * f[j - 1][k][1] * P (sum[j] - sum[i - 1] - k - 1, tot[j] - 1) % mod);
				mul (f[j][k + 1][0], 1ll * f[j - 1][k][1] * P (sum[j] - sum[i - 1] - k - 1, tot[j] - 1) % mod);
				mul (f[j][k][0], 1ll * f[j - 1][k][0] * P (sum[j] - sum[i - 1] - k, tot[j] - 1) % mod);
				if (tot[j] == 1)
					mul (f[j][k][1], f[j - 1][k][0]);
				if (tot[j] == 2)
					mul (f[j][k][1], 1ll * f[j - 1][k][0] * (sum[j] - sum[i - 1] - k) % mod),
					mul (f[j][k + 1][1], 1ll * f[j - 1][k][0] * k %mod);
				if (tot[j] == 3)
					mul (f[j][k][1], 1ll * f[j - 1][k][0] * P (sum[j] - sum[i - 1] - k, 2) % mod),
					mul (f[j][k + 1][1], 2ll * f[j - 1][k][0] * k % mod * (sum[j] - sum[i - 1] - k - 1) % mod),
					mul (f[j][k + 2][1], 1ll * f[j - 1][k][0] * P (k + 1, 2) % mod);
		//		std::cout << j << " " << k << " " << f[j][k][1] << " " << f[j][k + 1][1] << " " << f[j][k + 2][1] << "\n";
			}
			for (int k = 1; k <= sum[j] - sum[i - 1]; k++) mul (f[j][k][1], f[j][k - 1][1]);
			for (int k = sum[j] - sum[i - 1]; k >= 1; k--) mul (f[j][k][0], f[j][k + 1][0]);
		}
		//std::cout << nxt << " " << sum[nxt] - sum[i - 1] << " " << f[nxt][sum[nxt] - sum[i - 1]][1] << "\n";
		ans = 1ll * ans * inv[sum[nxt] - sum[i - 1]] % mod * f[nxt][sum[nxt] - sum[i - 1]][1] % mod;
	}
	std::cout << ans << "\n";
}
/*
3
ooo
xxo
ooo
*/
