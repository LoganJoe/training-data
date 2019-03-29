#include<bits/stdc++.h>
#define N 100005
int n, m, mark[N], p[5], c[5], f[N], mark2[N], ans, cnt;
int main ()
{
	freopen("fan.in","r",stdin);
	freopen("fan.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1, x; i <= m; i++) scanf ("%d", &x), mark[x] ++;
	for (int tmp = n, i = 2; i <= n; i++)
		if (tmp%i == 0)
		{
			p[++p[0]] = i;
			while (tmp%i == 0) tmp /= i;
			if (tmp == 1) break;
		}
	if (p[0] == 1 && p[1]==n) return puts ("-1"), 0;
	if (!p[2]) p[2] = 1;
	c[1] = n / p[1], c[2] = n / p[2];
	for (int k = 1; k <= n / p[1] / p[2]; k++)
	{
		int cnt = 0, tp = 0;
		for (int i = 0; i < p[1]; i++) f[i] = 0;
		for (int i = 0; i < p[2]; i++)
		{
			int pw = (i*c[2] + k - 1)%n + 1, flag = 1;
			for (int j = 0; j < p[1]; j++,pw = (pw + c[1] - 1) % n + 1)
				if (mark[pw]) f[j] = 1, flag = 0;
			cnt += flag;
		}
		for (int i = 0; i < p[1]; i++) tp += !f[i];
		if(p[2]==1) tp=0;
		ans += std::max (cnt*p[1], tp*p[2]);
	}
	if(!ans) return puts("-1"),0;
	printf ("%d\n", n - m - ans);
}
/*
675 5
3 123 233 250 450
*/
