#include<bits/stdc++.h>

namespace FAST_IO  //writen by laofudasuan, copyright MIT lisence, modified.
{
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	template <class I>
	inline void get (I &x) {
		for (f = 1, c = gc (); c < '0' || c > '9'; c = gc ()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc ()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I &x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++qr] = x % 10 + '0', x /= 10;
		while (qr) putc (qu[qr--]);
		putc('\n');
	}
	//no need to call flush at the end manually
	struct Flusher_ { ~Flusher_ () { flush (); } }IO_flusher_;
}
using FAST_IO::get;
using FAST_IO::putc;
using FAST_IO::print;

#define N 1500005

int n, m, A[N], ans[N];

class BIT
{
	int t[N];
public:
	void add (int x, int v) { for (; x <= n; x += x & -x) t[x] += v; }
	int ask (int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }
}T;

class ConnectTree
{
public:
	int f[N];
	int find (int x) { return f[x] == x ? f[x] : f[x] = find (f[x]); }
	void clear () { for (int i = 1; i <= n; i++) f[i] = i; }
}F1, F2;

int sta[N], f[N], top;
struct node
{
	int l, r, id;
}q[N];
int main ()
{
	freopen("exchange.in", "r", stdin);
	freopen("exchange.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) get(A[i]);
	for (int i = 1; i <= m; i++) get(q[i].l), get(q[i].r), q[i].id = i;
	std::sort (q + 1, q + 1 + m, [](node t1, node t2) {return t1.r < t2.r; });
	F1.clear (), F2.clear ();
	for (int i = 1; i <= n; i++)
	{
		for (; top && A[sta[top]] < A[i]; top--);
		f[i] = sta[top] + 1, sta[++top] = i;
	}
	for (int i = 1, j = 1; i <= m; i++)
	{
		for (; j <= q[i].r; j++)
		{
			T.add (f[j], 1), T.add (j + 1, -1);
			int pa = F1.find (f[j] - 1);
			if (pa) F1.f[pa] = F1.find (pa - 1), F2.f[pa] = F2.find (pa + 1);
		}
		ans[q[i].id] = T.ask (F2.find (q[i].l));
	}
	for (int i = 1; i <= m; i++) print(ans[i]);
}
/*
8 10
3 1 3 4 2 5 5 2 
2 8 
3 3 
1 2
2 6 
1 4 
3 8
4 7 
2 6 
2 2 
2 2


*/