#include <bits/stdc++.h>
#include "square.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;
const int mx=1010;

static int b[mx][mx];
int n, in, cnt=0;

void transfrm()
{
	rep(i, 1, n) rep(j, 1, n)
		b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
}

int get(int a1, int b1, int a2, int b2)
{
	return b[a2][b2]-b[a1][b2]-b[a2][b1]+b[a1][b1];
}

int chk(int si)
{
	cnt=0;
	rep(i, si, n) rep(j, si, n)
		if(!get(i-si, j-si, i, j)) cnt++;
	return cnt;
}

int findMaxSquare(int material[SIZE][SIZE], int	materialSize)
{
	n=materialSize;
	rep(i, 1, n)
		rep(j, 1, n)
			b[i][j]+= (!material[i-1][j-1]);
	transfrm();

	int s=0, e=mx;
	while(s<=e)
	{
		int m=(s+e)>>1;
		if(chk(m))s=m+1;
		else e=m-1;
	}

	return chk(e)*e;
}
