#include <bits/stdc++.h>
#include "wall.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;
const int mx=2e6+10;

struct node{int x, n, s;} st[4*mx];
int val, qs, qe, p;

void up(int x, int y, int n)
{
	if(y<qs || qe<x) return;
	if(qs<=x && y<=qe)
	{
		if(p==1)
		{
			if(st[n].s) st[n].n=st[n].x=max(st[n].n, val);
			else st[n].n=max(st[n].n, val), st[n].x=max(st[n].x, val);
		}
		else
		{
			if(st[n].s) st[n].x=st[n].n=min(st[n].x, val);
			else st[n].x=min(st[n].x, val), st[n].n=min(st[n].n, val);
		}
		return;
	}

	int m=(x+y)>>1;
	st[n].s=0;

	if(st[2*n].s) st[2*n].n=st[2*n].x=max(st[n].n, st[2*n].n);
	else st[2*n].n=max(st[n].n, st[2*n].n), st[2*n].x=max(st[2*n].x, st[n].n);
	if(st[2*n].s) st[2*n].x=st[2*n].n=min(st[2*n].x, st[n].x);
	else st[2*n].x=min(st[2*n].x, st[n].x), st[2*n].n=min(st[2*n].n, st[n].x);

	if(st[2*n+1].s) st[2*n+1].n=st[2*n+1].x=max(st[n].n, st[2*n+1].n);
	else st[2*n+1].n=max(st[n].n, st[2*n+1].n), st[2*n+1].x=max(st[2*n+1].x, st[n].n);
	if(st[2*n+1].s) st[2*n+1].x=st[2*n+1].n=min(st[2*n+1].x, st[n].x);
	else st[2*n+1].x=min(st[2*n+1].x, st[n].x), st[2*n+1].n=min(st[2*n+1].n, st[n].x);

	up(x, m, 2*n); up(m+1, y, 2*n+1);
	st[n].x=max(st[2*n].x, st[2*n+1].x);
	st[n].n=min(st[2*n].n, st[2*n+1].n);
}

void qu(int x, int y, int n)
{
	if(y<qs || qe<x) return;
	if(qs<=x && y<=qe)
		return void(val=st[n].x);

	int m=(x+y)>>1;

	if(st[n].s)
		return void(val=st[n].x);

	if(st[2*n].s) st[2*n].n=st[2*n].x=max(st[n].n, st[2*n].n);
	else st[2*n].n=max(st[n].n, st[2*n].n), st[2*n].x=max(st[2*n].x, st[n].n);
	if(st[2*n].s) st[2*n].x=st[2*n].n=min(st[2*n].x, st[n].x);
	else st[2*n].x=min(st[2*n].x, st[n].x), st[2*n].n=min(st[2*n].n, st[n].x);

	if(st[2*n+1].s) st[2*n+1].n=st[2*n+1].x=max(st[n].n, st[2*n+1].n);
	else st[2*n+1].n=max(st[n].n, st[2*n+1].n), st[2*n+1].x=max(st[2*n+1].x, st[n].n);
	if(st[2*n+1].s) st[2*n+1].x=st[2*n+1].n=min(st[2*n+1].x, st[n].x);
	else st[2*n+1].x=min(st[2*n+1].x, st[n].x), st[2*n+1].n=min(st[2*n+1].n, st[n].x);

	qu(x, m, 2*n); qu(m+1, y, 2*n+1);
}

void buildWall(int n, int k, int op[], int l[], int r[], int h[], int fh[])
{
	rep(i, 0, 4*mx-1)
		st[i].x=st[i].n=0, st[i].s=1;
	rep(i, 0, k-1)
	{
		qs=l[i]+1, qe=r[i]+1; p=op[i], val=h[i];
		up(1, n, 1);
	}

	rep(i, 1, n)
	{
		qs=i, qe=i; val=0;
		qu(1, n, 1);
		fh[i-1]=val;
	}
}
