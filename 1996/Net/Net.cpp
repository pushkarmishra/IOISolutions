#include <bits/stdc++.h>
using namespace std;

int n, s;
int g[110][110], tg[110][110];
int r[110], d[110], tr[110], td[110], vis[110];
vector<int> a, b;

void dfs(int gr[][110], int dom[], int req[], int u)
{
	vis[u]=dom[u]=1;
	req[u]=0;
	for(int i=1; i<=n; ++i)
	{
		if(!gr[u][i] || vis[i])continue;
		dfs(gr, dom, req, i);
	}
}

void find_dom(int gr[][110], int dom[], int req[], vector<int> &in)
{
	for(int i=1; i<=n; ++i)
	{
		if(dom[i])continue;
		memset(vis, 0, sizeof vis);
		dfs(gr, dom, req, i);
		req[i]=1;
	}

	for(int i=1; i<=n; ++i)
		if(req[i])in.push_back(i);
}

int main()
{
	cin >> n;
	for(int u=1, v; u<=n; ++u)
	{
		cin >> v;
		while(v)
		{
			g[u][v]=tg[v][u]=1;
			cin >> v;
		}
	}

	find_dom(g, d, r, a);
	find_dom(tg, td, tr, b);

	cout << a.size() << '\n';
	if(a[0]==b[0] && b.size()==1) cout << 0 << '\n';
	else cout << max(a.size(), b.size()) << '\n';
	
	return 0;
}
