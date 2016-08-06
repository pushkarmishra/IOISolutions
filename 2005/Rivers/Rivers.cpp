#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=8e9;

int n, k;
static int v[110], d[110], dis[110],
			w[110], dep[110];
vector<int> g[110];
static ll dp[110][52][110], tmp[52][110];

void solve(int u)
{
	int t=u, l=dep[t];
	while(t>-1)
	{
		for(int i=0; i<=k+1; ++i)
			dp[u][i][l]=(dis[u]-dis[t])*w[u];
		t=v[t], l=dep[t];
	}

	for(int i=0; i<g[u].size(); ++i)
	{
		for(int p=0; p<52; ++p)
			for(int q=0; q<110; ++q)
				tmp[p][q]=inf;

		int e=g[u][i];
		for(int p=0; p<=k+1; ++p)
		{
			for(int q=0; p+q<=k+1; ++q)
			{
				tmp[p+q+1][dep[u]]=min(tmp[p+q+1][dep[u]],
							dp[u][p+1][dep[u]]+dp[e][q][dep[u]]);

				t=v[u], l=dep[t];
				while(t>-1)
				{
					tmp[p+q][l] = min(tmp[p+q][l],
								dp[u][p][l]+dp[e][q][l]);
					tmp[p+q+1][l]=min(tmp[p+q+1][l],
								tmp[p+q+1][dep[u]]);

					t=v[t]; l=dep[t];
				}
			}
		}

		for(int p=0; p<=k+1; ++p)
			for(int q=0; q<=dep[u]; ++q)
				dp[u][p][q]=tmp[p][q];
	}
}

void tree_dp(int u, int di, int de)
{
	dep[u]=de, dis[u]=di;

	for(int i=0; i<g[u].size(); ++i)
	{
		int e=g[u][i];
		tree_dp(e, di+d[e], de+1);
	}
	if(u<n+1)solve(u);
}

int main()
{
	cin >> n >> k;
	for(int i=1; i<=n; ++i)
	{
		scanf("%d %d %d",&w[i], &v[i], &d[i]);
		g[v[i]].push_back(i);
	}

	v[0]=-1;
	for(int i=1; i<=n; ++i)
		if(!g[i].size())g[i].push_back(n+1);

	for(int i=0; i<=n+1; ++i)
		for(int j=0; j<=k+1; ++j)
			for(int l=0; l<=n+1; ++l)
				dp[i][j][l]=inf;
	for(int i=0; i<=n; ++i)dp[n+1][0][i]=0;

	tree_dp(0, 0, 0);

	cout << dp[0][k+1][0] << '\n';
	return 0;
}
