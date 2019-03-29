#include<bits/stdc++.h>
#define LL long long 
#define fr(i,n) for(int i=0;i<n;i++)
using namespace std;
int m,M,x,z,i,S1,S2,SS1,SS2,l,r,W1[50505],V1[50505],W2[50505],V2[50505];
char s[9];
LL an,f1[50505][505],f2[50505][505],E[1111];
void up(LL&x,LL y){x=max(x,y);}
void bd(int k,int l,int r){
	if(l==r){E[k]=f1[S1][l-1];return;}
	int md=l+r>>1;
	bd(k<<1,l,md);bd(k<<1|1,md+1,r);
	E[k]=max(E[k<<1],E[k<<1|1]);
}
LL qu(int k,int l,int r,int x,int y){
	if(x>y)return -1e18;
	if(x<=l&&r<=y)return E[k];
	LL an=-1e18;int md=l+r>>1;
	if(x<=md)up(an,qu(k<<1,l,md,x,y));
	if(y>md)up(an,qu(k<<1|1,md+1,r,x,y));
	return an;
}
int main(){
	freopen("tanwan.in","r",stdin);
	freopen("tanwan.out","w",stdout);
	int Test;scanf("%d",&Test);
	scanf("%d%d",&m,&M);
	for(i=1;i<M;i++)f1[0][i]=f2[0][i]=-1e18;
	for(;m--;){
		scanf("%s",s);
		if(s[0]=='I'){
			scanf("%d%d",&x,&z);
			if(s[1]=='F'){//ADD FRONT 
				fr(i,M)f1[S1+1][i]=f1[S1][i];	
				fr(i,M)up(f1[S1+1][(i+x)%M],f1[S1][i]+z);
				W1[++S1]=x;V1[S1]=z;
			}else{//ADD BACK
				fr(i,M)f2[S2+1][i]=f2[S2][i];
				fr(i,M)up(f2[S2+1][(i+x)%M],f2[S2][i]+z);
				W2[++S2]=x;V2[S2]=z;
			}
		}
		if(s[0]=='D'){
			if(s[1]=='F'){//DEL FRONT
				if(!S1){
					for(i=(S2+1)/2;i;i--){
						fr(j,M)f1[S1+1][j]=f1[S1][j];
						fr(j,M)up(f1[S1+1][(j+W2[i])%M],f1[S1][j]+V2[i]);
						W1[++S1]=W2[i];V1[S1]=V2[i];
					}
					SS2=0;
					for(i=(S2+1)/2+1;i<=S2;i++){
						fr(j,M)f2[SS2+1][j]=f2[SS2][j];
						fr(j,M)up(f2[SS2+1][(j+W2[i])%M],f2[SS2][j]+V2[i]);
						W2[++SS2]=W2[i];V2[SS2]=V2[i];
					}
					S2=SS2;
				}
				S1--;
			}else{//DEL BACK
				if(!S2){
					for(i=(S1+1)/2;i;i--){
						fr(j,M)f2[S2+1][j]=f2[S2][j];
						fr(j,M)up(f2[S2+1][(j+W1[i])%M],f2[S2][j]+V1[i]);
						W2[++S2]=W1[i];V2[S2]=V1[i];
					}
					SS1=0;
					for(i=(S1+1)/2+1;i<=S1;i++){
						fr(j,M)f1[SS1+1][j]=f1[SS1][j];
						fr(j,M)up(f1[SS1+1][(j+W1[i])%M],f1[SS1][j]+V1[i]);
						W1[++SS1]=W1[i];V1[SS1]=V1[i];
					}
					S1=SS1;
				}
				S2--;
			}
		}
		if(s[0]=='Q'){//QUERY
			an=-1e18;
			scanf("%d%d",&l,&r);
			bd(1,1,M);
			fr(i,M){
				if(i>=l&&i<=r)up(an,f2[S2][i]+max(qu(1,1,M,1,r-i+1),qu(1,1,M,M-i+l+1,M)));
				else if(i>r)up(an,f2[S2][i]+qu(1,1,M,M-i+l+1,M-i+r+1));
				else up(an,f2[S2][i]+qu(1,1,M,l-i+1,r-i+1));
			}
			printf("%lld\n",an<0?-1:an);
		}
	}
} 
