#include <bits/stdc++.h>
#include "triplet.h"

namespace Interaction_Libary {

	using std::min;
	using std::max;

	const int MaxCase = 10;
	const int Maxn = 10000;
	const int Base = 233, Mod = 998244353;

	int Case, Max_Score, Taskid;
	int data[MaxCase + 5][Maxn + 5], N[MaxCase + 5];

	int n, *A, qcnt;

	int query(int x, int y, int z) {
		assert(x >= 1 && x <= n);
		assert(y >= 1 && y <= n);
		assert(z >= 1 && z <= n);
		assert(x != y && y != z && z != x);
		++qcnt;
		return max(A[x], max(A[y], A[z])) + min(A[x], min(A[y], A[z]));
	}

	double getscore(int a, int b) {
		if (a <= b) return 1.0;
		else if (a <= b * 3 / 2) return 0.9 - 0.6 * (a - b) / b;
		else if (a <= b * 3) return 0.7 - 0.2 * (a - b) / b;
		else return max(0.1, 0.34 - 0.02 * (a - b) / b);
	}

	void work() {
		scanf("%d%d%d", &Case, &Taskid, &Max_Score);
		for (int i = 1; i <= Case; i++) {
			scanf("%d", &N[i]), assert(N[i] >= 5 && N[i] <= 10000);
			for (int j = 1; j <= N[i]; j++)
				scanf("%d", &data[i][j]), assert(data[i][j] >= 1 && data[i][j] <= 1000000000);
		}

		double score = Max_Score;
		for (int i = 1; i <= Case; i++) {
			A = data[i], n = N[i];
			qcnt = 0;
			int ans = guess(n, Taskid), P = min(2 * n, n + 35), val = 0;
			for (int j = n; j; --j) val = 1ll * (val + A[j]) * Base % Mod;
			if (val != ans) {
				printf("wa %d\n", i);
				exit(0);
			}
			score = min(score, Max_Score * getscore(qcnt, P));
		}
		printf("ok %.2lf\n", score);
	}

};

int query(int x, int y, int z) {
	return Interaction_Libary::query(x, y, z);
}

int main() {

	Interaction_Libary::work();

	return 0;
}
