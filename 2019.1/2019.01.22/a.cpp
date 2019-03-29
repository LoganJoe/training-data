#include<bits/stdc++.h>
#define N 1000005
#define mod 1000109107
int T, n, m, K, fac[N], inv[N], ine[N], ans;
int C (int a, int b) { return 1ll * fac[a] * inv[b] % mod*inv[a - b] % mod; }
int main ()
{
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i < N; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 2; i < N; i++) ine[i] = inv[i] = 1ll * (mod - mod / i)*inv[mod%i] % mod;
	for (int i = 2; i < N; i++) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
	for (scanf ("%d", &T); T--;)
	{
		scanf ("%d%d%d", &n, &m, &K); int t = n + 1 >> 1;
		if (K > 3) { puts ("0"); continue; }
		if (K == 3) ans = m > 3 ? 0 : t * (t - 1) / 2;
		//if(K == 2)
		printf ("%d\n", 1ll * ans * n * ine[m] % mod);
	}
}
