#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <iomanip>
#include <fstream>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef long double db;

const int MAXN = 100005;
const int INF = (1 << 30) - 1;

int T,n,id;
int val[MAXN];
int fa[MAXN];
int ch[MAXN][2];
int cnt[MAXN];
int sz[MAXN];
int seq[MAXN];

int Alice();
int Bob();

int Alice()
{
	if (val[1] != -1)
		return val[1];
	int MAX = -INF;
	for (int i = 1;i <= n;i++)
		if (cnt[i] == 2)
		{
			cnt[i] = 0;
			cnt[fa[i]]++;
			val[i] = max(val[ch[i][0]],val[ch[i][1]]);
			MAX = max(MAX,Bob());
			val[i] = -1;
			cnt[fa[i]]--;
			cnt[i] = 2;
		}
	return MAX;
}

int Bob()
{
	if (val[1] != -1)
		return val[1];
	int MIN = INF;
	for (int i = 1;i <= n;i++)
		if (cnt[i] == 2)
		{
			cnt[i] = 0;
			cnt[fa[i]]++;
			val[i] = min(val[ch[i][0]],val[ch[i][1]]);
			MIN = min(MIN,Alice());
			val[i] = -1;
			cnt[fa[i]]--;
			cnt[i] = 2;
		}
	return MIN;
}

void dfs(int now,int lim)
{
	if (!ch[now][0] && !ch[now][1])
	{
		sz[now] = (val[now] >= lim);
		return;
	}
	dfs(ch[now][0],lim);
	dfs(ch[now][1],lim);
	sz[now] = sz[ch[now][0]] + sz[ch[now][1]];
	if (sz[ch[now][0]] < sz[ch[now][1]])
		swap(ch[now][0],ch[now][1]);
}

void getseq(int now,int lim)
{
	if (!ch[now][0] && !ch[now][1])
	{
		seq[++id] = (val[now] >= lim);
		return;
	}
	getseq(ch[now][0],lim);
	getseq(ch[now][1],lim);
}

bool ok(int lim)
{
	dfs(1,lim);
	id = 0;
	getseq(1,lim);
	if (n <= 4 && seq[1])
		return true;
	bool ok[2][4] = {0,0,0,0,0,0,0,0};
	for (int j = 0;j < 4;j++)
	{
		ok[0][j] = seq[j * (n / 4) + 1];
		ok[1][j] = true;
		for (int i = 1 + j * (n / 4);i <= n / 8 + j * (n / 4);i++)
			if (!seq[i])
				ok[1][j] = false;
	}
	if (ok[0][0] && ok[1][1])
		return true;
	if (ok[1][0] && ok[0][1])
		return true;
	if (ok[0][2] && ok[1][3])
		return true;
	if (ok[1][2] && ok[0][3])
		return true;
	return false;
}

int main()
{
	scanf("%d",&T);
	while (T--)
	{
		memset(fa,0,sizeof(fa));
		memset(ch,0,sizeof(ch));
		memset(cnt,0,sizeof(cnt));
		scanf("%d",&n);
		for (int tp,i = 1;i <= n;i++)
		{
			scanf("%d",&val[i]);
			if (val[i] == -1)
			{
				scanf("%d%d",&ch[i][0],&ch[i][1]);
				fa[ch[i][0]] = fa[ch[i][1]] = i;
			}
		}
		if (n <= 10)
		{
			for (int i = 1;i <= n;i++)
				if (val[i] != -1)
					cnt[fa[i]]++;
			printf("%d\n",Alice());
			continue;
		}
		bool tp3 = true;
		for (int i = 2;i <= n;i++)
		{
			if (i == 2)
				tp3 &= (fa[i] == 1);
			else if (i == 3)
				tp3 &= (fa[i] == 1);
			else if (i % 2 == 0)
				tp3 &= (fa[i] == i - 2);
			else if (i % 2 == 1)
				tp3 &= (fa[i] == i - 3);
		}
		if (tp3)
		{
			bool side = 0;
			val[0] = val[1];
			ch[0][0] = ch[1][0];
			ch[0][1] = ch[1][1];
			for (int i = n - 3;i >= 0;i -= 2,side ^= 1)
			{
				if (!side)
					val[i] = max(val[i + 2],val[i + 3]);
				else
					val[i] = min(val[i + 2],val[i + 3]);
			}
			printf("%d\n",val[0]);
			continue;
		}
		n = (n + 1) / 2;
		int low = 0,high = 1000000000;
		while (low < high)
		{
			int mid = (low + high + 1) >> 1;
			if (ok(mid))
				low = mid;
			else
				high = mid - 1;
		}
		printf("%d\n",low);
	}
 	return 0;
}
