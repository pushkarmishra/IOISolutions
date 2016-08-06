#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <cstring>
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 1e5+10, mod = 1e9+7;

static int dp[2][111][111], pr[111], su[111];
int r, c, h[5111][111], v[5111][111];

void build()
{
	pr[1] = h[r-1][0];
	rep(i, 1, c-1)
		pr[i+1] = pr[i]+h[r-1][i];

	su[c]=0;
	for(int i=c-1; i; --i)
		su[i] = su[i+1]+h[r-1][i-1];

	memset(dp, 0, sizeof dp);
	rep(i, 1, c) rep(j, 1, c)
		dp[1][i][j] += abs(pr[j-1]-pr[i-1]);

	for(int i = r-2; i+1; --i)
	{
		pr[1] = h[i][0];
		rep(j, 1, c-1)
			pr[j+1] = pr[j]+h[i][j];

		su[c]=0;
		for(int j=c-1; j; --j)
			su[j] = su[j+1]+h[i][j-1];

		rep(j, 1, c) rep(k, 1, c)
			dp[0][j][k] = 2e9;

		rep(k, 1, c)
		{
			int minl = dp[1][1][k]+v[i][0]-pr[0];
			rep(j, 1, c)
			{
				minl = min(minl, dp[1][j][k]+v[i][j-1]-pr[j-1]);
				dp[0][j][k] = min(dp[0][j][k], pr[j-1]+minl);
			}
		}

		rep(k, 1, c)
		{
			int minr = dp[1][c][k]+v[i][c-1]-su[c];
			for(int j=c; j; --j)
			{
				minr = min(minr, dp[1][j][k]+v[i][j-1]-su[j]);
				dp[0][j][k] = min(dp[0][j][k], su[j]+minr);
			}
		}

		memcpy(dp[1], dp[0], sizeof dp[0]);
	}
}

void init(int R, int C, int H[5000][200], int V[5000][200])
{
	r=R, c=C;
	rep(i, 0, r-1) rep(j, 0, c-2)
		h[i][j] = H[i][j];

	rep(i, 0, r-2) rep(j, 0, c-1)
		v[i][j] = V[i][j];
	
	build();
}

void changeH(int P, int Q, int W)
{
	h[P][Q]=W;
	build();
}

void changeV(int P, int Q, int W)
{
	v[P][Q]=W;
	build();
}

int escape(int V1, int V2)
{
	return dp[0][V1+1][V2+1];
}