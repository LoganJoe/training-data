# include<cstdio>
# include<cstring>
# include<algorithm>
# include<set>
using namespace std;
const int N = 1e5 + 5;
set <int> fir,sec;
int st[N],to[N << 1],nx[N << 1],w[N << 1];
int n,Q,ans,tot,is;
inline void add(int u,int v,int c)
{
	to[++tot] = v,nx[tot] = st[u],w[tot] = c,st[u] =tot;
	to[++tot] = u,nx[tot] = st[v],w[tot] = c,st[v] = tot;
}
inline void dfs(int x,int e,int g,int f)
{
	++ans; if (x == g) is = 1;
	for (int i = st[x] ; i ; i = nx[i])
	if (to[i] != f && !(e && w[i] == 3)) dfs(to[i],e || (w[i] == 2) || (w[i] == 3),g,x);
}
int main()
{
//	freopen("A.in","r",stdin);
	scanf("%d%d",&n,&Q);
	for (int i = 1 ; i <= n - 1 ; ++i)
	{
		int u,v,c; scanf("%d%d%d",&u,&v,&c);
		add(u,v,c);
		if (c == 2) fir.insert(i);
		else if (c == 3) sec.insert(i);
	}
	if (Q <= 1000)
	{
		while (Q--)
		{
			int x,v,s,t; scanf("%d%d%d%d",&x,&v,&s,&t);
			x ^= ans,v ^= ans,s ^= ans,t ^= ans; ans = is = 0;
			w[x << 1] = w[(x << 1) - 1] = v,dfs(s,0,t,0);
			printf("%d %d\n",ans,is);
		}
	}else
	{
		while (Q--)
		{
			int x,v,s,t; scanf("%d%d%d%d",&x,&v,&s,&t);
			x ^= ans,v ^= ans,s ^= ans,t ^= ans; ans = 0;
			if (w[x << 1] == 2) fir.erase(x);
			else if (w[x << 1] == 3) sec.erase(x);
			w[x << 1] = w[(x << 1) - 1] = v;
			if (v == 2) fir.insert(x);
			else if (v == 3) sec.insert(x);
			int l = 0,l1 = 0;
			if (*fir.begin() < s && !fir.empty()) l = *(--fir.lower_bound(s));
			if (*sec.begin() < s && !sec.empty()) l1 = *(--sec.lower_bound(s));
			if (l < l1)
			{
				if (*sec.begin() < max(l,l1) && !sec.empty()) l = *(--sec.lower_bound(max(l,l1)));
				else l = 0;
			}else l = l1;
			int r = n,r1 = n;
			if (!fir.empty() && *(--fir.end()) >= s) r = *fir.lower_bound(s);
			if (!sec.empty() && *(--sec.end()) >= s) r1 = *sec.lower_bound(s);
			if (r > r1)
			{
				if (!sec.empty() && *(--sec.end()) > min(r,r1))
				{
					if (*sec.lower_bound(min(r,r1)) == r1) r = *(++sec.lower_bound(min(r,r1)));
					else r = *sec.lower_bound(min(r,r1));
				}else r = n;
			}else r = r1;
			ans = r - l;
			printf("%d %d\n",ans,(t > l) && (t <= r));
		}
	}
	return 0;
}
