#include<bits/stdc++.h>
#define N 200005
int n,m,typ1,typ2;
int A[N],B[N],vis[N],chrt[N],fr[N];
struct info
{
	int a,b;
}s[N<<2],t[N<<2];
bool check(int mid)
{
	for(int i=1;i<=n;i++) B[i]=A[i],vis[i]=0;
	for(int i=1;i<=mid;i++) std::swap(B[s[i].a],B[s[i].b]);
	for(int i=1;i<=n;i++) fr[B[i]]=i;
	int res=0;
	for(int i=1;i<=n;i++) if(!vis[i])
	{
		vis[i]=1;
		for(int x=fr[i];x!=i;x=fr[x]) vis[x]=1,t[++res]=(info){x,fr[x]};
	}
	for(int i=res+1;i<=mid;i++) t[i]=(info){1,1};
	return res<=mid;
}
void print(int m)
{
	for(int i=1;i<=m;i++)
	{
		if(s[i].a>s[i].b) std::swap(s[i].a,s[i].b);
		if(t[i].a>t[i].b) std::swap(t[i].a,t[i].b);
	}
	for(int i=1;i<=n;i++) chrt[i]=i;
	for(int i=m;i;i--)
	{
		for(int j=i-1;j;j--)
		{
			if(t[j].a==s[i].a) std::swap(t[j].b,s[i].b);
			if(t[j].a==s[i].b) std::swap(t[j].b,s[i].a);
			if(t[j].b==s[i].a) std::swap(t[j].a,s[i].b);
			if(t[j].b==s[i].b) std::swap(t[j].a,s[i].a);
		}
	}
	for(int i=1;i<=m;i++) printf("%d %d\n",t[i].a-1,t[i].b-1);
}
void is_right_solution(int m)
{
	for(int i=1;i<=n;i++) B[i]=A[i];
	for(int i=1;i<=m;i++) printf("%d %d\n",t[i].a,t[i].b);
	for(int i=1;i<=n;i++) printf("%d ",B[i]);puts("");
	for(int i=1;i<=m;i++)
	{
	 	std::swap(B[s[i].a],B[s[i].b]);
	 	std::swap(B[t[i].a],B[t[i].b]);
	 	for(int i=1;i<=n;i++) printf("%d ",B[i]);
	puts("");
	}
	for(int i=1;i<=n;i++) printf("%d ",B[i]);
	puts("");
	for(int i=1;i<=n;i++) if(B[i]!=i) return (void)puts("NO");
	puts("YES");
}
int main()
{
	freopen("arrange.in","r",stdin);
	freopen("arrange.out","w",stdout);
	scanf("%d%d%d",&n,&typ1,&typ2);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]),A[i]++;
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&s[i].a,&s[i].b),s[i].a++,s[i].b++;
	int l=0,r=m;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);check(l);
	if(typ1) print(l);
	//is_right_solution(l);
}
/*
6 1 1
0 3 2 5 4 1
6
0 0
0 0
0 0 
0 0 
0 0 
0 0
1 2
0 3
3 4
2 5
1 5
0 1
1 4
4 5
4 0
2 3
*/
