#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<assert.h>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<bitset>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

template<typename T>inline void upmin(T &x,T y) { y<x?x=y:0; }
template<typename T>inline void upmax(T &x,T y) { x<y?x=y:0; }

typedef unsigned int u32;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double lod;
typedef pair<int,int> PR;
typedef vector<int> VI;

const lod pi=acos(-1);
const int oo=1<<30;
const LL OO=1e18;

const int N=3e5+100,M=1e6+100;
const int mod=1e9+7;

int gi() {
	int w=0;bool q=1;char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}

#define lc (i<<1)
#define rc (lc|1)
int mx[N*4];
void modify(int i,int l,int r,int k,int t) {
	upmax(mx[i],t);
	if (l!=r) {
		int mid=(l+r)>>1;
		k<=mid?modify(lc,l,mid,k,t):modify(rc,mid+1,r,k,t);
	}
}
int query(int i,int l,int r,int L,int R) {
	if (L<=l&&r<=R) return mx[i];
	else {
		int mid=(l+r)>>1,ret=0;
		if (L<=mid) upmax(ret,query(lc,l,mid,L,R));
		if (mid<R) upmax(ret,query(rc,mid+1,r,L,R));
		return ret;
	}
}
#undef lc
#undef rc

char s[N];
int son[N][26],len[N],fail[N],dif[N],anc[N],tot,last;
int head[N],nxt[N];
int c[N];
int L[N],R[N],cnt,n;
int cur[M],go[M],le[M];
int getfail(int k,int n) {
	while (s[n]!=s[n-len[k]-1])
		k=fail[k];
	return k;
}
int add(int p,int n) {
	p=getfail(p,n);
	if (!son[p][s[n]-'a']) {
		len[++tot]=len[p]+2;
		fail[tot]=son[getfail(fail[p],n)][s[n]-'a'];
		son[p][s[n]-'a']=tot;
		dif[tot]=len[tot]-len[fail[tot]];
		anc[tot]=dif[tot]==dif[fail[tot]]?anc[fail[tot]]:tot;
	}
	return son[p][s[n]-'a'];
}
void dfs(int k) {
	L[k]=++cnt;
	for (int i=head[k];~i;i=nxt[i]) dfs(i);
	R[k]=cnt;
}
int ans[M];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	int n=gi(),Q=gi(),i,k,t;
	assert(1<=n&&n<=300000);
	assert(1<=Q&&Q<=1000000);
	last=tot=1;len[1]=-1;fail[0]=1;
	scanf("%s",s+1);assert(strlen(s+1)==n);
	s[0]='#';s[n+1]='@';
	for (i=1;i<=n;i++)
		assert('a'<=s[i]&&s[i]<='z'),last=add(last,i);
	for (i=0;i<=tot;i++) head[i]=-1;
	for (i=0;i<=tot;i++)
		if (i!=1) nxt[i]=head[fail[i]],head[fail[i]]=i;
	dfs(1);
	for (i=1;i<=Q;i++) { 
		le[i]=gi(),go[i]=cur[k=gi()],cur[k]=i;
		assert(1<=le[i]&&le[i]<=k&&k<=n);
	}
	for (i=1,last=1;i<=n;i++) {
		last=son[getfail(last,i)][s[i]-'a'];
		for (k=last;k;k=fail[anc[k]]) {
			for (t=max(1,query(1,1,cnt,L[k],R[k])-len[k]+2);t<=n;t+=t&-t) ++c[t];
			for (t=i-len[anc[k]]+1 +1;t<=n;t+=t&-t) --c[t];
		}
		modify(1,1,cnt,L[last],i);
		for (k=cur[i];k;k=go[k])
			for (t=le[k];t;t^=t&-t)
				ans[k]+=c[t];
	}
	int ret=0;
	for (i=1;i<=Q;i++)
		ret=(ret+1LL*i*ans[i])%mod;
	cout<<ret<<endl;
	return 0;
}
