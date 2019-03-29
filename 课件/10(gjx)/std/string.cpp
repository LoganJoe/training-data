#include<bits/stdc++.h>
using namespace std;
template<class T>void gi(T &x){
	int f;char c;
	for(f=1,c=getchar();c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
	for(x=0;c<='9'&&c>='0';c=getchar())x=x*10+(c&15);x*=f;
}
typedef long long ll;
const int N=1e6+10;
int n,Q,ty;char s[N];
namespace lct{
	int fa[N],ch[N][2],w[N][21],la[N][21];
	inline bool isrt(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	inline void add(int x,int y,int z){
		for(int i=1;i<=n;i++)w[x][i]+=z*w[y][i],la[x][i]+=z*w[y][i];
	}
	inline void rotate(int x){
		int y=fa[x];bool t=ch[y][1]==x;
		ch[y][t]=ch[x][!t];fa[ch[y][t]]=y;
		ch[x][!t]=y;fa[x]=fa[y];
		if(!isrt(y))ch[fa[y]][ch[fa[y]][1]==y]=x;
		fa[y]=x;
	}
	inline void pushdown(int x){
		int l=ch[x][0],r=ch[x][1];
		for(int i=1;i<=n;i++){
			if(l)w[l][i]+=la[x][i],la[l][i]+=la[x][i];
			if(r)w[r][i]+=la[x][i],la[r][i]+=la[x][i];la[x][i]=0;
		}
	}
	inline void Push(int x){if(!isrt(x))Push(fa[x]);pushdown(x);}
	inline void splay(int x){
		Push(x);
		while(!isrt(x)){
			int y=fa[x],p=fa[y];
			if(isrt(y))rotate(x);
			else if((ch[p][0]==y)==(ch[y][0]==x))rotate(y),rotate(x);
			else rotate(x),rotate(x);
		}
	}
	inline void access(int x){
		int y=0;
		while(x)splay(x),ch[x][1]=y,x=fa[y=x];
	}
	inline void link(int x,int y){
		fa[x]=y;splay(x);access(y);splay(y);add(y,x,1);
	}
	inline void cut(int x){
		access(x);splay(x);add(ch[x][0],x,-1);ch[x][0]=fa[ch[x][0]]=0;
	}
	inline int qry(int x,int y){splay(x);return w[x][y];}
}
int fa[N],ch[N][10],len[N],cur=1,cnt=1,pos[N][21];ll sum=0;
inline int ins(int p,int id,int c){
	if(ch[p][c] && len[ch[p][c]]==len[p]+1){
		int q=ch[p][c];
		lct::access(q);lct::splay(q);lct::w[q][id]++;lct::la[q][id]++;
		return q;
	}
	len[cur=++cnt]=len[p]+1;lct::w[cur][id]=1;
	for(;p && !ch[p][c];p=fa[p])ch[p][c]=cur;
	if(!p)fa[cur]=1,lct::link(cur,1);
	else{
		int q=ch[p][c];
		if(len[p]+1==len[q])fa[cur]=q,lct::link(cur,q);
		else{
			if(len[p]+1==len[cur]){
				lct::cut(q);lct::link(cur,fa[q]);lct::link(q,cur);
				memcpy(ch[cur],ch[q],sizeof(ch[q]));
				fa[cur]=fa[q];fa[q]=cur;
				sum-=len[cur]-len[fa[cur]];
				for(;p && ch[p][c]==q;p=fa[p])ch[p][c]=cur;
			}
			else{
				int nt=++cnt;len[nt]=len[p]+1;
				memcpy(ch[nt],ch[q],sizeof(ch[q]));
			  lct::cut(q);lct::link(nt,fa[q]);lct::link(q,nt);lct::link(cur,nt);
				fa[nt]=fa[q];fa[q]=fa[cur]=nt;
				for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=nt;
			}
		}
	}
	sum+=len[cur]-len[fa[cur]];
	return cur;
}
inline int work(){
	int x=1,ret=0;
	scanf("%s",s+1);
	for(int i=1,le=strlen(s+1);i<=le;i++){
		int c=s[i]-'0';
		if(ch[x][c])x=ch[x][c];
		else return 0;
	}
	lct::splay(x);
	for(int i=1;i<=n;i++)ret=max(ret,lct::w[x][i]);
	return ret;
}
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	cin>>n>>ty;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);pos[0][i]=1;
		for(int j=1,le=strlen(s+1);j<=le;j++)
			pos[0][i]=ins(pos[0][i],i,s[j]-'0');
	}
	cin>>Q;
	int op,x,y,z,ans=0;
	for(int i=1;i<=Q;i++){
		gi(op);
		if(op<=2)gi(x),gi(y);
		for(int j=1;j<=n;j++)pos[i][j]=pos[i-1][j];
		if(op==1)y=(y^(ans*ty))%10,pos[i][x]=ins(pos[i][x],x,y);
		else if(op==2)gi(z),printf("%d\n",ans=lct::qry(pos[y][x],z));
		else if(op==3)printf("%lld\n",sum);
		else printf("%d\n",ans=work());
	}
	return 0;
}
