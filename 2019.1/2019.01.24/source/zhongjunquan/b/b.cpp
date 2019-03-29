#include<cstring>
#include<cstdio>
#include<algorithm>
#define fo(i,a,b) for(int i=a,___=b;i<=___;++i)
#define N 210000
using namespace std;

int fir[N],nex[N],to[N],c[N],que[N],top,h,t,n,m,f[N][2],fa[N];
int son[N][2],l2[N],l3[N],r2[N],r3[N],opl,opr,rt,opv,cnt;
#define link(x,y,v) to[++top]=y,nex[top]=fir[x],fir[x]=top,c[top]=v

void build(int &w,int h,int t){
	int m=h+t>>1;w=++cnt;l2[w]=l3[w]=n;r2[w]=r3[w]=0;
	if(h==t)return;
	build(son[w][0],h,m);build(son[w][1],m+1,t);
}
void change(int w,int h,int t){
	if(h==t){
		if(opv==2)l2[w]=r2[w]=h;else l2[w]=n,r2[w]=0;
		if(opv==3)l3[w]=r3[w]=h;else l3[w]=n,r3[w]=0;return;
	}int m=h+t>>1;
	if(opl<=m)change(son[w][0],h,m);else change(son[w][1],m+1,t);
	r2[w]=max(r2[son[w][0]],r2[son[w][1]]);
	r3[w]=max(r3[son[w][0]],r3[son[w][1]]);
	l2[w]=min(l2[son[w][0]],l2[son[w][1]]);
	l3[w]=min(l3[son[w][0]],l3[son[w][1]]);
}
int ri(int w,int h,int t){
	if(opl>opr)return 0;
	if(opl<=h&&opr>=t)return opv==2?r2[w]:r3[w];
	int m=h+t>>1,a=0,b=0;
	if(opl<=m)a=ri(son[w][0],h,m);
	if(opr>m)b=ri(son[w][1],m+1,t);
	return max(a,b);
}
int le(int w,int h,int t){
	if(opl>opr)return n;
	if(opl<=h&&opr>=t)return opv==2?l2[w]:l3[w];
	int m=h+t>>1,a=n,b=n;
	if(opl<=m)a=le(son[w][0],h,m);
	if(opr>m)b=le(son[w][1],m+1,t);
	return min(a,b);
}

bool con(int s,int t){
	if(s==t)return 1;
	if(s<t){
		opl=1,opr=t-1;opv=3;
		int a=ri(rt,1,n),b,c;
		if(a<s)return 1;
		opl=s;opr=n;opv=2;b=le(rt,1,n);opv=3;c=le(rt,1,n);
		return a<b&&a<=c;
	}
	if(s>t){
		opl=t,opr=n;opv=3;
		int a=le(rt,1,n),b,c;
		if(a>=s)return 1;
		opl=1;opr=s-1;opv=2;b=ri(rt,1,n);opv=3;c=ri(rt,1,n);
		return a>b&&a>=c;
	}
}

int main(){
	scanf("%d %d",&n,&m);
	build(rt,1,n);
	fo(i,1,n-1){
		int x,y,s;scanf("%d %d %d",&x,&y,&s);
		link(x,y,s);link(y,x,s);
		opl=i;opv=s;change(rt,1,n);
	}int ls=0;
	fo(i,1,m){
		int x,w,s,t;scanf("%d %d %d %d",&x,&w,&s,&t);
		x^=ls;w^=ls;s^=ls;t^=ls;
		if(n<=1000&&m<=1000){
			c[x+x-1]=c[x+x]=w;
			fo(j,1,n)f[j][0]=f[j][1]=0;
			for(h=0,fa[que[t=1]=s]=0,f[s][0]=f[s][1]=1;h^t;)
				for(int x=que[++h],i=fir[x],y;i;i=nex[i])if((y=to[i])!=fa[x]){
					if(c[i]==1)f[y][0]=f[x][0],f[y][1]=f[x][1];
					if(c[i]==2)f[y][0]=0,f[y][1]=f[x][1]|f[x][0];
					if(c[i]==3)f[y][0]=0,f[y][1]=f[x][0];
					fa[que[++t]=y]=x;
				}
			ls=0;
			fo(j,1,n)if(f[j][0]||f[j][1])++ls;
			printf("%d %d\n",ls,f[t][0]|f[t][1]);
		}else{
			opl=x;opv=w;change(rt,1,n);
			int L2,L3,R2,R3;
			opl=1;opr=s-1;opv=2;L2=ri(rt,1,n);opv=3;L3=ri(rt,1,n);
			opl=s;opr=n;opv=2;R2=le(rt,1,n);opv=3;R3=le(rt,1,n);
			ls=R3-L3;
			if(L2<L3)opl=1,opr=L3-1,opv=3,ls+=L3-ri(rt,1,n);
			if(R2>R3)opl=R3+1,opr=n,opv=3,ls+=le(rt,1,n)-R3;
			printf("%d %d\n",ls,con(s,t));
		}
	}
}
