#include <bits/stdc++.h>
#include "friend.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define rf freopen("in.in", "r", stdin)
using namespace std;
const int mx=1e5+10;
static int dp[mx][2];

void process(int h, int g, int p)
{
	if(p==0)
	{
		dp[h][1] += dp[g][0];
		dp[h][0] += max(dp[g][1], dp[g][0]);
	}
	else if(p==1)
	{
		dp[h][1] = max( dp[h][1]+max(dp[g][0], dp[g][1]), dp[h][0]+dp[g][1] );
		dp[h][0] += dp[g][0];
	}
	else
	{
		dp[h][1] = max( dp[h][1]+dp[g][0], dp[h][0]+dp[g][1] );
		dp[h][0] += dp[g][0];
	}
}

int findSample(int n, int c[], int h[], int p[])
{
	rep(i, 0, n-1)
		dp[i][1]=c[i], dp[i][0]=0;

	for (int i = n-1; i > 0; --i)
		process(h[i], i, p[i]);
	
	return max(dp[0][0], dp[0][1]);
}