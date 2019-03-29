# include <cstdlib>  
# include <cstdio>  
# include <cmath>  
# include <cstring>  

using namespace std;  

const int maxn=300000+10, maxm=900000+10, oo=1073741819;  
int top,top2,link2[maxm*3], next2[maxm*3], sum2[maxm*3],linke[maxm*3], next[maxm*3], sum[maxm*3];  
int low[maxn], dfn[maxn], w[maxn],st[maxn];  
bool step[maxn], stay[maxn];  
int id[maxn], place[maxn], pt[maxn], pe[maxn], pb[maxn],l[maxn], r[maxn];  
int n,m,A,B,tot,time;  

void link(int x, int y) {++top; next[top]=linke[x]; linke[x]=top; sum[top]=y;};  
inline int min(int x, int y) {return x<y?x:y;};  
inline int max(int x, int y) {return x>y?x:y;};  
void tarjan(int p)  
{  
  int ke=linke[p],now;low[p]=dfn[p]=++time;st[++tot]=p; step[p]=true; stay[p]=true;  
  for (;ke!= 0; ke=next[ke])  
    if (!step[sum[ke]]) tarjan(sum[ke]), low[p]=min(low[p], low[sum[ke]]);  
      else if (stay[sum[ke]]) low[p]=min(low[p], dfn[sum[ke]]);  
  if (dfn[p]==low[p])  
  {  
    for (now=st[tot];now!=p;now=st[--tot])  
      id[now]=p, w[p]+= w[now], stay[now]=false, l[p]=min(l[p],l[now]), r[p]=max(r[p],r[now]);  
    tot--; stay[now]=false;  
  }  
}  

void dfs(int p)  
{  
  int ke=link2[p]; step[p]=true;  
  for (;ke!=0; ke=next2[ke])  
  {  
    if (!step[sum2[ke]])  
      dfs(sum2[ke]), step[sum2[ke]]=true;  
    r[p]=max(r[p], r[sum2[ke]]); l[p]=min(l[p],l[sum2[ke]]);  
  }  
}  

void sort(int pt[maxn], int l, int r)  
{  
  int i=l, j=r, tmp,d=place[pt[l+r>>1]];  
  for (;i <= j;)  
  {  
    for (;place[pt[i]] < d;i++);  
    for (;place[pt[j]] > d;j--);  
    if (i <= j) tmp=pt[i],pt[i]=pt[j],pt[j]=tmp,i++,j--;  
  }  
  if (i<r) sort(pt,i,r);  
  if (l<j) sort(pt,l,j);  
}  

void linke2(int x, int y)   
{  
++top2; next2[top2]=link2[x];link2[x]=top2;sum2[top2]=y;  
};  

void dfs2(int p)  
{  
  step[p]= true;  
  for (int ke=link2[p]; ke!= 0; ke=next2[ke])   
    if (!step[sum2[ke]])dfs2(sum2[ke]);  
}  

void prepare()  
{  
  int i,x,y,z;  sort(pt,1,pt[0]); sort(pb,1,pb[0]);  
  for (i = 1; i <= m; i++)  
  {  
    scanf("%d%d%d",&x, &y, &z);  
    linke2(x,y); if (z==2) linke2(y,x);  
  }  
  for(int i=1;i<=n;i++) printf("%d\n",pb[i]);
  for (i = 1; i <= pt[0]; i++) dfs2(pt[i]);  
  for (i = 1; i <= n; i++)   
    for (int ke=link2[i]; ke!= 0; ke=next2[ke])  
      if (step[i] && step[sum2[ke]]) link(i, sum2[ke]);   
  for (i = 1; i <=pb[0]; i++)  
    if (step[pb[i]]) pe[++pe[0]] = pb[i], l[pb[i]]=r[pb[i]]=pe[0];   
	for(int i=1;i<=pe[0];i++) printf("%d %d\n",i,pe[i]);
  memset(next2, 0, sizeof(next2));  
  memset(sum2, 0, sizeof(sum2));  
  memset(link2, 0, sizeof(link2));  
  memset(step, 0, sizeof(step)); top2=0;  
}  
int main()  
{  
  int i,x,y;  
  scanf("%d%d%d%d", &n, &m, &A, &B);  
  for (i = 1; i <= n; i++)  
  {  
    scanf("%d%d", &x, &y); place[i]=y; l[i]=oo; r[i]=-oo;  
    if (x==0) pt[++pt[0]]=i; else if (x==A) pb[++pb[0]]=i;  
  }
  prepare();  
  memset(step, false, sizeof(step));  
  for (i =1; i <= n; i++) id[i]=i; 
  for (int i = 1; i <= n; i++) printf ("%d %d\n", l[i], r[i]);
  for (i = 1; i <= n; i++)  
    if (!step[i]) tarjan(i);  
  memset(step, false, sizeof(step));  
  for (i = 1; i <= n; i++)  
    for (int ke=linke[i]; ke!= 0; ke=next[ke])  
      if (id[i]!= id[sum[ke]]) linke2(id[i], id[sum[ke]]);
      	

  for (i = 1; i <= n; i++)  
    if (!step[i]) dfs(i);  
  for (i = pt[0]; i >= 1; i--)  
    if (r[id[pt[i]]] != -oo) printf("%d\n", r[id[pt[i]]]-l[id[pt[i]]]+1); else printf("0\n");  
  return 0;  
}  
