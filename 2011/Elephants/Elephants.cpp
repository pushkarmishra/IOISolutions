#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <cstring>
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 2e5+10, mod = 1e9+7;

int l, m, n, sqr, x[mx], id[mx], bck, test, cntr=1;
static int cnt[400][800], nxt[400][800], b[400][800], d[400];

int upb(int arr[], int s, int e, int v)
{
	while(s<=e)
	{
		int mid = (s+e)>>1;
		if(arr[mid]<=v) s=mid+1;
		else e=mid-1;
	}
	return s;
}

void build_row(int r)
{
	rep(i, 0, d[r])
		cnt[r][i]=1, nxt[r][i]=-1;

	int idx = d[r];
	for(int i=d[r]; i+1; --i)
	{
		while(b[r][idx] > b[r][i]+l)
			idx--;

		if(idx+1 <= d[r])
		{
			cnt[r][i] += cnt[r][idx+1];
			nxt[r][i] = (nxt[r][idx+1]==-1)? idx+1: nxt[r][idx+1];
		}
	}
}

void build()
{
	for(int i=0, p=-1; i<=bck and test; ++i)
		rep(j, 0, d[i])
			x[++p] = b[i][j];
	memset(d, -1, sizeof d);

	rep(i, 0, n-1)
	{
		bck = i/sqr;
		b[bck][++d[bck]]=x[i];
	}
	rep(i, 0, bck)
		build_row(i);
}

int ans()
{
	int rem = -1, ret = 0;
	rep(i, 0, bck)
	{
		int idx = upb(b[i], 0, d[i], rem);
		if(idx > d[i]) continue;

		ret += cnt[i][idx];

		if(nxt[i][idx] != -1)
			idx = nxt[i][idx];

		rem = b[i][idx]+l;
	}
	return ret;
}

void init(int N, int L, int X[])
{
	n = N, l=L; sqr = sqrt(n);
	rep(i, 0, n-1)
	{
		x[i] = X[i];
		id[i] = x[i];
	}
	build(); test=1;
}

int update(int i, int y)
{
	int idx=i, cval=id[idx], nval=y;
	id[idx] = nval; cntr++;

	rep(i, 0, bck)
	{
		if(b[i][d[i]]>=cval)
		{
			int t = upb(b[i], 0, d[i], cval-1);
			d[i]--;
			
			while(t<=d[i])
				b[i][t] = b[i][t+1], t++;
			build_row(i);
			
			break;
		}
	}

	rep(i, 0, bck)
	{
		if(b[i][d[i]] >= nval or i == bck)
		{
			b[i][++d[i]] = nval;
			
			int t=d[i];
			while(t)
			{
				if(b[i][t] <= b[i][t-1])
					swap(b[i][t], b[i][t-1]);
				--t;
			}
			build_row(i);
			
			break;
		}
	}

	if(cntr == sqr)
		build(), cntr=1;
	
	return ans();
}