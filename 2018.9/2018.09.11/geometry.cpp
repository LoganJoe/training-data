#include<bits/stdc++.h>
#define N 1005
int n,mark[N<<2],sta[N],top,ans;
struct matrix
{
	int x1,y1,x2,y2;
	friend bool operator <(matrix t1,matrix t2){return t1.x1<t2.x1;}
}A[N];
void solve1()
{
	if(A[1].x1>A[2].x1) std::swap(A[1],A[2]);
	if(A[1].x1<=A[2].x1 && A[2].x1<=A[1].x2 && A[1].y1<=A[2].y2 && A[2].y2<=A[1].y2) return (void)puts("2");
	else return (void) puts("0");
}
void solve2()
{
	std::sort(A+1,A+1+n);
	for(int i=A[1].x1;i<=A[1].x2;i++)mark[i]=A[1].y1;
	for(int i=2;i<=n;i++)
		if(A[1].x1<=A[i].x1 && A[i].x1<=A[1].x2 && A[1].y1<=A[i].y2 && A[i].y2<=A[1].y2)
			for(int j=A[i].x1;j<=std::min(A[1].x2,A[i].x2);j++) mark[j]=std::max(mark[j],A[i].y2);
	for(int i=A[1].x1;i<=A[1].x2;i++) if(mark[i]!=mark[i-1]) sta[++top]=mark[i];
	for(int i=2;i<=top;i++) 
		if(i!=top && sta[i]>sta[i-1] && sta[i]>sta[i+1]) ans++;
		else ans+=2;
	printf("%d\n",ans); 
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2);
	if(n==2) return solve1(),0;
	else return solve2(),0;
}
