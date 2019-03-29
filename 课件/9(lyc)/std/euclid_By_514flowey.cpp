#include<bits/stdc++.h>
using namespace std;
const long long md=998244353;
int N;
struct Matrix{
	long long a[20][20];
	void readl(){
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				scanf("%lld",&a[i][j]);
	}
	void operator = (const long long &x){
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				a[i][j]=0;
		for(int i=0;i<N;i++)
			a[i][i]=x;
	}
};
void print(const Matrix &A){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			printf("%lld ",A.a[i][j]);
		printf("\n");
	}
}
Matrix operator * (const Matrix &A,const Matrix &B){
	Matrix res;
	res=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++){
			for(int k=0;k<N;k++)
				res.a[i][j]+=A.a[i][k]*B.a[k][j]%md;
			res.a[i][j]%=md;
		}
	return res;
}
Matrix operator + (const Matrix &A,const Matrix &B){
	Matrix res;
	res=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			res.a[i][j]=(A.a[i][j]+B.a[i][j])%md;
	return res;
}
Matrix Matrix_powd(Matrix x,long long y){
	Matrix res;
	res=1;
	while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
Matrix BaseA,BaseB;
struct Segment{
	long long cnt0,cnt1;
	Matrix v;
};
void sprint(const Segment &A){
	print(A.v);
	printf("(0*%lld+1*%lld)\n",A.cnt0,A.cnt1);
}
Segment Segment_empty(){
	Matrix v;
	v=0;
	return (Segment){0,0,v};
}
Segment Segment_1(){
	Matrix v;
	v=BaseA;
	return (Segment){0,1,v};
}
Segment Segment_0(){
	Matrix v;
	v=0;
	return (Segment){1,0,v};
}
Segment operator + (const Segment &A,const Segment &B){
	Segment res;
	res.cnt0=A.cnt0+B.cnt0,res.cnt1=A.cnt1+B.cnt1;
	res.v=A.v+Matrix_powd(BaseA,A.cnt1)*B.v*Matrix_powd(BaseB,A.cnt0);
	return res;
}
Segment operator * (const Segment &A,const long long &y){
	Segment res,x=A;
	long long yy=y;
	res=Segment_empty();
	while(yy){
		if(yy&1) res=res+x;
		x=(x+x);
		yy>>=1;
	}
	return res;
}
struct node{
	long long cnt0,cnt1;
	Segment s;
}val[2][1000];
long long get_len(const node &A){
	return A.s.cnt1;
}
long long p[1000],q[1000];
int num,cnt_rev;
void Build_string(long long P,long long Q){
	p[0]=P,q[0]=Q;
	val[0][0].s=Segment_0();
	val[1][0].s=Segment_1();
	while(1){
		if(p[num]%q[num]==0){
			if(q[num]!=1){
				fprintf(stderr,"gcd is wrong!\n");
				exit(-1);
			}
			num++;
			p[num]=1,q[num]=1;

			val[0][num].cnt0=1,val[0][num].cnt1=0;
			val[1][num].cnt0=p[num-1]-1,val[1][num].cnt1=1;
			
			val[0][num].s=val[0][num-1].s;
			val[1][num].s=val[0][num-1].s*val[1][num].cnt0+val[1][num-1].s;
			break;
		}
		if(p[num]<q[num]){
			num++,cnt_rev^=1;
			p[num]=q[num-1],q[num]=p[num-1];

			val[0][num].cnt0=0,val[0][num].cnt1=1;
			val[1][num].cnt0=1,val[1][num].cnt1=0;

			val[0][num].s=val[1][num-1].s;
			val[1][num].s=val[0][num-1].s;
		}
		else{
			num++;
			p[num]=p[num-1]%q[num-1],q[num]=q[num-1];

			val[0][num].cnt0=1,val[0][num].cnt1=0;
			val[1][num].cnt0=p[num-1]/q[num-1],val[1][num].cnt1=1;

			val[0][num].s=val[0][num-1].s;
			val[1][num].s=val[0][num-1].s*val[1][num].cnt0+val[1][num-1].s;
		}
	}
	num++;
	val[0][num].cnt0=1,val[0][num].cnt1=1;
	if(!cnt_rev)
		val[0][num].s=val[0][num-1].s+val[1][num-1].s;
	else
		val[0][num].s=val[1][num-1].s+val[0][num-1].s;
}
Segment solver(int p_dep,long long r,int id){
	if(r<=0||r>get_len(val[id][p_dep])){
		printf("wrong r!\n");
		exit(-1);
	}
	if(p_dep==0){
		if(id==1) return Segment_1();
		return Segment_0();
	}
	long long len=get_len(val[0][p_dep-1]),pos=len*val[id][p_dep].cnt0;
	if(r>pos) return val[0][p_dep-1].s*val[id][p_dep].cnt0+solver(p_dep-1,r-pos,1);
	else
		return val[0][p_dep-1].s*((r-1)/len)+solver(p_dep-1,(r-1)%len+1,0);
}
Segment solvel(int p_dep,long long l,int id){
	if(l<=0||l>get_len(val[id][p_dep])){
		printf("wrong l!\n");
		exit(-1);
	}
	if(p_dep==0)
		return Segment_empty();
	long long len=get_len(val[0][p_dep-1]),pos=len*val[id][p_dep].cnt0;
	if(l>pos)
		return solvel(p_dep-1,l-pos,1);
	else
		return solvel(p_dep-1,(l-1)%len+1,0)+val[0][p_dep-1].s*(val[id][p_dep].cnt0-((l-1)/len+1))+val[1][p_dep-1].s*val[id][p_dep].cnt1;
}
Segment solve(int p_dep,long long l,long long r,int id){
	if(r<=0||r>get_len(val[id][p_dep])){
		printf("wrong r!\n");
		exit(-1);
	}
	if(l<=0||l>get_len(val[id][p_dep])){
		printf("wrong l!\n");
		exit(-1);
	}
	if(p_dep==0)
		return Segment_empty();
	long long len=get_len(val[0][p_dep-1]),pos=len*val[id][p_dep].cnt0;
	if(l>pos) return solve(p_dep-1,l-pos,r-pos,1);
	else{
		if((r-1)/len==(l-1)/len) return solve(p_dep-1,(l-1)%len+1,(r-1)%len+1,0);
		else if(r<=pos)
			return solvel(p_dep-1,(l-1)%len+1,0)+val[0][p_dep-1].s*((r-1)/len-((l-1)/len+1))+solver(p_dep-1,(r-1)%len+1,0);
		else
			return solvel(p_dep-1,(l-1)%len+1,0)+val[0][p_dep-1].s*(val[id][p_dep].cnt0-((l-1)/len+1))+solver(p_dep-1,r-pos,1);
	}
}
Segment solve(long long l,long long r){
	long long len=get_len(val[0][num]);
	long long cnt=r/len;
	Segment res,vl,vr;
	if(l==0)
		vl=Segment_empty();
	else{
		long long p1=get_len(val[cnt_rev][num-1]),p2=l/len*len+len;
		if(r<=p1) return solve(num-1,l,r,cnt_rev);
		else if(r<=p2){
			if(l<=p1){
				return solvel(num-1,l,cnt_rev)+solver(num-1,r-p1,cnt_rev^1);
			}
			else
				return solve(num-1,l-p1,r-p1,cnt_rev^1);
		}
		else{
			if(l<=p1) vl=solvel(num-1,l,cnt_rev)+val[cnt_rev^1][num-1].s;
			else vl=solvel(num-1,l-p1,cnt_rev^1);
		}
		cnt--;
	}
	res=val[0][num].s*cnt;
	r%=len;
	if(r==0)
		vr=Segment_empty();
	else{
		long long pos=get_len(val[cnt_rev][num-1]);
		if(r<=pos) vr=solver(num-1,r,cnt_rev);
		else vr=val[cnt_rev][num-1].s+solver(num-1,r-pos,cnt_rev^1);
	}
	return vl+res+vr;
}
void exgcd(long long a,long long b,long long &x,long long &y){
	if(b==0){
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y=(y-(a/b)*x);
}
long long get_inv(long long x,long long y){
	long long xx,yy;
	exgcd(x,y,xx,yy);
	return (xx%y+y)%y;
}
long long Mult(long long x,long long y,long long p_mod){
	long long res=0;
	while(y){
		if(y&1) res=(res+x)%p_mod;
		x=(x+x)%p_mod;
		y>>=1;
	}
	return res;
}
Matrix get_ans(long long P,long long Q,long long R,long long L){
	Matrix res=Matrix_powd(BaseB,R/Q);
	R%=Q;
	long long x=Mult(R,get_inv(P,Q),Q);
	Segment st;
	st=solve(x,x+L);
	return res*st.v;
}
int main(){
	freopen("euclid.in","r",stdin);
	freopen("euclid.out","w",stdout);
	long long P,Q,R,L;
	scanf("%lld%lld%lld%lld%d",&P,&Q,&R,&L,&N);
	BaseA.readl(),BaseB.readl();
	long long d=__gcd(P,Q);
	R-=R%d;
	P/=d,Q/=d,R/=d;
	Build_string(P,Q);
	Matrix ans=get_ans(P,Q,R,L);
	print(ans);
	return 0;
}
