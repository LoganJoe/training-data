#include <cstdio>
#include <vector>

#define iter(i, n) for (int i = 1; i <= n; ++i)
#define iter_r(i, n) for (int i = n; i >= 1; --i)

const int NR = 1e6 + 100;

std::vector<int> a[NR];
int c[NR], xs[NR], n, m;
bool vis[NR];

int read()
{
	int ret = 0; char k = getchar();
	while (k < '0' || k > '9') k = getchar();
	while (k >= '0' && k <= '9') ret = ret * 10 + k - '0', k = getchar();
	return ret;
}


int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d%d", &n, &m);
	iter(i, n) c[i] = read();
	iter(i, m) {
		int l, r;
		l = read(); r = read();
		a[l].push_back(r);
	}
	iter_r(i, n) {
		for (int r : a[i]) vis[xs[i + 1] ^ xs[r + 1]] = true;
		for (xs[i] = 1; vis[xs[i]]; ++xs[i]);
		xs[i] ^= xs[i + 1];
		for (int r : a[i]) vis[xs[i + 1] ^ xs[r + 1]] = false;
	}
	int sum = 0;
	iter(i, n) if (c[i] == 1) sum ^=  xs[i] ^ xs[i + 1];
	printf("%s\n", sum ? "First" : "Second");
	return 0;
}
