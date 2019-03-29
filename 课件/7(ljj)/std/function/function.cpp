#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int N = 5e5 + 10;

int A[N];
LL S[N], ans[N];
int n, m;

struct Query {
	int x, y, id;

	bool operator < (const Query& B) const {
		return x < B.x;
	}

}Q[N];

int st[N], L[N], c;

LL calc(int x, int y, int u) {
	return S[x] - S[u] + 1ll * (y + u) * A[u];
}

int main() {

	freopen("function.in", "r", stdin);
	freopen("function.out", "w", stdout);

	scanf("%d", &n);
	For(i, 1, n) scanf("%d", &A[i]), S[i] = S[i - 1] + A[i];
	scanf("%d", &m);
	For(i, 1, m) scanf("%d%d", &Q[i].y, &Q[i].x), Q[i].id = i;
	sort(Q + 1, Q + m + 1);

	L[0] = 1e9;
	int p = 1;
	For(i, 1, n) {
		while (c && calc(i, L[c - 1] - 1, st[c]) >= calc(i, L[c - 1] - 1, i)) --c;
		if (c) {
			int l = L[c], r = L[c - 1] - 1;
			while (l < r) {
				int mid = (l + r) >> 1;
				if (calc(i, mid, st[c]) < calc(i, mid, i)) r = mid;
				else l = mid + 1;
			}
			L[c] = l;
		}
		st[++c] = i, L[c] = 1 - i;

		while (p <= m && Q[p].x == i) {
			int l = 1, r = c;
			while (l < r) {
				int mid = (l + r) >> 1;
				if (L[mid] <= Q[p].y - i) r = mid;
				else l = mid + 1;
			}
			ans[Q[p].id] = calc(i, Q[p].y - i, st[l]);
			++p;
		}
	}

	For(i, 1, m) printf("%lld\n", ans[i]);

	return 0;
}
