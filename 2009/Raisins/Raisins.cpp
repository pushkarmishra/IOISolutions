#include <bits/stdc++.h>
using namespace std;

static int mem[52][52][52][52]={0},
		   n, m, in[52][52];

void transform()
{
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			in[i][j]+=in[i][j-1]+in[i-1][j]-in[i-1][j-1];
}
int get(int r1, int c1, int r2, int c2)
{
	return in[r2][c2]-in[r1-1][c2]-in[r2][c1-1]+in[r1-1][c1-1];
}

int solve(int r1, int c1, int r2, int c2)
{
	if(mem[r1][c1][r2][c2]!=-1)
		return mem[r1][c1][r2][c2];
	if(r2-r1==1 && c2-c1==1)
	{
		mem[r1][c1][r2][c2]=0;
		return 0;
	}

	int mx=INT_MAX;
	for(int i=r1+1; i<r2; ++i)
	{
		int tmp=solve(r1, c1, i, c2)+solve(i, c1, r2, c2);
		mx=min(mx, tmp);
	}
	for(int i=c1+1; i<c2; ++i)
	{
		int tmp=solve(r1, c1, r2, i)+solve(r1, i, r2, c2);
		mx=min(mx, tmp);
	}

	mem[r1][c1][r2][c2]=mx+get(r1, c1, r2-1, c2-1);
	return mem[r1][c1][r2][c2];
}

int main()
{
	cin >> n >> m;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			cin >> in[i][j];
	fill(&mem[0][0][0][0], &mem[51][51][51][51], -1);
	transform();

	cout << solve(1, 1, n+1, m+1) << '\n';
	return 0;
}
