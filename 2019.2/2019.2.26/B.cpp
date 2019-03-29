
#include<bits/stdc++.h>
#define N 100005
int n, A[N];
std::bitset<N> s, t, mark;
bool check (int mid)
{
	if (mid == 0) return 1;
	s.reset ();
	for (int i = mid; i < A[1]; i++) s[i] = 1;
	for (int i = 1; i <= n; i++) if (A[i] ^ A[i - 1])
	{
		t = s ^ ((s >> A[i]) << A[i]);
		for (int j = 1; j <= (A[n] / A[i]) + 1; ++j) t |= (t << A[i]);
		s |= t;
		if ((mark&s).count ()) return 1;
	}
	return 0;
}
int main ()
{
	freopen ("array.in", "r", stdin);
	freopen ("array.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), mark[A[i]] = 1;
	std::sort (A + 1, A + 1 + n); A[0] = -1;
	if (A[1] ^ A[2]) return printf ("%d\n", A[1]), 0;
	int l = 0, r = A[1] - 1, res;
	//for (int mid; l <= r; mid = l + r >> 1, check (mid) ? (l = mid + 1, res = mid) : r = mid - 1);
	for (int mid; l < r; mid = l + r + 1 >> 1, check (mid) ? l = mid : r = mid - 1);
	//printf ("%d\n", res);
	printf ("%d\n", l);
}
