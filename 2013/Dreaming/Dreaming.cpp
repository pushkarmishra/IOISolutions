#include <bits/stdc++.h>
using namespace std;
const int mx=1e5+10;

int n, m, l, cmpmn, ans=0;
int v1[mx]={0}, v2[mx]={0}, ld[mx][3]={0};
vector< pair<int, int> > g[mx];
vector<int> bl;

void dfs1(int u)
{
	v1[u]=1;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first, d=g[u][i].second;
		if(v1[v])continue;
		
		dfs1(v);
		int mo=ld[v][1]+d;
		if(mo>ld[u][1])swap(mo, ld[u][1]);
		if(mo>ld[u][2])swap(mo, ld[u][2]);
	}
}
void dfs2(int u, int q)
{
	v2[u]=1;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first, d=g[u][i].second;
		if(v2[v])continue;
		
		if(ld[v][1]+d==ld[u][1])
			dfs2(v, max(q+d, ld[u][2]+d));
		else
			dfs2(v, max(q+d, ld[u][1]+d));
	}
	ld[u][1]=max(q, ld[u][1]);
	ans=max(ans, ld[u][1]);
	cmpmn=min(ld[u][1], cmpmn);
}

int travelTime(int N, int M, int L, int A[], int B[], int T[])
{
	n=N, m=M, l=L;
	for(int i=1, u, v, d; i<=m; ++i)
	{
		u=A[i-1], v=B[i-1], d=T[i-1]; u++; v++;
		g[u].push_back(make_pair(v, d));
		g[v].push_back(make_pair(u, d));
	}

	for(int i=1; i<=n; ++i)
	{
		if(!v1[i])
			dfs1(i);
		cmpmn=2e9;
		if(!v2[i])
			dfs2(i, 0);
		if(cmpmn<2e9)bl.push_back(cmpmn);
	}

	sort(bl.begin(), bl.end()); int sz=bl.size()-1;
	while(sz)
	{
		ans=max(ans, bl[sz]+bl[sz-1]+l);
		bl[sz-1]=max(bl[sz], bl[sz-1]+l);
		sz--;
	}
	return ans;
}