#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mx=1e6+10;

static int n, vis[mx],
	par[mx], cs, ce;
static ll ans=0, len, ret, dp[mx];
vector< pair<int, int> > g[mx];

void dfs(int u)
{
	vis[u]=1;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first, d=g[u][i].second;
		if(v==par[u])continue;
		if(vis[v])
		{
			ce=v, cs=u, len=d;
			continue;
		}
		par[v]=u; dp[v]=d;
		dfs(v);
	}
}
ll dist(int u)
{
	ll mo1=0, mo2=0;
	vis[u]=2;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first;
		if(vis[v]==2)continue;

		ll mo=dist(v)+g[u][i].second;
		if(mo>mo1)swap(mo, mo1);
		if(mo>mo2)swap(mo, mo2);
		ret = max(ret, mo1+mo2);
	}
	return mo1;
}

ll process(int root)
{
	ret=len=0;
	dfs(root);

	int u=ce;
	while(u!=cs)
		vis[u]=2, len+=dp[u], u=par[u];
	vis[cs]=2;

	u=ce; ll cum=0;
	ll pqp=LLONG_MIN, pqm=LLONG_MIN;
	while(u!=par[cs])
	{
		ll get=dist(u);
		ret=max(ret, pqp+len+get-cum);
		ret=max(ret, pqm+get+cum);

		pqp=max(pqp, get+cum);
		pqm=max(pqm, get-cum);

		cum+= dp[u]; u=par[u];
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	for(int u=1, v, d; u<=n; ++u)
	{
		scanf("%d %d", &v, &d);
		g[u].push_back(make_pair(v, d));
		g[v].push_back(make_pair(u, d));
	}

	for(int i=1; i<=n; ++i)
	{
		if(vis[i])continue;
		ans+= process(i);
	}
	cout << ans << '\n';
	return 0;
}
