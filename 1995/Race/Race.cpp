#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;

vector<int> g[1010], cr, sp;
int l[1010], vis[1010], crit[1010];
int n=0, in;

void dfs(int u)
{
	vis[u]=1;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i];
		if(!vis[v]) dfs(v);
	}
}

int det_spl(int u)
{
	vis[u]=1;
	int minl=l[u];

	for(int i=0; i<g[u].size(); ++i)
		l[g[u][i]]=min(l[u]+1, l[g[u][i]]);
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i];
		minl=min(minl, l[v]);
		if(!vis[v])
			minl=min(minl, det_spl(v));
	}

	if(minl>=l[u] && crit[u] && u!=1 && u!=n)
		sp.push_back(u);
	return minl;
}

int main()
{
	while(1)
	{
		++n; l[n]=1010;
		cin >> in;
		while(in>=0)
		{
			g[n].push_back(in+1);
			cin >> in;
		}
		if(in==-1) break;
	}

	for(int i=2; i<n; ++i)
	{
		memset(vis, 0, sizeof vis);
		vis[i]=1;
		dfs(1);
		if(!vis[n]) cr.push_back(i), crit[i]=1;
	}

	memset(vis, 0, sizeof vis); l[1]=0;
	det_spl(1);

	sort(cr.begin(), cr.end()); sort(sp.begin(), sp.end());

	cout << cr.size() << ' ';
	for(int i=0; i<cr.size(); ++i)cout << cr[i]-1 << ' ';
	cout << '\n';

	cout << sp.size() << ' ';
	for(int i=0; i<sp.size(); ++i)cout << sp[i]-1 << ' ';
	cout << '\n';

	return 0;
}
