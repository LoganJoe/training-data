#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

const int N = 1030;

int Mod;

int Pow(int x, int e) {
	int ret = 1;
	while (e) {
		if (e & 1) ret = ret * x % Mod;
		x = x * x % Mod;
		e >>= 1;
	}
	return ret;
}

void add(int &x, int y) {
	x += y;
	x = x >= Mod ? x - Mod : x;
}

int n;
int dp[N][N], f[N][N], g[N][N];
bool vis[N];
int inv[N], cnt[N], odd[N], pos[N];

int main() {

//	freopen("seat.in", "r", stdin);
//	freopen("seat.out", "w", stdout);

	scanf("%d%d", &n, &Mod);
	For(i, 1, n) inv[i] = Pow(i, Mod - 2);

	vis[0] = vis[n + 1] = true;
	For(i, 1, n) {
		int pl = 0, pr = 0;
		For(j, 0, n) {
			int r = j + 1;
			while (!vis[r]) ++r;
			if (r - j > pr - pl) pl = j, pr = r;
			j = r - 1;
		}
		int mx = (pr - pl) / 2;
		cnt[mx]++;
		pos[i] = pl + mx;
		vis[pl + mx] = true;
		if ((pr - pl) % 2) odd[mx]++;		
	}
	int sum = n;
	For(i, 1, n) if (cnt[i]) {	
		int l = sum - cnt[i] + 1, r = sum;
		if (i == 1) {
			For(j, l, r) For(k, l, r) 
				dp[j][pos[k]] = inv[cnt[i]];
		} else {

			For(j, 0, cnt[i]) For(k, 0, odd[i]) f[j][k] = 0;
			f[0][odd[i]] = 1;

			int p = l + odd[i] - 1;
			For(j, 1, cnt[i]) {
				int oddw = 0, evenw = 0;
				For(k, 0, odd[i]) if (f[j - 1][k]) {
					int frac = (cnt[i] - j + 1) + k, w = 0;
					if (k) {
						w = f[j - 1][k] * k * 2 % Mod * inv[frac] % Mod;
						oddw = (oddw + w * inv[odd[i] * 2]) % Mod;
						add(f[j][k - 1], w);
					}
					if (cnt[i] - odd[i]) {
						w = f[j - 1][k] * (frac - 2 * k) % Mod * inv[frac] % Mod;
						evenw = (evenw + w * inv[cnt[i] - odd[i]]) % Mod;
						add(f[j][k], w);
					}
				}
				For(u, l, p) add(dp[l + j - 1][pos[u]], oddw), add(dp[l + j - 1][pos[u] + 1], oddw);
				For(u, p + 1, r) add(dp[l + j - 1][pos[u]], evenw);
			}

		//	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
		//		printf("%d%c", dp[i][j], j == n ? '\n' : ' ');
		printf("%d %d\n",l,p);
			For(j, l, p) {
				int L = pos[j] - i + 1, R = pos[j] + i;	
				printf("%d %d %d\n",j,L,R);
				For(v, L, R) if (v != pos[j]) For(u, r + 1, n) {
				
			
					int s = v < pos[j] ? v + i + 1 : v - i, w = dp[u][v] * inv[2] % Mod;
					add(g[u][v], w), add(g[u][s], w);
		//				printf("%d %d\n",v,s);
				}
				For(v, L, R) For(u, r + 1, n) 
					dp[u][v] = g[u][v], g[u][v] = 0;
			}	

		}
		sum = l - 1;
	}

	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
		printf("%d%c", dp[i][j], j == n ? '\n' : ' ');

	return 0;
}
