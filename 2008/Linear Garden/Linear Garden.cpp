#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
 
struct state {
  int lo, hi, now;
};
char S[1<<20];
state T[1<<20];
 
int main()
{
  	int N, MOD;
  	int dp[2][7][7][7] = {{{{0}}}};
	scanf("%d%d", &N, &MOD);
  	scanf("%s", S);
  
  	T[0].lo = T[0].hi = T[0].now = 3;
  	if(S[0] == 'L') T[0].lo = T[0].now = 2;
  	else T[0].hi = T[0].now = 4;
  	for(int i=1; i<N; ++i) {
    		if(S[i] == 'L') {
      			T[i].now = T[i-1].now-1;
      			T[i].lo = min(T[i-1].lo, T[i].now);
      			T[i].hi = T[i-1].hi;
    		}
    		else {
      			T[i].now = T[i-1].now+1;
      			T[i].lo = T[i-1].lo;
      			T[i].hi = max(T[i-1].hi, T[i].now);
    		}
  	}
  
  	for(int i=1; i<=3; ++i)
    		for(int j=3; j<=i+2; ++j)
      			for(int k=i; k<=j; ++k)
				dp[0][i][j][k] = 1;
  
  	int sol = 0;
  	for(int i=1; i<=N; ++i) {
    		int p = i&1, q = 1-p;
    		if(S[N-i] == 'P') {
      			int lo = min(T[N-i].lo, T[N-i].now-2);
      			int hi = i == N ? 3 : T[N-i-1].hi;
      			int now = T[N-i].now-2;
      			sol = (sol + dp[q][lo][hi][now]) % MOD;
    		}
    
    		for(int lo=1; lo<=3; ++lo) {
      			for(int hi=3; hi<=lo+2; ++hi) {
				for(int now=lo; now<=hi; ++now) {
	  				dp[p][lo][hi][now] = 0;
	  				if(now+1-lo <= 2) // P 
	    					dp[p][lo][hi][now] = (dp[p][lo][hi][now] + dp[q][lo][max(hi, now+1)][now+1]) % MOD;
	  				if(hi-now+1 <= 2)  // L
	    					dp[p][lo][hi][now] = (dp[p][lo][hi][now] + dp[q][min(lo, now-1)][hi][now-1]) % MOD;
				}
      			}
    		}
  	}
	printf("%d\n", (sol+1)%MOD);
  	return 0;
}