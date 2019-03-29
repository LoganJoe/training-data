#include<bits/stdc++.h>
#define mod 26281314
#define N 1005
int n, x1, Y1, x2, y2, ans;
int a[N][N], b[N][N], c[N][N], s[N][N], cnt;
int tx[] = { 1,0,-1,0 }, ty[] = { 0,1,0,-1 };
bool check (int x, int y) { return x<1 || x>n || y<1 || y>n; }
void work (int x, int y, int dx, int dy)
{
	s[x][y] = ++cnt;
	if (s[x + dx][y + dy] || check (x + dx, y + dy))
	{
		for (int k = 0; k < 4; k++) 
			if (!s[x + tx[k]][y + ty[k]] && !check (x + tx[k], y + ty[k])) 
				return work (x + tx[k], y + ty[k], tx[k], ty[k]);
	}
	else work (x + dx, y + dy, dx, dy);
}
int main ()
{
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
	scanf ("%d%d%d%d%d", &n, &x1, &Y1, &x2, &y2);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int Min = std::min (std::min (i, j), std::min (n - i + 1, n - j + 1));
			a[i][j] = Min;
		}
	work (1, 1, 0, 1);// work (1, 1, 1, 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) b[i][j] = s[i][j], s[i][j] = 0;
	cnt = 0; work (1, 1, 1, 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) c[i][j] = s[i][j], s[i][j] = 0;
	for (int i = x1; i <= x2; i++)
		for (int j = Y1; j <= y2; j++) ans = (ans + 1ll * a[i][j] * b[i][j] % mod * c[i][j] % mod) % mod;
	printf ("%d\n", ans);
}
