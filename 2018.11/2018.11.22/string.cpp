#include<bits/stdc++.h>
#define N 205
int T, n, cnt[N], tot[N], len, ansl;
int f[N][N];
char s[N], t[N], ans[N];
void clear ()
{
	for (int i = 0; i <= 200; i++) cnt[i] = 0;
}
void update ()
{
	if (len < ansl) return (void)(ansl=len, std::swap (t, ans));
	if (len > ansl) return;
	for (int i = 1; i <= ansl; i++)
	{
		if (ans[i] > t[i]) break;
		if (ans[i] < t[i]) return;
	}
	std::swap (t, ans);
}
bool solve ()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) f[i][j] = 0;
	for (int i = 1; i <= n; i++) if (s[i] == t[1]) f[i][i] = 1;
	for (int le = 2; le <= n; le++)
	{
		for (int l = 1; l + le - 1 <= n; l++)
		{
			int r = l + le - 1;
			if (s[r] == t[(le - 1) % len + 1]) f[l][r] |= f[l][r - 1];
			if (f[l][r]) continue;
			for (int k = l + len; k <= r; k += len)
				if (f[l][k - 1]) f[l][r] |= f[k][r];
			for (int k = r - len; k >= l; k -= len)
				if (f[k + 1][r]) f[l][r] |= f[l][k];
		}
	}
	return f[1][n];
}
int main ()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	for (scanf ("%d", &T); T--; clear ())
	{
		scanf ("%s", s + 1); ansl = n = strlen (s + 1);
		for (int i = 1; i <= n; i++) cnt[s[i]]++;
		for (int i = 1; i <= n; i++)
			for (int j = i; j <= n; j++)
			{
				if (n % (j - i + 1)) goto END;
				for (int k = 1; k < 200; k++) 
					if (cnt[k] && cnt[k] % (n / (j - i + 1))) goto END;
				for (int k = 1; k <= 200; k++) tot[k] = 0;
				len = 0;
				for (int k = i; k <= j; k++) t[++len] = s[k], tot[s[k]]++;
				for (int k = i; k <= j; k++) if (cnt[s[k]] % tot[s[k]]) goto END;
				if (solve ()) update ();
			END:;
			}
		for (int i = 1; i <= ansl; i++) printf ("%c", ans[i]);
		puts ("");
	}

}

