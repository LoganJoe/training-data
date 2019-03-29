#include <bits/stdc++.h>
#define N 105
int n, m, P[N][N], A[N][N], sum[N][N][12], num[12];
int sqsum(int x1, int y1, int x2, int y2, int k)
{
	return sum[x2][y2][k] - sum[x2][y1 - 1][k] - sum[x1 - 1][y2][k] + sum[x1 - 1][y1 - 1][k];
}
struct node
{
	int x1, y1, x2, y2, k;
};
std::vector<node> ans;
void solve(int x, int y)
{
	int Max = 1, tx = x, ty = y, val = 0;
	for (int i = x; i <= n; i++)
		for (int j = y; j <= m; j++)
			if (i != x || j != y)
			{
				for (int k = 0; k < 10; k++)
					num[k] = sqsum(x, y, i, j, k);
				int Maxk = 0;
				for (int k = 1; k < 10; k++)
					if (num[Max] < num[k])
						Max = k;
				if (Max == 0)
					continue;
				if (num[Max] - num[0] - ((A[x][y] - Max + P[x][y]) % P[x][y] != 0) > Max)
					Max = num[Max] - num[0] - ((A[x][y] - Max + P[x][y]) % P[x][y] != 0), tx = i, ty = j, val = Maxk;
			}
	if (Max == 1 && A[x][y] == 0)
		return;
	for (int i = x; i <= tx; i++)
		for (int j = y; j <= ty; j++)
			A[i][j] = (A[i][j] - val + P[i][j]) % P[i][j];
	ans.push_back({x, y, tx, ty, val});
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0; k < 10; k++)
			{
				sum[i][j][k] = sum[i - 1][j][k] + sum[i][j - 1][k] - sum[i - 1][j - 1][k];
				if (A[i][j] == k)
					sum[i][j][k]++;
			}
}
int main()
{
	freopen("bake.in", "r", stdin);
	freopen("bake.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &P[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &A[i][j]), A[i][j] = (P[i][j] - A[i][j]) % P[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0; k < 10; k++)
			{
				sum[i][j][k] = sum[i - 1][j][k] + sum[i][j - 1][k] - sum[i - 1][j - 1][k];
				if (A[i][j] == k)
					sum[i][j][k]++;
			}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) solve(i, j);
	printf("%d\n", ans.size());
	for (node v : ans)
		printf("%d %d %d %d %d\n", v.x1, v.y1, v.x2, v.y2, v.k);
}