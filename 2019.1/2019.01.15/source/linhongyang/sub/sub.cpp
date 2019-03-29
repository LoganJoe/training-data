#include<bits/stdc++.h>
#define N 500005
int n,A[N],cnt[N],Max,ans,mark[N];
namespace solve1
{
	int f[3005][4050];
	int solve(int x,int Xor)
	{
		int res=0;
		if(f[x][Xor]!=-1) return f[x][Xor];
		for(int i=x+1;i<=n;i++) res=std::max(res,solve(i,Xor^A[x]));
		if(!x) return res;
		if(res) res++;
		else if(Xor==A[x]) res=1;
		return f[x][Xor]=res;
	}
	void Main()
	{
		for(int i=0;i<=n;i++) 
			for(int j=0;j<=4096;j++) f[i][j]=-1;
		std::cout<<solve(0,0)<<"\n";
	}
}
namespace solve2
{
	int res;
	class Linear_Basis
	{
	public:
		int a[60],id[60];
	public:
		void insert(int v,int d)
		{
			//std::cout<<v<<"\n";
			for(int i=1;i<=n;i++) if(A[i]==v && i!=d) mark[i]=1;
			for(int i=30;~i;i--) 
			{
				if(!(v&(1<<i))) continue;
				if(a[i]) v^=a[i];
				else{a[i]=v,id[i]=d;return ;}
			}
			ans++;
		}
		void solve(int x,int tot,int Xor)
		{
			if(!a[x]) return solve(x+1,tot,Xor);
			if(x>20)
			{
				for(int i=1;i<=n;i++) if(!mark[i] && tot && (Xor^A[i])==0) {ans++;mark[i]=1;break;}
				return ;
			}
			mark[id[x]]=1;
			solve(x+1,tot+1,Xor^a[x]);
			solve(x+1,tot,Xor);
		}
	}L;
	void Main()
	{
		for(int i=1;i<=n;i++) cnt[A[i]]++;
		for(int i=1;i<=Max;i++) ans+=cnt[i]>>1;
		ans<<=1;ans+=cnt[0];
		for(int i=1;i<=n;i++) if(!(cnt[A[i]]&1) || !A[i]) mark[i]=1;
		for(int i=1;i<=n;i++) if(cnt[A[i]]&1) L.insert(A[i],i),cnt[A[i]]=0;
		L.solve(0,0,0);ans+=res;
		std::cout<<ans<<"\n";
	}
}
int main()
{
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]),Max=std::max(Max,A[i]);
	if(n<=3000 )solve1::Main();
	else solve2::Main();
}
