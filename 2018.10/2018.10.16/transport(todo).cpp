#include<bits/stdc++.h>
#define N 100005
//#define ll long long
#define ll int
int n, m, Q, pos[N];
ll now_pos, now_tim, now_arr = 1, now_ask = 1;
ll B[N]; int ans[N];
struct node
{
	int t, a, b, id;
	friend bool operator <(node t1, node t2) { return t1.t<t2.t; }
}A[N];
//three set
//set1::praise people by times(out,wait)
std::set<node> s1;
//set2::praise people by position(out,wait)
std::set<int> s2;
//set2::praise people in the machine(by arriveplace)
std::set<int> s3;
//first_block get_people in
//out::s3.erase(it)
void appear (int x)
{
	s1.insert (A[x]);
	s2.insert (A[x].a);
}
void insert_p (int x)
{
	s1.erase (A[x]);
	s2.erase (A[x].a);
	s3.insert (A[x].b);
}
void clear_people (int st, int t)
{//printf("%d\n",now_arr);
	for (int i = st; i <= n + 1; i++)
	{
		if (A[i].t>t || i>n)
			return (void)(now_arr = i);
		appear (i);
	}

}
void cal_ask (int fr, int to, int t)
{
	while (B[now_ask] <= t + abs(fr - to) + 1 && now_ask <= Q)
	{
		//sol of now_ask
		int exact = B[now_ask] - t;
		ans[now_ask] = fr>to ? fr - exact : fr + exact;
		now_ask++;
	}
}
void get_ask (int x, int t)
{
	while (B[now_ask] <= t && now_ask <= Q)
	{
		//sol of now_ask
		ans[now_ask] = x;
		now_ask++;
	}
}
void get_people ()
{
	std::set<node>::iterator it;
	it = s1.begin ();
	cal_ask (now_pos, it->a, now_tim);
	
	now_tim += abs (now_pos - it->a);
	now_pos = it->a;
	clear_people (now_arr, now_tim);
	insert_p (it->id);
}
void jump_time ()
{
	
	get_ask (now_pos, A[now_arr].t - abs (A[now_arr].a - now_pos));
	now_tim = A[now_arr].t - abs (A[now_arr].a - now_pos);
	appear (now_arr++);
	get_people ();
}
void journey_pick ()
{
	int p = *s2.begin ();
	cal_ask (now_pos, p, now_tim);
	now_tim += abs (now_pos - p);
	clear_people (now_arr, now_tim);
	now_pos = p;
	insert_p (pos[p]);
}
void journey_first ()
{
	int p = *s3.begin ();
	int st = now_tim, ed = now_tim + abs (now_pos - p);
	for (int i = now_arr; i <= n; i++)
	{
		if (A[i].t>ed)  break;
		if (A[i].a >= now_pos + A[i].t - now_tim)
		{
			clear_people (now_arr, A[i].t);
			journey_pick ();
		}
	}
	cal_ask (now_pos, p, now_tim);
	now_tim += abs (now_pos - p);
	clear_people (now_arr, now_tim);
	now_pos = p;
	s3.erase (p);
	if (!s3.empty() &&*s3.begin () == p) journey_pick ();
}
int main ()
{
	scanf ("%d%d%d", &n, &m, &Q);
	for (int i = 1; i <= n; i++) scanf ("%d%d%d", &A[i].t, &A[i].a, &A[i].b), A[i].id = i, pos[A[i].a] = i;
	for (int i = 1; i <= Q; i++) scanf ("%lld", &B[i]);
	while (now_ask <= Q)
	{
		if (s3.empty ())
			if (s1.empty ()) jump_time ();
			else get_people ();
		else
			if (s2.empty ()) journey_first ();
			else
				if (*s2.begin ()<*s3.begin () && s3.size ()<m) journey_pick ();
				else journey_first ();
	}
	for (int i = 1; i <= Q; i++) printf ("%d\n", ans[i]);
}
