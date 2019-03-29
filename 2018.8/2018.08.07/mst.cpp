#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<queue>
#include<iomanip>
#define ll long long
using namespace std;
const int inf=1000000000;
template <typename T>
inline void _read(T& x){
    char t=getchar();bool sign=true;
    while(t<'0'||t>'9'){if(t=='-')sign=false;t=getchar();}
    for(x=0;t>='0'&&t<='9';t=getchar())x=x*10+t-'0';
    if(!sign)x=-x;
}
int n,m;
int cnt[1<<11],Set[15];
ll c[55][55],f[1<<11][55],g[1<<11][55];
int bitcnt(int x){
	int temp=0;
	while(x){
		temp++;
		x-=x&(-x);
	}
	return temp;
}
int main(){
	int i,j,k,s,s1;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		int x,y;
		_read(x);_read(y);
		x--;y--;
		Set[x]|=(1<<y);
		Set[y]|=(1<<x);
	}
	for(i=0;i<=m;i++){
		for(j=0;j<=i;j++){
			if(j==0)c[i][j]=1;
			else c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
	}
	int all=(1<<n)-1;
	for(s=1;s<=all;s++){
		int size=bitcnt(s);
		if(size==1){
			g[s][0]=1;
			continue;
		}
		for(i=0;i<n;i++){
			if(s&(1<<i)){
				cnt[s]+=bitcnt(Set[i]&s);
			}
		}
		cnt[s]>>=1;
		int p=s&(-s);
		for(s1=(s-1)&s;s1;s1=(s1-1)&s){
			if(s1&p){
				for(i=0;i<=cnt[s1];i++){
					for(j=0;j<=cnt[s-s1];j++){
						f[s][i+j]+=g[s1][i]*c[cnt[s-s1]][j];
					}
				}
			}
		}
		for(i=0;i<=cnt[s];i++){
			g[s][i]=c[cnt[s]][i]-f[s][i];
		}
	}
	double ans=0.0;
	for(i=0;i<=m;i++){
		ans+=(double)f[all][i]/(double)c[cnt[all]][i];
	}
	printf("%.8lf\n",ans);
	ans/=double(m+1);
	cout<<fixed<<setprecision(6)<<ans;
}

