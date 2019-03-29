#include<bits/stdc++.h>
#define db double
int T;
struct point
{
	db x, y;
}A, B;
db sqr (point a)
{
	return a.x*a.x + a.y*a.y;
}
bool check (point A, point B)
{
	if (A.x < B.x && A.y < B.y) return 1;
	if (sqr (A) < sqr (B)) return 0;
	db a = A.x / 2.0, b = A.y / 2.0;
	db delt1 = sqrt (sqr (B) / 4 - b * b), delt2 = sqrt (sqr (B) / 4 - a * a);
	db d1 = atan2 (delt1, b), d2 = atan2 (delt2, a);
	db d3 = atan2 (a, b) - d1 + atan2 (b, a) - d2;
	db res = atan2 (B.x, B.y) * 2;
	if (res <= d3 || (res >= std::min (d1, d2) * 2 && res <= 2 * (std::min(d1, d2) + d3)))  return 1;
	return 0;
}
int main ()
{
//	freopen("girls.in","r",stdin);
//	freopen("girls.out","w",stdout);
	for (scanf ("%d", &T); T--;)
	{
		scanf ("%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y);
		if (A.x > A.y) std::swap (A.x, A.y);
		if (B.x > B.y) std::swap (B.x, B.y);
		if (check (A, B) || check (B, A)) puts ("Yes");
		else puts ("No");
	}
}
/*
5
4 4 4 4
3 2 4 5
4 5 5 5
1 7 3 2
2 5 3 4
*/
