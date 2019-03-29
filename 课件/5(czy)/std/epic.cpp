#include <cstdio>
#include <algorithm>
#include <cstring>

#define Rep(i, n) for (int i = 1; i <= n; i ++)
#define Rep0(i, n) for (int i = 0; i <= n; i ++)

using namespace std;

const int N = 2000010;
typedef long long LL;

int a[N], n;
LL s[N], q[N];

LL solve(int k)
{
	int he0 = n + 1 - ((k - 1 - ((n - 1) % (k - 1))) % (k - 1)), he = 1, ta = 0;
	//printf("%d %d\n", k, n * 2 - he0 + 1);
	LL ret = 0;
	while (true) {
		int tmp = he0 + k - 1;
		LL sum = 0;
		while (tmp >= he0 && he <= ta && (tmp > n * 2 || a[tmp] > q[he])) tmp --, sum += q[he], he ++;
	//	printf("%d %lld\n", tmp, s[tmp]);
		sum += s[tmp] - s[he0 - 1];
		if (tmp > n * 2) break;
		he0 = tmp + 1, q[++ ta] = sum, ret += sum;
	}
	return ret;
}

int read()
{
	int ret = 0; char k = getchar();
	while (k < '0' || k > '9') k = getchar();
	while (k >= '0' && k <= '9') ret = ret * 10 + k - '0', k = getchar();
	return ret;
}

int main()
{
	freopen("epic.in", "r", stdin);
	freopen("epic.out", "w", stdout);
	scanf("%d", &n);
	Rep(i, n) a[i] = read();
	sort(a + 1, a + 1 + n * 2);
	for (int i = n + 1; i <= n * 2; i ++) s[i] = s[i - 1] + a[i];
	LL ans = 0;	
	for (int i = 2; i <= n; i++) ans ^= solve(i);
	printf("%lld\n", ans);
		//for (int i = 2; i <= n; i ++) printf("%lld\n", solve(i));
	return 0;
}
