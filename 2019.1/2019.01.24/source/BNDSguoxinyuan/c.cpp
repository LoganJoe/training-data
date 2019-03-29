#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=100005;
int sc[N];
int n;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&sc[i]);
			if(i==1||((!(i&1))&&i<n-2)){
				scanf("%d",&sc[i]);
				scanf("%d",&sc[i]);
			}
		}
		int md=1;
		for(int i=n-1;i>=2;i-=2){
			if(md==1)
				sc[i-2]=max(sc[i],sc[i+1]);
			else
				sc[i-2]=min(sc[i],sc[i+1]);
		}
		printf("%d\n",sc[0]);
	}
	return 0;
}
