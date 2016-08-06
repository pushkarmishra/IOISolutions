#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;

int n;
char s[100010];
static int dp[2][4][4][4][4];

void init()
{
        for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			for(int k=0; k<4; ++k)
				for(int l=0; l<4; ++l)
	dp[0][i][j][k][l]=dp[1][i][j][k][l]=-inf;
}

int f(char t)
{
	if(t=='B')return 1;
	else if(t=='F') return 2;
	else if(t=='M') return 3;
}

int g(int a, int b, int c)
{
	a=(!a)? c: a; b=(!b)? c:b;
	if(a==b and b==c) return 1;
	if(a==b or b==c or a==c)return 2;
	return 3;
}

void copy_prev()
{
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			for(int k=0; k<4; ++k)
				for(int l=0; l<4; ++l)
	dp[0][i][j][k][l]=dp[1][i][j][k][l],
	dp[1][i][j][k][l]=-inf;
}

int main()
{
	cin >> n >> s;
	init(); dp[0][0][0][0][0]=0;

	for(int i=0; i<n; ++i)
	{
		int x=f(s[i]);
		for(int a=0; a<4; ++a)
			for(int b=0; b<4; ++b)
				for(int c=0; c<4; ++c)
					for(int d=0; d<4; ++d)
		dp[1][b][x][c][d]=max(dp[1][b][x][c][d], dp[0][a][b][c][d]+g(a, b, x)),
		dp[1][a][b][d][x]=max(dp[1][a][b][d][x], dp[0][a][b][c][d]+g(c, d, x));

		copy_prev();
	}

	int ans=INT_MIN;
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			for(int k=0; k<4; ++k)
				for(int l=0; l<4; ++l)
					ans=max(ans, dp[0][i][j][k][l]);
	
	cout << ans << '\n';
	return 0;
}
