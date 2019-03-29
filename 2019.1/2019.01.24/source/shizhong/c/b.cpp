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
	//freopen("b.in","r",stdin);
	//freopen("b.out","w",stdout);
}
void close(){
	fclose(stdin);
	fclose(stdout);
}


int m,n;
int p[NN]={};
struct edge{
	int to,xt,v;
}e[2*NN]={};
int col[NN]={};
int ecnt=2;
int ok=0;
int last_ans=0;
int ans=0;
int req=0;
void dfs(int x,int fa,int kd){
	ans++;
	if(x==req)ok=1;
	for(int pos=p[x];pos;pos=e[pos].xt){
		int cur=e[pos].to;
		if(cur==fa)continue;
		if(!kd){
			dfs(cur,x,kd|(e[pos].v>>1));
		}
		else{
			if(e[pos].v!=3){
				dfs(cur,x,kd);
			}
		}
	}
}
void add_edge(int x,int y,int val){
	e[ecnt].to=y;
	e[ecnt].v=val;
	e[ecnt].xt=p[x];
	p[x]=ecnt++;
}
void brute(){
	for(int i=1;i<=m;++i){
		int x=read(),v=read(),qx=read(),qt=read();
		x^=last_ans;
		v^=last_ans;
		qx^=last_ans;
		qt^=last_ans;
		req=qt;
		e[x<<1].v=v;
		e[x<<1|1].v=v;
		ok=0;
		ans=0;
		dfs(qx,0,0);
		last_ans=ans;
		printf("%d %d\n",last_ans,ok);
	}
}
#define ls pos<<1
#define rs pos<<1|1
bool is[4*NN][2]={};
void push_up(int pos){
	is[pos][0]=is[ls][0]&is[rs][0];
	is[pos][1]=is[ls][1]&is[rs][1];
}
void build_tree(int l,int r,int pos){
	if(l==r){
		if(col[l]==1){
			is[pos][0]=1;
			is[pos][1]=1;
		}
		else if(col[l]==2){
			is[pos][0]=0;
			is[pos][1]=1;
		}
		else{
			is[pos][0]=0;
			is[pos][1]=0;
		}
		return;
	}
	int mid=(l+r)>>1;
	build_tree(l,mid,ls);
	build_tree(mid+1,r,rs);
	push_up(pos);
}
void modify(int x,int v,int l,int r,int pos){
	if(l==r){
		if(v==1){
			is[pos][0]=1;
			is[pos][1]=1;
		}
		else if(v==2){
			is[pos][0]=0;
			is[pos][1]=1;
		}
		else{
			is[pos][0]=0;
			is[pos][1]=0;
		}
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		modify(x,v,l,mid,ls);
	}
	else modify(x,v,mid+1,r,rs);
	push_up(pos);
}
int extendr(int st,int kd,int l,int r,int pos){
	if(r<st)return r+1;
	int mid=(l+r)>>1;
	if(st<=l){
		if(is[pos][kd-1])return r+1;
		if(l==r)return l;
		bool tp=is[ls][kd-1];
		if(tp){
			return extendr(st,kd,mid+1,r,rs);
		}
		else return extendr(st,kd,l,mid,ls);
	}
	else{
		int tp=extendr(st,kd,l,mid,ls);
		if(tp!=mid+1)return tp;
		return extendr(st,kd,mid+1,r,rs);
	}
}
int extendl(int st,int kd,int l,int r,int pos){
	if(st<l)return l-1;
	int mid=(l+r)>>1;
	if(r<=st){
		if(is[pos][kd-1])return l-1;
		bool tp=is[rs][kd-1];
		if(l==r)return l;
		if(tp){
			if(is[ls][kd-1])return r;
			return extendl(st,kd,l,mid,ls);
		}
		else return extendl(st,kd,mid+1,r,rs);
	}
	else{
		int tp=extendl(st,kd,mid+1,r,rs);
		if(tp!=mid)return tp;
		return extendl(st,kd,l,mid,ls);
	}

}
void on_line(){
	build_tree(1,n,1);
	int posl,posr;
	col[n]=3;
	for(int i=1;i<=m;++i){
		int x=read(),v=read(),qx=read(),qt=read();
		x^=last_ans;
		v^=last_ans;
		qx^=last_ans;
		qt^=last_ans;
		req=qt;
		modify(x,v,1,n,1);
		ok=0;
		ans=0;
		posr=extendr(qx,1,1,n,1);
		posr+=1;
		if(posr<n){
			posr=extendr(posr,2,1,n,1);
		}
		if(posr>n)posr=n;
		posl=1;
		if(qx>1)posl=extendl(qx-1,1,1,n,1);
		if(posl>1){
			posl=extendl(posl-1,2,1,n,1)+1;
		}
		if(posl<1)posl=1;
		ans=posr-posl+1;
		ok=(req>=posl&&req<=posr);
		last_ans=ans;
		printf("%d %d\n",last_ans,ok);
	}
}
int main(){
	open();
	n=read();
	m=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read(),v=read();
		add_edge(x,y,v);
		add_edge(y,x,v);
		col[i]=v;
	}
	int last_ans=0;
	if((LL)n*m<=6000000){
		on_line();
//		brute();
	}
	else{
		on_line();
	}

	close();
	return 0;
}