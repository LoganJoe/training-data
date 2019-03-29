#include<bits/stdc++.h>
#define N 100005
#define db double

int n, tot, x, ans = 1;
struct node
{
	int x1, x2, y1, y2, id;
	friend bool operator <(node t1, node t2)
	{
		db k1 = 1.0*(t1.y2 - t2.y1) / (t1.x2 - t2.x1);
		db k2 = 1.0*(t2.y2 - t2.y1) / (t2.x2 - t2.x1);
		return 1.0*t1.y1 + k1 * (x - t1.x1) > 1.0*t2.y1 + k2 * (x - t2.x1);
	}
}A[N];
struct Point
{
	int type, id, x, y;
	friend bool operator <(Point t1, Point t2)
	{
		return t1.x < t2.x || t1.x == t2.x && t1.y < t2.y;
	}
}B[N<<1];

std::set<node> s;
std::set<node>::iterator it;

int main ()
{
	//freopen("hillwark.in","r",stdin);
	//freopen("hillwark.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d%d%d%d", &A[i].x1, &A[i].y1, &A[i].x2, &A[i].y2);
		A[i].id = i;
		B[++tot] = { 1,i,A[i].x1,A[i].y1 }; B[++tot] = { -1,i,A[i].x2,A[i].y2 };
	}
	std::sort (B + 1, B + 1 + tot);
	for (int i = 1, nw = 1; i <= tot; i++)
	{
		x = B[i].x;
		if (B[i].type > 0) s.insert (A[B[i].id]);
		else
		{
			if (B[i].id == nw)
			{
				it = s.upper_bound (A[B[i].id]);
				if (it == s.end ()) break;
				nw = (*it).id; ans++;
			}
			s.erase (A[B[i].id]);
		}
	}
	std::cout << ans << "\n";
	return 0;
}
/*
4
0 0 3 9
1 1 10 2
2 3 4 5
1 2 2 3
*/
