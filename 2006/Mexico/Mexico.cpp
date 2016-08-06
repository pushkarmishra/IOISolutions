#include <bits/stdc++.h>
using namespace std;
const int mx=1010;
#define f first
#define s second

int n, c;
static int adm[mx][mx], ans[mx][mx][2];
pair<int, int> nx[mx][mx][2];
bool dp[mx][mx][2];

void process(int b, int e, int in, int l)
{
	if(adm[e][in] && dp[b][in][l])
		ans[b][e][l]=in, dp[b][e][l]=1,
		nx[b][e][l].f=b, nx[b][e][l].s=in;
	else if(adm[b][e] && dp[in][b][!l])
		ans[b][e][l]=b, dp[b][e][l]=1,
		nx[b][e][l].f=in, nx[b][e][l].s=b;
}

int main()
{
	cin >> c >> n;
	for(int i=1, u, v; i<=n; ++i)
	{
		cin >> u >> v; u--; v--;
		adm[u][v]=adm[v][u]=1;
	}
	
	for(int i=0; i<c; ++i)
		dp[i][i][0]=dp[i][i][1]=1;

	for(int i=1; i<c; ++i)
	{
		for(int j=0, u, v; j<c; ++j)
		{
			u=j; v=(j+i)%c;
			process(u, v, (j+i-1)%c, 1);
			u=j; v=(j-i+c)%c;
		    process(u, v, (j-i+c+1)%c, 0);
		}
	}

	int u=-1, v=-1, l=c-1, r;
	for(int i=0; i<c; ++i)
	{
		if(dp[i][(i+1)%c][0])u=i, v=(i+1)%c, r=0;
		if(dp[i][(i-1+c)%c][1])u=i, v=(i-1+c)%c, r=1;
	}
	
	if(v==-1)
	{	
		cout << "-1\n"; return 0;
	}
	cout << v+1 << endl;
	while(l)
	{
		cout << ans[u][v][r]+1 << '\n';
		int tu=nx[u][v][r].f; v=nx[u][v][r].s;
		r=(u==tu)? r: !r;
		u=tu; l--;
	}
	return 0;
}