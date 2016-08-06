#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#include "tile.h"
using namespace std;

int idx=-1;

void divandconq(int a1, int b1, int a2, int b2, int x, int y, int tile[][6])
{
	int i=++idx;
	if(a2-a1==1 && b2-b1==1)
	{
		int p=-1;
		rep(l, a1, a2) rep(j, b1, b2)
		{
			if(l==x && j==y) continue;
			tile[i][++p]=l; tile[i][++p]=j;
		}
		return;
	}

	int mx=(a1+a2)>>1, my=(b1+b2)>>1;
	int p=-1;

	if(a1<=x && x<=mx && b1<=y && y<=my) divandconq(a1, b1, mx, my, x, y, tile);
	else {tile[i][++p]=mx; tile[i][++p]=my; divandconq(a1, b1, mx, my, mx, my, tile);}

	if(a1<=x && x<=mx && my+1<=y && y<=b2) divandconq(a1, my+1, mx, b2, x, y, tile);
	else {tile[i][++p]=mx; tile[i][++p]=my+1; divandconq(a1, my+1, mx, b2, mx, my+1, tile);}

	if(mx+1<=x && x<=a2 && b1<=y && y<=my) divandconq(mx+1, b1, a2, my, x, y, tile);
	else {tile[i][++p]=mx+1; tile[i][++p]=my; divandconq(mx+1, b1, a2, my, mx+1, my, tile);}

	if(mx+1<=x && x<=a2 && my+1<=y && y<=b2) divandconq(mx+1, my+1, a2, b2, x, y, tile);
	else {tile[i][++p]=mx+1; tile[i][++p]=my+1; divandconq(mx+1, my+1, a2, b2, mx+1, my+1, tile);}
}

void placeTile(int n, int x, int y, int tile[][6])
{
	int d=1<<n; d--;
	divandconq(0, 0, d, d, x, y, tile);
}
