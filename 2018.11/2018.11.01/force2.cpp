#include<bits/stdc++.h>
const int N = 200005, M = 450, mod = 1000000007;
int n, m, Q, A[N];
int mul (int x) { return x >= mod ? x - mod : x; }
int calm (int x) { return x >= m ? x - m : x; }
struct node
{
	int s[22];
};
int main ()
{
	freopen("yukari.in","r",stdin);
	freopen("yukari.ans","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), A[i] %= m;
	scanf ("%d", &Q);
	while (Q--)
	{
		int l, r; scanf ("%d%d", &l, &r);
		node tp[2]; for (int i = 0; i < m; i++) tp[0].s[i] = tp[1].s[i] = 0;
		tp[0].s[0] = 1;
		for (int i = l, k = 1; i <= r; i++, k ^= 1)
		{
			for (int j = 0; j < m; j++)
				tp[k].s[j] = mul (tp[k ^ 1].s[j] + tp[k ^ 1].s[calm (j - A[i] + m)]);
			//tp[k].s[A[i]]++;
		}
		printf ("%d\n", tp[(r - l + 1) & 1].s[0]);
	}
}
