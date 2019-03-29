#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstdlib>
#define LL long long
#define LD long double
using namespace std;
const int NN=100000 +117;
const int MM=1 +117;
int read(){
	int fl=1,x;char c;
	for(c=getchar();(c<'0'||c>'9')&&c!='-';c=getchar());
	if(c=='-'){fl=-1;c=getchar();}
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
	return x*fl;
}
void open(){
	//freopen("c.in","r",stdin);
	//freopen("c.out","w",stdout);
}
void close(){
	fclose(stdin);
	fclose(stdout);
}


int m,n;
int s[NN][2]={};
int v[NN]={};
void solve(){
	int n=read();
	for(int i=1;i<=n;++i){
		int x=read();
		v[i]=x;
		if(x<0){
			s[i][0]=read();
			s[i][1]=read();
		}
	}
	int now=1;
	for(int i=n;i>=1;--i){
		if(v[i]<0){
			if(now){
				v[i]=max(v[s[i][0]],v[s[i][1]]);
			}
			else v[i]=min(v[s[i][0]],v[s[i][1]]);
			now^=1;
		}
	}
	printf("%d\n",v[1]);
}
int main(){
	open();
	int ti=read();
	while(ti--){
		solve();
	}
	close();
	return 0;
}