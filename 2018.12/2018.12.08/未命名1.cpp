#include<bits/stdc++.h>
#define N 100005
int n, A[N], ans, sum;
struct node
{
	int x, v;
	friend bool operator <(node t1, node t2)
	{
		return t1.v > t2.v;
	}
};
std::priority_queue<node> q;
int main() 
{
	freopen("elasticity.in","r",stdin);
	freopen("elasticity.out","w",stdout);
	while(scanf("%d",&n), n)
	{
		ans = sum = 0;
		for (int i = 1; i <= n; i++) scanf("%d", &A[i]), sum += A[i];
		if(sum < 0) 
		{
			puts("-1");
			continue;
		}
		for (int i = 1; i <= n; i++) if(A[i] < 0) q.push({i, A[i]});
		while(!q.empty())
		{
			node u = q.top(); q.pop();
			if(A[u.x] != u.v) continue;
			int l = u.x == 1 ? n : u.x - 1, r = u.x == n ? 1 : u.x + 1;
			A[l] += A[u.x], A[r] += A[u.x], A[u.x] = -A[u.x];
			if(A[l] < 0) q.push({l, A[l]});
			if(A[r] < 0) q.push({r, A[r]});
			ans++;
 		}
 		std::cout << ans << "\n";
	}
}


