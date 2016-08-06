#include <bits/stdc++.h>
#include "station.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;
const int mx=5e5+10;
const int inf=1e9;

static int st[mx*5];
int n, qs, qe, in[mx], val, k;

void up(int x, int y, int r)
{
	if(y<qs || qe<x)return;
	if(qs<=x && y<=qe)
		return void(st[r]=val);
	int mid=(x+y)>>1;
	up(x, mid, 2*r); up(mid+1, y, 2*r+1);
	st[r]=min(st[2*r], st[2*r+1]);
}
int qu(int x, int y, int r)
{
	if(y<qs || qe<x)return inf;
	if(qs<=x && y<=qe)
		return st[r];
	int mid=(x+y)>>1;
	return min(qu(x, mid, 2*r), qu(mid+1, y, 2*r+1));
}

int findMinDays(int N, int K, int lodge[])
{
	n=N, k=K;
	rep(i, 1, n) in[i]=lodge[i-1];
	in[1]=in[n]=1;
	rep(i, 0, 5*mx-1) st[i]=inf;

	val=0; qs=qe=1;
	up(1, n, 1);

	rep(i, 2, n)
	{
		if(in[i])
		{
			qs=max(1, i-k), qe=i;
			val=qu(1, n, 1)+1;
			qs=qe=i;
			up(1, n, 1);
		}
	}
	return (val<inf)? val: -1;
}
