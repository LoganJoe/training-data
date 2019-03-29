#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

const int N = 1 << 17;
const int Mod = 998244353, r = 3;

int Pow(int x, int e) {
	int ret = 1;
	while (e) {
		if (e & 1) ret = 1ll * ret * x % Mod;
		x = 1ll * x * x % Mod;
		e >>= 1;
	}
	return ret;
}

int k;

namespace FFT {

	int n, invn;
	int rev[N], w[N];

	void init() {
		n = 1;
		while (n < (k + 1) * 2) n <<= 1;
		For(i, 0, n - 1) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
		invn = Pow(n, Mod - 2);
	}

	void DFT(int *A, int wn) {
		For(i, 0, n - 1) if (i < rev[i]) swap(A[i], A[rev[i]]);
		for (int i = 1; i < n; i <<= 1) {
			w[0] = 1, w[1] = Pow(r, (Mod - 1) / (i << 1));
			if (wn == -1) w[1] = Pow(w[1], Mod - 2);
			For(j, 2, i - 1) w[j] = 1ll * w[j - 1] * w[1] % Mod;
			for (int j = 0; j < n; j += i << 1)
				for (int k = 0; k < i; ++k) {
					int x = A[j + k], y = 1ll * w[k] * A[i + j + k] % Mod;
					A[j + k] = (x + y) % Mod, A[i + j + k] = (x - y + Mod) % Mod;
				}
		}
	}

	void mult(int *A, int *B) {
		DFT(A, 1), DFT(B, 1);
		For(i, 0, n - 1) A[i] = 1ll * A[i] * B[i] % Mod;
		DFT(A, -1);
		For(i, 0, n - 1) B[i] = 0, A[i] = i <= k ? 1ll * A[i] * invn % Mod : 0;
	}

};

int fac[N], rfac[N];
int ans[N], P[N];

void mul(int *A, int x) {
	int coe = 1;
	For(i, 0, k) A[i] = 1ll * A[i] * coe % Mod, coe = 1ll * coe * x % Mod;
}

void calc(int e) {
	if (!e) {
		ans[0] = 1;
	} else if (e & 1) {
		calc(e - 1);
		P[0] = 0;
		For(i, 1, k) P[i] = rfac[i];
		mul(P, Pow(2, e - 1));
		FFT::mult(ans, P);
	} else {
		calc(e >> 1);
		For(i, 0, k) P[i] = ans[i];
		mul(P, Pow(2, e / 2));
		FFT::mult(ans, P);
	}
}

int main() {

	freopen("or.in", "r", stdin);
	freopen("or.out", "w", stdout);

	int n;
	scanf("%d%d", &n, &k);

	fac[0] = 1;
	For(i, 1, k) fac[i] = 1ll * fac[i - 1] * i % Mod;
	rfac[k] = Pow(fac[k], Mod - 2);
	Forr(i, k, 1) rfac[i - 1] = 1ll * rfac[i] * i % Mod;

	FFT::init();
	calc(n);

	int res = 0;
	For(i, n, k) res = (res + 1ll * ans[i] * fac[k] % Mod * rfac[k - i]) % Mod;
	printf("%d\n", res);

	return 0;
}
