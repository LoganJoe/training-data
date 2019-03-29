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
int k;
struct node
{
	int v,id;
	friend bool operator <(node t1,node t2){return t1.v+k*t1.id > t2.v+k*t2.id;}
};
std::set<node> S1,S2;
namespace solve2
{
	void Main ()
	{
		if (r[Minr] - l[Maxl] + 1 > 0) ans += r[Minr] - l[Maxl] + 1;
		for (int i = 2; i <= Maxl; i++) l[i] = std::max (l[i], l[i - 1]);
		for (int i = 2; i <= Minr; i++) r[i] = std::min (r[i], r[i - 1]);
		for (int i = n - 1; i >= Maxl; i--) l[i] = std::max (l[i], l[i + 1]);
		for (int i = n - 1; i >= Minr; i--) r[i] = std::min (r[i], r[i + 1]);
		for(int i=1;i<=n;i++) S1.insert({l[i],i}),S2.insert({-r[i],-i});
		for (k = 1;; k++)
		{
			auto it1 = S1.begin(),it2 = S2.begin();
			node s1= *it1,s2= *it2;
			std::cout<<s1.v + s1.id*k<<" "<<-s2.v-s2.id*k<<"\n";
			if(s1.v + s1.id*k+s2.v+s2.id*k>=0) break;
			ans+=-(s1.v + s1.id*k+s2.v+s2.id*k)+1;
		}
		for (k = -1;; k--)
		{
			auto it1 = S1.begin(),it2 = S2.begin();
			node s1= *it1,s2= *it2;
			if(s1.v + s1.id*k+s2.v+s2.id*k>=0) break;
			ans+=-(s1.v + s1.id*k+s2.v+s2.id*k)+1;
		}
		std::cout << ans << "\n";
	}
}
int main ()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d%d", &l[i], &r[i]);
	Maxl = 1, Minr = 1;
	for (int i = 1; i <= n; i++) if (l[i] > l[Maxl]) Maxl = i;
	for (int i = 1; i <= n; i++) if (r[i] < r[Minr]) Minr = i;
	if (Minr <= 1e5) return solve1::Main (), 0;
	//return solve2::Main (), 0;
}
/*
3
1 3
2 3 
1 5

*/
