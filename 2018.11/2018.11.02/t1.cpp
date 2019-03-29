#include<bits/stdc++.h>
#define N 200005
struct node
{
	int x, op, id;
	friend bool operator <(node t1, node t2){return t1.x < t2.x;}
}A[N];
int n, Q, pos[N], ans[N];
struct ask
{
	int v, t, id;
	friend bool operator <(ask t1, ask t2) { return pos[t1.v] > pos[t2.v]; }
}q[N];
int s1[N], cnt1, s2[N], cnt2;
int main ()
{
	freopen("bridge.in","r",stdin);
	freopen("bridge.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i].x), A[i].id = i;
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i].op), pos[i] = A[i].x;
	std::sort (A + 1, A + 1 + n);
	scanf ("%d", &Q);
	for (int i = 1; i <= Q; i++) scanf ("%d%d", &q[i].v, &q[i].t), q[i].v++, q[i].id = i;
	std::sort (q + 1, q + 1 + Q);
	for (int i = 1; i <= n; i++) if (A[i].op) s1[++cnt1] = A[i].x;
	for (int i = n, j = 1; i; i--)
	{
		if (!A[i].op) s2[++cnt2] = A[i].x;
		while (j <= Q && q[j].v == A[i].id)
		{
			if (!s1 && !s2 || s1[cnt1] + 2 * q[j].t <= s2[cnt2])
			{
				ans[q[j].id] = A[i].x + (A[i].op ? 1 : -1) * q[j].t, j++;
				continue;
			}
			int l = 1, r = std::min (cnt1, cnt2);
			while (l < r)
			{
				int mid = (l + r + 1) >> 1;
				if (s1[cnt1 - mid + 1] +  2 * q[j].t >= s2[cnt2 - mid + 1]) l = mid;
				else r = mid - 1;
			}
			if (A[i].op)
			{
				if (l != cnt1 && s1[cnt1 - l] + q[j].t > s2[cnt2 - l + 1]) ans[q[j].id] = s1[cnt1 - l] + q[j].t;
				else ans[q[j].id] = s2[cnt2 - l + 1] - q[j].t;
			}
			else
			{
				if (l != cnt2 && s1[cnt1 - l + 1] + q[j].t < s2[cnt2 - l]) ans[q[j].id] = s2[cnt2 - l] - q[j].t;
				else ans[q[j].id] = s1[cnt1 - l + 1] + q[j].t;
			}
			j++;
		}
		if(A[i].op &&A[i].x==s1[cnt1]) cnt1--;
	}
	for (int i = 1; i <= Q; i++) printf ("%d\n", ans[i]);
}
