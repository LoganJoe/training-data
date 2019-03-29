#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define vi vector<int>
#define all(a) a.begin(),a.end()
#define pii pair<int,int> 
#define pb push_back
#define mp make_pair
#define SS second
#define FF first
#define clr(a,x) memset(a,x,sizeof(a))
#define cpy(a,x) memcpy(a,x,sizeof(a))
#define SZ(x) ((int)x.size())
using namespace std;

int n,K,w0;

const int N=2005,inf=0x3f3f3f3f;

namespace chk{
	int m,d[N];
	pii p[N];
	vi g[N];
	inline void pre(int x,int y){p[++m]=mp(x,y);}
	inline void add(int x,int y){g[x].pb(y);g[y].pb(x);}
	inline void bfs(int x){
		static int q[N];
		clr(d,0);
		int h=1,t=1;q[t]=x;
		d[x]=1;
		while(h<=t){
			int x=q[h++];
			for(int y:g[x])
				if(!d[y]) d[y]=d[x]+1,q[++t]=y;
		}
	}
	inline int get(vector<pii> &a){
		if(SZ(a)>K) return inf;
		for(int i=1;i<=n;i++) vi(0).swap(g[i]);
		for(int i=1;i<n;i++)
			add(p[i].FF,p[i].SS);
		for(auto i:a)
			add(i.FF,i.SS);
		int ans=0;
		for(int i=1;i<=n;i++){
			bfs(i);
			for(int j=1;j<i;j++)
				ans+=d[j]-1;
		}
		return ans;
	}
}

int main(int argc, char *argv[]) {
	FILE *fin = fopen(argv[1], "r");
	FILE *fout = fopen(argv[2], "r");
	FILE *score = fopen(argv[5], "w");
	FILE *msg = fopen(argv[6], "w");
	
	fscanf(fin,"%d%d%d",&n,&K,&w0);
	for(int i=1;i<n;i++){
		int x,y;fscanf(fin,"%d%d",&x,&y);
		chk::pre(x,y);
	}
	vector<pii> E(0);
	for(int i=1;i<=K;i++){
		int x,y;
		if(fscanf(fout,"%d%d",&x,&y)!=2){
			fprintf(score,"0\n");
			fclose(fin);
			fclose(fout);
			fclose(score);
			fclose(msg);return 0;
		}
		if(x<1||x>n||y<1||y>n){
			fprintf(score,"0\n");
			fclose(fin);
			fclose(fout);
			fclose(score);
			fclose(msg);return 0;
		}
		E.pb(mp(x,y));
	}
	{
		int x,y;
		if(fscanf(fout,"%d%d",&x,&y)!=EOF){
			fprintf(score,"0\n");
			fclose(fin);
			fclose(fout);
			fclose(score);
			fclose(msg);return 0;
		}
	}
	int P=(n==20?10:18),answer=chk::get(E);
	double S=1.0-(double)answer/(double)w0;
	double Score=min((double)P,(double)P*pow(50,S));
	int result=0;
	while(Score-(result+1)>-1e-3) result++;
	if (answer<=w0){
		fprintf(score, "%s\n", argv[4]);
		fprintf(msg,"w=%d,w0=%d\nscore=%.9f\n",answer,w0,(double)P);
	}else{
		fprintf(score, "%d\n",min(P-1,(int)floor(Score+0.01)));
		fprintf(msg,"w=%d,w0=%d\nscore=%.9f\n",answer,w0,Score);
	}
	fclose(fin);
	fclose(fout);
	fclose(score);
	fclose(msg);
	return 0;
}
