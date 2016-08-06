#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;

static int dp[610][610];
static int x[210], y[210];
int h, w, n;

int solve()
{
	rep(i, 1, h)
	{
		rep(j, 1, w)
		{
			int mw=i*j;
			rep(k, 1, n)
			{
				int a=i-x[k], b=j-y[k];
				if(a<0 || b<0) continue;

				int tmp=dp[i][b]+dp[a][y[k]];
				int tmp1=dp[a][j]+dp[x[k]][b];

				mw=min(mw, min(tmp, tmp1));
			}
			dp[i][j]=mw;
		}
	}
	return dp[h][w];
}

int main()
{
	cin >> h >> w >> n;
	rep(i, 1, n)
		cin >> x[i] >> y[i];

	cout << solve() << '\n';
	return 0;
}