#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;
#define MOD 1000000007ll

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

int N;
char board[2010][3];
int a[2010];
ll F[6010],inv[6010],Finv[6010];
ll dp[2010][6010],dp2[2010][6010];
ll dp_sum[2010][6010],dp2_sum[2010][6010];

ll comb(int N, int K){
	if(!(0 <= K && K <= N)) return 0;
	return F[N] * Finv[K] % MOD * Finv[N-K] % MOD;
}

ll func(int L, int R){
	int i;
	
	for(i=L;i<R;i++){
		if(board[i][0] == 'x') a[i]++;
		if(board[i][2] == 'x') a[i]++;
	}
	
	// for(i=L;i<R;i++) cout << a[i] << ' ';
	// cout << endl;
	
	dp[L+1][a[L]] = dp2[L+1][a[L]] = F[a[L]];
	if(L != 0) REP(i,a[L]+1) dp2[L+1][i] = F[a[L]];
	
	int sum = a[L] + 1;
	
	for(int x=L+1;x<R;x++){
		int sum2 = sum + a[x] + 1;
		
		REP(i,sum) dp_sum[x][i+1] = (dp_sum[x][i] + dp[x][i]) % MOD;
		for(i=sum-1;i>=0;i--) dp2_sum[x][i] = (dp2_sum[x][i+1] + dp2[x][i]) % MOD;
		
		// prev > cur
		REP(i,sum2) if(i >= a[x]) dp[x+1][i] = (dp[x+1][i] + dp2_sum[x][i-a[x]] * comb(i, a[x]) % MOD * F[a[x]]) % MOD;
		
		// prev < cur
		REP(i,sum2) if(i >= a[x]) dp[x+1][i] = (dp[x+1][i] + dp_sum[x][i-a[x]] * comb(i, a[x]) % MOD * F[a[x]]) % MOD;
		
		// prev < cur > next
		REP(i,sum2) dp2[x+1][i] = dp[x+1][i];
		REP(i,sum2) for(int big=1;big<=a[x];big++){
			int small = a[x] - big;
			if(small > i || big > sum2-1-i) continue;
			dp2[x+1][i] = (dp2[x+1][i] + dp_sum[x][i-small] * comb(i, small) % MOD * comb(sum2-1-i, big) % MOD * F[small] % MOD * F[big] % MOD * comb(big+small, big)) % MOD;
		}
		
		sum = sum2;
	}
	
	ll ans = 0;
	REP(i,sum){
		if(R == N){
			ans = (ans + dp[R][i]) % MOD;
		} else {
			ans = (ans + dp2[R][i]) % MOD;
		}
	}
	
	// cout << ans << endl;
	
	return ans;
}

int main(void){
	freopen("chessmen.in","r",stdin);
	freopen("chessmen.out","w",stdout);
	int i,j,k;
	
	inv[1] = 1;
	for(i=2;i<6010;i++) inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;
	F[0] = Finv[0] = 1;
	for(i=1;i<6010;i++){
		F[i] = F[i-1] * i % MOD;
		Finv[i] = Finv[i-1] * inv[i] % MOD;
	}
	
	cin >> N;
	REP(i,3){
		string s;
		cin >> s;
		REP(j,N) board[j][i] = s[j];
	}
	
	REP(i,N) REP(j,3) if((j == 0 || j == 2) && board[i][j] == 'x' && (i == 0 || i == N-1 || board[i-1][j] == 'x' || board[i+1][j] == 'x')){
		cout << 0 << endl;
		return 0;
	}
	
	int cnt = 0;
	REP(i,N) REP(j,3) if(board[i][j] == 'x') cnt++;
	
	vector <int> v;
	v.push_back(0);
	v.push_back(N);
	
	ll ans = 1;
	REP(i,N) if(board[i][1] == 'o'){
		v.push_back(i);
		v.push_back(i+1);
		REP(j,3) if(board[i][j] == 'x'){
			ans = ans * cnt % MOD;
			cnt--;
		}
	}
	
	sort(v.begin(),v.end());
	for(i=0;i<v.size();i+=2){
		int L = v[i], R = v[i+1];
		if(L < R){
			ans = ans * func(L, R) % MOD;
			int cnt2 = 0;
			for(j=L;j<R;j++) REP(k,3) if(board[j][k] == 'x') cnt2++;
			ans = ans * comb(cnt, cnt2) % MOD;
			cnt -= cnt2;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
