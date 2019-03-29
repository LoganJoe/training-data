#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <iomanip>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef long double db;

const int MAXN = 1005;
const int MOD = 998244353;

int n,m,ans;
int f[MAXN][8][MAXN * 7];

int main()
{
	cin >> n >> m;
	f[0][0][0] = 1;
	for (int i = 0;i < n;i++)
		for (int j = 0;j <= min(i,m);j++)
		{
			for (int k = 0;k <= (i + i - j + 1) * j / 2;k++)
			{
				(f[i + 1][j][k] += f[i][j][k]) %= MOD;
				(f[i + 1][j + 1][k + i + 1] += f[i][j][k]) %= MOD;
			}
			for (int k = (i + i - j + 1) * j / 2 - 1;k >= 0;k--)
				(f[i][j][k] += f[i][j][k + 1]) %= MOD;
		}
	for (int i = m;i <= n;i++)
		(ans += f[i - 1][m - 1][i + 1]) %= MOD;
	cout << ans << endl;
 	return 0;
}

