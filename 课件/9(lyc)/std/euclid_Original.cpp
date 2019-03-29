#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,r,l) for(int i=r;i>=l;i--)
#define ll long long
#define mo 998244353
#define Pr 1000000000000000003ll
//#define EXT QAQ
namespace Matrix{
	int n;
	struct nd{
		int a[25][25];
		void read(){
			rep(i,1,n) rep(j,1,n) scanf("%d",&a[i][j]);
		}
		void print(){
			rep(i,1,n) rep(j,1,n) printf(j<n?"%d ":"%d\n",a[i][j]);
		}
	};
	nd O(){
		nd c;
		rep(i,1,n) rep(j,1,n) c.a[i][j]=0;
		return c;
	}
	nd I(){
		nd c;
		rep(i,1,n) rep(j,1,n) c.a[i][j]=(i==j);
		return c;
	}
	nd operator+(nd a,nd b){
		nd c;
		rep(i,1,n) rep(j,1,n) c.a[i][j]=(a.a[i][j]+b.a[i][j])%mo;
		return c;
	}
	nd operator*(nd a,nd b){
		nd c;
		rep(i,1,n) rep(j,1,n){
			c.a[i][j]=0;
			rep(k,1,n) c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%mo;
		}
		return c;
	}
	nd operator^(nd a,ll b){
		nd c=I();
		while(b){
			if(b&1) c=c*a;
			b>>=1;a=a*a;
		}
		return c;
	}
}
ll lmul(ll a,ll b,ll p){
	ll c=0;
	while(b){
		if(b&1) c=c+a>=p?c+a-p:c+a;
		b>>=1;a=a+a>=p?a+a-p:a+a;
	}
	return c;
}
ll lpow(ll a,ll b,ll p){
	ll c=1;
	while(b){
		if(b&1) c=lmul(c,a,p);
		b>>=1;a=lmul(a,a,p);
	}
	return c;
}
ll linv(ll a,ll p){
	return lpow(a,p-2,p);
}
ll lmud(ll a,ll b,ll c,ll p){
	ll t=(lmul(a,b,Pr)+c)%Pr-(lmul(a,b,p)+c)%p;if(t<0) t+=Pr;
	return lmul(t,linv(p,Pr),Pr);
}
ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b) return x=1,y=0,a;
	ll d=exgcd(b,a%b,y,x);
	return y-=a/b*x,d;
}
ll _f(ll P,ll Q,ll R){
	ll xx,yy;
	ll d=exgcd(P,Q,xx,yy);
	P/=d;Q/=d;R/=d;
	return lmul((xx%Q+Q)%Q,R,Q);
}
ll P,Q,R,N;
Matrix::nd A,B;
#ifdef EXT
void brute_force_generate(){
	int S=0;
	while(1){
		S+=P;
		while(S>=Q) S-=Q,putchar('1');
		putchar('0');
		if(!S) break;
	}
	std::cout<<std::endl;
}
void false_smart_generate(){
	int P_=P,Q_=Q;
	std::string S0,S1;int sign=0;
	S0="0";S1="1";
	while(P^Q){
		if(P<Q) std::swap(P,Q),std::swap(S0,S1),sign^=1;
		else while(P>Q) P-=Q,S0=S1+S0;
	}
	if(!sign) std::swap(S0,S1);
	std::cout<<S0;
	std::cout<<S1;
	std::cout<<std::endl;
	
	P=P_;Q=Q_;
}
#endif
int m;ll p[233],q[233];
struct info{
	ll len;
	#ifdef EXT
	std::string mian;
	#endif
	ll n;
	Matrix::nd s;
};
info O(){
	info a;
	a.len=0;
	#ifdef EXT
	a.mian="";
	#endif
	a.n=0;
	a.s=Matrix::O();
	return a;
}
info I0(){
	info a;
	a.len=1;
	#ifdef EXT
	a.mian="0";
	#endif
	a.n=0;
	a.s=A;
	return a;
}
info I1(){
	info a;
	a.len=1;
	#ifdef EXT
	a.mian="1";
	#endif
	a.n=1;
	a.s=Matrix::O();
	return a;
}
info operator+(info a,info b){
	#ifdef EXT
	a.mian+=b.mian;
	#endif
	a.s=a.s+(A^a.len-a.n)*b.s*(B^a.n);
	a.len+=b.len;
	a.n+=b.n;
	return a;
}
info operator-(info a,info b){
	//This is not OK
	return O();
} 
info operator*(info a,ll b){
	info o=O();
	while(b){
		if(b&1) o=o+a;
		b>>=1;a=a+a;
	}
	return o;
}
struct node{
	int p,d;ll l,l2;
	info t;
}s0[233],s1[233],S;
void maintain(node&a){
	if(a.d) a.t=s1[a.p].t*a.l+s0[a.p].t*a.l2;
	else a.t=s0[a.p].t*a.l+s1[a.p].t*a.l2;
}
void build_recursive_structure(){
	m=1;p[1]=P;q[1]=Q;
	s0[1].d=-1;s0[1].t=I0();
	s1[1].d=-1;s1[1].t=I1();
	int sign=0;
	while(p[m]^q[m]){
		if(p[m]<q[m]){
			sign^=1;
			m++;
			p[m]=q[m-1];q[m]=p[m-1];
			s0[m].p=m-1;s0[m].d=1;s0[m].l=1;s0[m].l2=0;
			s1[m].p=m-1;s1[m].d=0;s1[m].l=1;s1[m].l2=0;
		}
		else{
			m++;
			p[m]=p[m-1]%q[m-1]?p[m-1]%q[m-1]:q[m-1];q[m]=q[m-1];
			s0[m].p=m-1;s0[m].d=1;s0[m].l=p[m-1]%q[m-1]?p[m-1]/q[m-1]:p[m-1]/q[m-1]-1;s0[m].l2=1;
			s1[m].p=m-1;s1[m].d=1;s1[m].l=1;s1[m].l2=0;
		}
		maintain(s0[m]);
		maintain(s1[m]);
	}
	if(sign) S.p=m,S.d=0,S.l=1,S.l2=1;
	else S.p=m,S.d=1,S.l=1,S.l2=1;
	maintain(S);
	#ifdef EXT
	std::cout<<S.t.mian<<std::endl;
	#endif
}
info split(node a,ll L){
	if(L>a.t.len) return a.t*(L/a.t.len)+split(a,L%a.t.len);
	if(L==a.t.len) return a.t;
	if(L==0) return O();
	ll lx=a.d?s1[a.p].t.len:s0[a.p].t.len;
	if(L<=a.l*lx) return (a.d?s1[a.p].t:s0[a.p].t)*(L/lx)+split(a.d?s1[a.p]:s0[a.p],L%lx);
	return (a.d?s1[a.p].t:s0[a.p].t)*a.l+split(a.d?s0[a.p]:s1[a.p],L-a.l*lx);
}
info split1(node a,ll L,ll R){
	return split(a,R)-split(a,L-1);
}
info split2(node a,ll L,ll R){
	if(L-R==1) return O();
	assert(L<=R);
	if(R>a.t.len){
		if((L-1)/a.t.len==(R-1)/a.t.len) return split2(a,(L-1)%a.t.len+1,(R-1)%a.t.len+1);
		return split2(a,(L-1)%a.t.len+1,a.t.len)+a.t*((R-1)/a.t.len-(L-1)/a.t.len-1)+split2(a,1,(R-1)%a.t.len+1);
	}
	if(L==1&&R==a.t.len) return a.t;
	ll lx=a.d?s1[a.p].t.len:s0[a.p].t.len;
	if(R<=a.l*lx) return split2(a.d?s1[a.p]:s0[a.p],L,R);
	if(L>a.l*lx) return split2(a.d?s0[a.p]:s1[a.p],L-a.l*lx,R-a.l*lx);
	return split2(a.d?s1[a.p]:s0[a.p],L,a.l*lx)+split2(a.d?s0[a.p]:s1[a.p],1,R-a.l*lx);
}
void mainwork1(){
	Matrix::nd mul=B^R/Q;
	ll N0=_f(P,Q,R%Q),L0=lmud(N0,P,0,Q)+N0,L=lmud(N0+N,P,0,Q)+N0+N;
	info res=split1(S,L0+1,L);
	#ifdef EXT
	std::cout<<res.mian<<std::endl;
	#endif
	Matrix::nd ans=res.s*mul;
	ans.print();
}
void mainwork2(){
	Matrix::nd mul=B^R/Q;
	ll N0=_f(P,Q,R%Q),L0=lmud(N0,P,0,Q)+N0,L=lmud(N0+N,P,0,Q)+N0+N;
	info res=split2(S,L0+1,L); 
	#ifdef EXT
	std::cout<<res.mian<<std::endl;
	#endif
	Matrix::nd ans=res.s*mul;
	ans.print();
}
void brute_force_checker(){
	Matrix::nd S=Matrix::O();ll cd=R/Q,cm=R%Q;
	rep(i,1,N) cd+=(cm+P)/Q,cm=(cm+P)%Q,S=S+(A^i)*(B^cd);
	S.print();
}
int main(){
	freopen("euclid.in","r",stdin);
	freopen("euclid.out","w",stdout);
	
	scanf("%lld%lld%lld%lld%d",&P,&Q,&R,&N,&Matrix::n);
	A.read();B.read();
	#ifdef EXT
	brute_force_generate();
	false_smart_generate();
	#endif
	build_recursive_structure();
	//mainwork1();
	mainwork2();
	//brute_force_checker();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
