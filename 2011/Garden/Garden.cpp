#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define s second
#define f first
#define pii pair<int, int>
const int mx=1010;

int n, m, p, ans, gr[100], q, tar;
vector< pii > g[mx];
queue< pair<pii, pii> > que;

int bfs(int s)
{
	que=queue< pair<pii, pii> >();
	que.push(mp(mp(s, 0), mp(-1, -1)));

	while(!que.empty() && que.front().f.s<=tar)
	{
		int u=que.front().f.f, l=que.front().f.s;
		int v=g[u][0].second;
		int prf=que.front().s.f, prs=que.front().s.s;

		if(u==p && l==tar)
			return 1;

		if((u==prf && v==prs) || (u==prs && v==prf))
		{
			if(g[u].size()==1)
				que.push(mp(mp(v, l+1), mp(u, v)));
			else
			{
				v=g[u][1].second;
				que.push(mp(mp(v, l+1), mp(u, v)));
			}
		}
		else
			que.push(mp(mp(v, l+1), mp(u, v)));

		que.pop();
	}

	return 0;
}

int main()
{
	cin >> n >> m >> p;
	for(int i=0, u, v; i<m; ++i)
	{
		cin >> u >> v;
		g[u].push_back(mp(i, v));
		g[v].push_back(mp(i, u));
	}
	for(int i=0; i<n; ++i)
		sort(g[i].begin(), g[i].end());

	cin >> q;
	for(int i=0; i<q; ++i)cin >> gr[i];
	tar=gr[0];

	for(int i=0; i<n; ++i)
		ans+=bfs(i);

	cout << ans << '\n';
	return 0;
}
