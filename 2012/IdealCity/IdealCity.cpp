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
const int mx = 1e5+10, mod = 1e9;
#define ff first
#define ss second

pair<int, int> sx[mx], sy[mx];
vector<int> g[mx];
map< int, pair<int, int> > mp;
set< pair<int, int> > chk;

int n, ans=0;
int ch[mx], len[mx], sz[mx];

void process(pair<int, int> a[], int i, int &node)
{
	if(mp[a[i].ss].ff==a[i].ff-1 and mp[a[i].ss].ff!=0)
	{
		sz[mp[a[i].ss].ss]++;
		mp[a[i].ss].ff = a[i].ff;
	}
	else
	{
		++node;
		mp[a[i].ss] = make_pair(a[i].ff, node);
		sz[mp[a[i].ss].ss]++;
	}

	if(a[i].ff == a[i-1].ff and a[i-1].ss == a[i].ss-1)
	{
		int u = mp[a[i].ss].ss, v = mp[a[i-1].ss].ss;

		if(chk.find(make_pair(u, v)) == chk.end())
		{
			chk.insert(make_pair(u, v));
			chk.insert(make_pair(v, u));

			g[u].push_back(v); g[v].push_back(u);
		}
	}
}
void fg(pair<int, int> a[])
{
	rep(i, 0, mx-1)
		g[i].clear();
	mp.clear(); chk.clear();

	int node = 0, i=1;
	while(i<=n)
	{
		while(a[i+1].ff == a[i].ff and i<=n)
			process(a, i, node),
			i++;

		process(a, i, node);
		i++;
	}
}

void calculate(int u, int p)
{
	ch[u]=sz[u];
	rep(i, 0, g[u].size()-1)
	{
		int v = g[u][i];
		if(v==p) continue;

		calculate(v, u);

		ans += (1ll*len[u]*ch[v])%mod; ans %= mod;
		ans += (1ll*len[v]*ch[u])%mod; ans %= mod;
		
		ch[u] += ch[v]; ch[u] %= mod;
		len[u] += len[v]; len[u] %= mod;
	}
	len[u] += ch[u]; len[u] %= mod;
}

int DistanceSum(int N, int *X, int *Y)
{
	n=N;
	rep(i, 1, n)
	{
		int x=X[i-1], y=Y[i-1];

		sx[i] = make_pair(x, y);
		sy[i] = make_pair(y, x);
	}
	sort(sx+1, sx+n+1); sort(sy+1, sy+n+1);

	fg(sy); calculate(1, -1);
	rep(i, 0, mx-1)
		ch[i] = len[i] = sz[i] = 0;
	fg(sx); calculate(1, -1);

	return ans;
}