#include<bits/stdc++.h>
#define N 1000005
int A[N];
int n, ans, q, num[32][2], Log[N], fl[N];
int lg (int x) { return (x >> 15) ? (Log[x >> 15] + 15) : Log[x]; }
void add (int i, int op)
{
	if (i > 1)
	{
		int x = lg (A[i] ^ A[i - 1]), y = 1 << x;
		if (A[i] & y) num[x][0]+=op; else num[x][1]+=op;
	}
	if (i < n)
	{
		int x = lg (A[i + 1] ^ A[i]), y = 1 << x;
		if (A[i + 1] & y) num[x][0] += op; else num[x][1] += op;
	}
}
struct node
{
	int l, r, t;
};
int solve ()
{
	std::queue<node> q; q.push ({ 1,n,30 });
	for (int i = 0; i < 30; i++) fl[i] = -1;
	while (!q.empty ())
	{
		node u = q.front (); q.pop (); int mark = 0;

		if (u.l >= u.r || u.t < 0) continue;
		for (int i = u.l; i < u.r; i++)
		{
			if ((A[i] >> u.t & 1) ^ (A[i + 1] >> u.t & 1))
				if (!mark) mark = i;
				else return -1;
		}
		if (!mark) q.push ({ u.l,u.r,u.t - 1 });
		else
		{
			q.push ({ u.l,mark,u.t - 1 });
			q.push ({ mark + 1,u.r,u.t - 1 });
			if (fl[u.t] == -1) fl[u.t] = A[u.l] >> u.t & 1;
			else if (fl[u.t] ^ (A[u.l] >> u.t & 1)) return -1;
		}
	}
	int ans = 0;
	for (int i = 0; i < 30; i++) if (fl[i] != -1)ans += fl[i] << i;
	return ans;
}
int main ()
{
	Log[0] = -1; for (int i = 1; i <= 32768; i++)Log[i] = Log[i >> 1] + 1;
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d", &A[i]);
		if (i > 1) 
		{
			int x = lg (A[i] ^ A[i - 1]), y = 1 << x;
			if (A[i] & y) num[x][0]++;
			else num[x][1]++;
		}
	}
	{
		for (int i = 0; i <= 30; i++)
		{
			if (num[i][0] && num[i][1]) { ans = -1; break; }
			if (num[i][1])ans |= (1 << i);
		}
		printf ("%d\n", ans);
	}
	for (scanf ("%d", &q); q--;)
	{
		int x, y; scanf ("%d %d", &x, &y);
		add (x, -1); A[x] = y; add (x, 1);
		ans = 0;
		for (int i = 0; i <= 30; i++)
		{
			if (num[i][0] && num[i][1]) { ans = -1; break; }
			if (num[i][1])ans |= (1 << i);
		}
		printf ("%d\n", ans);
	}
}
