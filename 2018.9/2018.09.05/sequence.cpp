#include<bits/stdc++.h>
#define N 100005
int n, K, A[N], cnt, pos[N], mark[N], num[N], fl[20], ans;
class BIT
{
	int t[N];
	int lowbit (int x) { return x & (-x); }
public:
	void add (int x, int y) { for (int i = x; i <= n; i += lowbit (i)) t[i] += y; }
	int ask (int x) { int res = 0; for (int i = x; i; i -= lowbit (i)) res += t[i]; return res; }
}T[15][2];
void solve1 ()
{

	cnt = 0; for (int i = 1; i <= n; i++) if (!A[i]) pos[++cnt] = i;
	for (int i = 1; i <= n; i++) mark[A[i]] = 1;
	cnt = 0; for (int i = 1; i <= n; i++) if (!mark[i]) num[++cnt] = i;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= cnt; j++) if (A[i])T[j][i <= pos[j]].add (i <= pos[j] ? n - A[i] + 1 : A[i], 1);
	int base=0;
	for (int i = 1; i <= n; i++) if (A[i])base += T[0][0].ask (n-A[i]+1), T[0][0].add (A[i], 1);
	std::sort (num + 1, num + 1 + cnt);
	do
	{
		int res = 0;
		for (int i = 1; i <= cnt; i++) res += T[i][1].ask (n - num[i]) + T[i][0].ask (num[i]);
		for (int i = 1; i <= cnt; i++)
			for (int j = i + 1; j <= cnt; j++) res += num[i] > num[j];
		if (res + base == K) ans++;
	} while (std::next_permutation (num + 1, num + 1 + cnt));
	printf ("%d\n", ans);
}
int main ()
{	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf ("%d%d", &n, &K);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), cnt += A[i] == 0;
	if (cnt <= 10) solve1 ();
}
