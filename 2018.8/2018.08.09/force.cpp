#include <cstdio>
#include <cstring>
#include <iostream>
#include<vector>
using namespace std;



const int N = 3030;
const int M = 4545;
const int P = 2333333;
typedef long long ll;
std::vector<int>e[N];
int pre[N], low[N], bcc[N], sta[N];
int has[N], mark[N][N], id[N];
int head[N];
int ans[N][N];
int n, m, x, y, Gcnt, clc, top, Bcnt, cnt, Ans;

inline int Min(int a, int b) {
  return a < b ? a : b;
}

void dfs(int u, int fa) {
  low[u] = pre[u] = ++clc;
  int to; id[u] = cnt;
  sta[++top] = u;
  for(auto to:e[u])
    if (!mark[u][to])
	 {
      if (pre[to]) {
        if (to != fa) low[u] = Min(low[u], low[to]);
      } else if (to != fa) {
        dfs(to, u); low[u] = Min(low[u], low[to]);
      }
    }
  if (low[u] == pre[u]) {
  	printf("%d\n",Bcnt);
    Bcnt++;
    while (sta[top] != u) {
      bcc[sta[top]] = Bcnt;
      top--;
    }
    bcc[sta[top--]] = Bcnt;
  }
}
void SetBcc(int flag = 0) {
  Bcnt = cnt = clc = top = 0;
  memset(pre, 0, sizeof pre);
  memset(id, 0, sizeof id);
  for (int i = 1; i <= n; i++)
    if (!pre[i]) {
      cnt++; dfs(i, 0);
    }
  if (flag) return (void)("%%%%gjghfd%%%%");
  for (int i = 1; i <= n; i++)
    has[i] = ((ll)has[i] * M % P + bcc[i]) % P;
}

int main(void) {
  scanf("%d%d",&n,&m);
  for (int i = 1; i <= m; i++) {
    //read(x); read(y);
    scanf("%d%d",&x,&y);
    e[x].push_back(y),e[y].push_back(x);
  }
  SetBcc(1);
 
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++) {
      if (bcc[i] != bcc[j]) ans[i][j] = 1;
      if (id[i] != id[j]) ans[i][j] = -1;
    }
    for(int i=1;i<=n;i++) printf("%d ",pre[i]);
    puts("");
    for(int i=1;i<=n;i++) printf("%d ",id[i]);
    
 for (int u = 1; u <= n; u++)
		for (auto to : e[u])
		{
			mark[u][to] = mark[to][u] = 1;
			SetBcc ();
			mark[to][u] = mark[u][to] = 0;
		}
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++) {
      if (ans[i][j] != 0) continue;
      if (has[i] == has[j]) ans[i][j] = 3;
      else ans[i][j] = 2;
    }
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      if (ans[i][j] > 0) Ans += ans[i][j];
  cout << Ans << endl;
  return 0;
}
