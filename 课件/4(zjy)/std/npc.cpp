#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=head[x];i!=-1;i=ne[i])
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int,int> pin;
#define mk(a,b) make_pair(a,b)
#define lowbit(x) ((x)&(-(x)))
#define sqr(a) ((a)*(a))
#define clr(a) (memset((a),0,sizeof(a)))
#define ls(x) ((x)<<1)
#define rs(x) (((x)<<1)|1)
#define mid (((l)+(r))>>1)
#define pb push_back
#define w1 first
#define w2 second
inline void read(int &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
/*******************************head*******************************/
inline int gcd(int x,int y){
	if (y==0)return x;
	return gcd(y,x%y);
}
inline void solve(int n,int m,vector<int> &res,vector<int> &x,vector<int> &y){	
	if(n<m){
		solve(m,n,res,y,x);
		return;
	}
	if(n==1&&m==1){
		res.pb(2);
		x.pb(0);
		y.pb(1);
		return;
	}
	solve(n-m,m,res,x,y);
	int z=res[0];res[0]++;
	res.pb(x.back());res.pb(z);
	x.pb(z);
	if(y.size()>1){
		res.pb(y[y.size()-2]);res.pb(z);
	}
}
vector <int> construct(int n) {
	if(n==1)return vector<int>(1,1);
	rep(i,1,n-1)if(gcd(i,n-i)==1){
		vector<int> res,x,y;
		solve(i,n-i,res,x,y);
		if(res[0]<=50&&res.size()<=201)return res;
	}
}
inline void judge(){
	freopen("npc.in","r",stdin);
	freopen("npc.out","w",stdout);
}
int main(){
//	judge();
	int n;read(n);
	vector<int> ans=construct(n);
	printf("%d %d\n",ans[0],ans.size()/2);
	for(u32 i=1;i<ans.size();i+=2){
		printf("%d %d\n",ans[i],ans[i+1]);
	}
	return 0;
}
