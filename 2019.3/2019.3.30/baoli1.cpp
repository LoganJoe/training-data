#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using std::cin;using std::cerr;
using std::max;using std::min;
#define N 80100
#define ll long long
#define db double
#define pb push_back
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\n"
int n,A[4][N/8],Bn,f[N],ans;
std::vector<int>S[4][N/8];
struct info
{
	int id,a,b,c,d;
	friend bool operator<(info t1,info t2)
	{
		if(t1.a^t2.a) return t1.a<t2.a;
		if(t1.b^t2.b) return t1.b<t2.b;
		if(t1.c^t2.c) return t1.c<t2.c;
		return t1.d<t2.d;
	}
}B[N];
int main()
{
	freopen("lcs.in","r",stdin);
	freopen("lcs.ans","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<4;i++)
		for(int j=1;j<=n;j++) scanf("%d",&A[i][j]),S[i][A[i][j]].pb(j);
	for(int i=1;i<=n;i++)
		for(int a:S[0][i])
			for(int b:S[1][i])
				for(int c:S[2][i])
					for(int d:S[3][i]) B[++Bn]={0,a,b,c,d};
	std::sort(B+1,B+1+Bn);
	for(int i=1;i<=Bn;i++) B[i].id=i,f[i]=1;
//	for(int i=1;i<=Bn;i++) dbg1(i),dbg1(B[i].a),dbg1(B[i].b),dbg1(B[i].c),dbg2(B[i].d);
	for(int i=1;i<=Bn;i++)
	{
		for(int j=1;j<i;j++)
			if(B[j].a<B[i].a&&B[j].b<B[i].b&&B[j].c<B[i].c&&B[j].d<B[i].d)
			{
				f[i]=max(f[i],f[j]+1);
//				dbg1(j),dbg2(i);
			}
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	dbg2(ans);
	return 0;
}
