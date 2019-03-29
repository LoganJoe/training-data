#include <bits/stdc++.h>
#define N 102
#define P 1000000007
using namespace std;
int n,R,G,B,f[N][N][N],g[N][N][N],m,fac[N],inv[N],re;
void F(int &a,int b) {a+=b;a>=P?a-=P:0;}
int po(int a,int b) {
    int t=1;
    for (;b;b>>=1,a=1LL*a*a%P)
        if (b&1) t=1LL*t*a%P;
    return t;
}
int calc(int n,int a,int b)  {
    return n<a+b?0:1LL*fac[n]*inv[a]%P*inv[b]%P*inv[n-a-b]%P;}
int main() {
    cin>>n>>R>>G>>B;
    if (R>G) swap(R,G);
    if (R>B) swap(R,B);
    if (G>B) swap(G,B);
    m=R+G+B;
    f[0][0][0]=g[0][0][0]=fac[0]=inv[0]=1;
    for (int i=1;i<=m;i++)
        inv[i]=po(fac[i]=1LL*fac[i-1]*i%P,P-2);
    for (int i=0;i<n;i++)
        for (int k=0;k<=B;k++)
            for (int c=0;c<=m;c++)
                for (int j=0;j<=B&&c+j<=m;j++)
                    F(f[i+1][max(k,j)][c+j],f[i][k][c]);
                    printf("%d %d\n",B,m);

    for (int i=1;i<=n;i++)
        for (int c=0;c<=m;c++) {
            for (int j=0;c+j<=m;j++)
                for (int p=0;p<=B;p++)
                    for (int q=0;p+q<=B;q++)
                        F(g[i][p+q][c+j],1LL*g[i-1][p][c]*f[n][q][j]%P);
        }
        for (int i = 0; i <= B; i++)
		for (int j = 0; j <= m; j++) printf ("%d\n", g[n][i][j]);
    for (int i=1;i<=R;i++)
        re=(re+1LL*g[n][i][m]*calc(m-i,B,G))%P;
    for (int i=1;i<=B;i++)
        re=(re+1LL*g[n][i][m]*calc(m-i,G,R))%P;
    for (int i=1;i<=G;i++)
        re=(re+1LL*g[n][i][m]*calc(m-i,R,B))%P;
    return cout<<re<<endl,0;
}
