#include <bits/stdc++.h>
using namespace std;
const int mx=1e6+10;

static int v1[mx], v2[mx], f[mx], in[mx];
int n, mn=INT_MAX, mni=0;
vector<int> g[mx];

void dfs1(int u)
{
	v1[u]=1, f[u]=in[u];
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i];
		if(v1[v])continue;

		dfs1(v);
		f[u]+=f[v];
	}
}

void dfs2(int u, int d)
{
	v2[u]=1;
	int mx=INT_MIN;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i];
		if(v2[v])continue;
		
		mx=max(mx, f[v]);
		dfs2(v, d+f[u]-f[v]);
	}
	if(mn>max(mx, d))
		mn=max(mx, d), mni=u;
}

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; ++i)
		scanf("%d", &in[i]);

	for(int i=1, u, v; i<n; ++i)
	{
		scanf("%d %d", &u, &v); u++; v++;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs1(1); dfs2(1, 0);

	printf("%d\n", mni-1);
	return 0;
}
