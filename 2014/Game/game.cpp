#include <bits/stdc++.h>
#include "game.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;

static int ne[1501][1501];
int p[1501], n;

void initialize(int m)
{
	n=m;
	rep(i, 1, n)
	{
		p[i]=i;
		rep(j, 1, n)
			if(i!=j)ne[i][j]=1;
	}
}

void unite(int d, int s)
{
	rep(i, 1, n)
		if(p[i]==s)p[i]=d;
	rep(i, 1, n)
	{
		int t1=ne[d][i], t2=ne[s][i];
		ne[d][i]=ne[i][d]=t1+t2;
	}
}

int hasEdge(int u, int v)
{
	u++, v++;

	int p1=p[u], p2=p[v];
	if(ne[p1][p2]>1)
	{
		ne[p1][p2]--; ne[p2][p1]--;
		return 0;
	}

	ne[p1][p2]=ne[p2][p1]=0;
	unite(p1, p2);
	return 1;
}