#include<bits/stdc++.h>
#define N 200005
#define ll long long
int n, l[N], r[N], Maxl, Minr; ll ans;
namespace solve1
{
	void Main ()
	{
		if (r[Minr] - l[Maxl] + 1 > 0) ans += r[Minr] - l[Maxl] + 1;
		for (ll k = 1;; k++)
		{
			ll L = -1e9, R = 1e9;
			for (int i = 1; i <= n; i++)
				L = std::max (L, l[i] - k * i),
				R = std::min (R, r[i] - k * i);
			if (L > R) break; ans += R - L + 1;
		}
		for (ll k = 1;; k++)
		{
			ll L = -1e9, R = 1e9;
			for (int i = 1; i <= n; i++)
				L = std::max (L, l[i] + k * i),
				R = std::min (R, r[i] + k * i);
			if (L > R) break; ans += R - L + 1;
		}
		std::cout << ans << "\n";
	}
}
namespace solve2
{
	void Main ()
	{
		if (r[Minr] - l[Maxl] + 1 > 0) ans += r[Minr] - l[Maxl] + 1;
		for (int i = 2; i <= Maxl; i++) l[i] = std::max (l[i], l[i - 1]);
		for (int i = 2; i <= Minr; i++) r[i] = std::min (r[i], r[i - 1]);
		for (int i = n - 1; i >= Maxl; i--) l[i] = std::max (l[i], l[i + 1]);
		for (int i = n - 1; i >= Minr; i--) r[i] = std::min (r[i], r[i + 1]);
		/*
		for (int k = 1;; k++)
		{
			int L = 1, R = n, tL;
			while (R - L > 2)
			{
				int Lmid = L + (R - L) / 3, Rmid = R - (R - L) / 3;
				if (l[Lmid] - k * Lmid < l[Rmid] - k * Rmid) L = Lmid + 1;
				else R = Rmid;
			}
			while (L < R && l[L] - k * L < l[L + 1] - k * (L + 1)) L++;
			tL = L; L = 1, R = n;
			while (R - L > 2)
			{
				int Lmid = L + (R - L) / 3, Rmid = R - (R - L) / 3;
				if (r[Lmid] - k * Lmid > r[Rmid] - k * Rmid) L = Lmid + 1;
				else R = Rmid;
			}
			while (L < R && r[R] - k * R > r[R - 1] - k * (R - 1)) R--;
			if (r[L] - k * L < r[R] - k * R) std::swap (L, R);
			if (l[tL] - k * tL > r[R] - k * R) break;
			ans += r[R] - k * R - l[tL] + k * tL + 1;
			std::cout<<l[tL] - k * tL<<" "<<r[R] - k * R<<"\n";
			//std::cout<<r[L] - k * L - l[tL] + k * tL + 1<<"\n";
			if(l[tL]-k*tL==29213)
			{
				for(int i=1;i<=n;i++) std::cout<<l[i]<<" ";
				puts("");
				for(int i=1;i<=n;i++) std::cout<<l[i]-k*i<<" ";
				puts("");
			}
		}
		*/
		for (ll k = 1;; k++)
		{
			int L = 1, R = n, tL;
			while (R - L > 2)
			{
				int Lmid = L + (R - L) / 3, Rmid = R - (R - L) / 3;
				if (l[Lmid] + k * Lmid < l[Rmid] + k * Rmid) L = Lmid + 1;
				else R = Rmid;
			}
			while (L < R && l[L] + k * L <= l[L + 1] + k * (L + 1)) L++;
			tL = L; L = 1, R = n;
			while (R - L > 2)
			{
				int Lmid = L + (R - L) / 3, Rmid = R - (R - L) / 3;
				if (r[Lmid] + k * Lmid > r[Rmid] + k * Rmid) L = Lmid + 1;
				else R = Rmid;
			}
			while (L < R && r[R] + k * R >= r[R - 1] + k * (R - 1)) R--;
			if (r[L] +k * L < r[R] + k * R) std::swap (L, R);
			if (l[tL] + k * tL > r[R] + k * R) break;
			ans += r[R] + k * R - l[tL] - k * tL + 1;
			//std::cout<<l[tL] + k * tL<<" "<<r[R] + k * R<<"\n";
			//std::cout<<r[L] + k * L - l[tL] - k * tL + 1<<"\n";
		}
		for (int i = 1; i <= n; i++) std::swap (l[i], r[i]), l[i] = -l[i], r[i] = -r[i];
		for (ll k = 1;; k++)
		{
			int L = 1, R = n, tL;
			while (R - L > 2)
			{
				int Lmid = L + (R - L) / 3, Rmid = R - (R - L) / 3;
				if (l[Lmid] + k * Lmid < l[Rmid] + k * Rmid) L = Lmid + 1;
				else R = Rmid;
			}
			while (L < R && l[L] + k * L <= l[L + 1] + k * (L + 1)) L++;
			tL = L; L = 1, R = n;
			while (R - L > 2)
			{
				int Lmid = L + (R - L) / 3, Rmid = R - (R - L) / 3;
				if (r[Lmid] + k * Lmid > r[Rmid] + k * Rmid) L = Lmid + 1;
				else R = Rmid;
			}
			while (L < R && r[R] + k * R >= r[R - 1] + k * (R - 1)) R--;
			if (r[L] +k * L < r[R] + k * R) std::swap (L, R);
			if (l[tL] + k * tL > r[R] + k * R) break;
			ans += r[R] + k * R - l[tL] - k * tL + 1;
			//std::cout<<k<<" "<<-(r[R] + k * R)<<" "<<-(l[tL] + k * tL)<<"\n";
			//std::cout<<r[L] + k * L - l[tL] - k * tL + 1<<"\n";
		}
		std::cout << ans << "\n";
	}
}
namespace solve3
{
	void Main ()
	{
		if (r[Minr] - l[Maxl] + 1 > 0) ans += r[Minr] - l[Maxl] + 1;
		for (int i = 2; i <= Maxl; i++) l[i] = std::max (l[i], l[i - 1]);
		for (int i = 2; i <= Minr; i++) r[i] = std::min (r[i], r[i - 1]);
		for (int i = n - 1; i >= Maxl; i--) l[i] = std::max (l[i], l[i + 1]);
		for (int i = n - 1; i >= Minr; i--) r[i] = std::min (r[i], r[i + 1]);
		for (int k = 1, s1 = Maxl, s2 = Minr;; k++)
		{
			for (; s1 > 1 && l[s1] - k * s1 <= l[s1 - 1] - k * (s1 - 1); s1--);
			for (; s2 < n && r[s2] - k * s2 >= r[s2 + 1] - k * (s2 + 1); s2++);
			if (l[s1] - k * s1 > r[s2] - k * s2) break;
			ans += r[s2] - k * s2 - l[s1] + k * s1 + 1;
		}
		for (int k = 1, s1 = Maxl, s2 = Minr;; k++)
		{
			for (; s1 < n && l[s1] + k * s1 <= l[s1 + 1] + k * (s1 + 1); s1++);
			for (; s2 > 1 && r[s2] + k * s2 >= r[s2 - 1] + k * (s2 - 1); s2--);
			if (l[s1] + k * s1 > r[s2] + k * s2) break;
			ans += r[s2] + k * s2 - l[s1] - k * s1 + 1;
		}
		std::cout << ans << "\n";
	}
}
int main ()
{
	freopen("line.in","r",stdin);
	freopen("line.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d%d", &l[i], &r[i]);
	Maxl = 1, Minr = 1;
	for (int i = 1; i <= n; i++) if (l[i] > l[Maxl]) Maxl = i;
	for (int i = 1; i <= n; i++) if (r[i] < r[Minr]) Minr = i;
	return solve1::Main (), 0;
	//return solve2::Main (), 0;
}
/*
3
1 3
2 3 
1 5

*/
