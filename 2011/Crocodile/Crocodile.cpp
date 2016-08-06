#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll, int>
const ll inf=1e18, mx=100010;

vector< pair<int, ll> > g[mx];
multiset<pli> ms;
multiset<pli>::iterator it;
static ll dj[mx][2];
static int vis[mx]={0};

void djik()
{
    while(!ms.empty())
	{
		int u=ms.begin()->second; vis[u]=1;
    	ll cur=ms.begin()->first;

    	for(int i=0; i<g[u].size(); ++i)
    	{
        	int v=g[u][i].first; ll d=g[u][i].second;
        	if(vis[v])
				continue;

        	if(cur+d <= dj[v][0])
        	{
            	it=ms.find(make_pair(dj[v][1], v));
            	ms.erase(it);
            	swap(dj[v][0], dj[v][1]);
            	dj[v][0]=cur+d;
            	ms.insert(make_pair(dj[v][1], v));
        	}
        	else if(cur+d < dj[v][1])
        	{
            	it=ms.find(make_pair(dj[v][1], v));
            	ms.erase(it);
            	dj[v][1]=cur+d;
            	ms.insert(make_pair(dj[v][1], v));
        	}
    	}
    	it=ms.find(make_pair(dj[u][1], u));
		ms.erase(it);
	}
}

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
    for(int i=0; i<M; ++i)
    {
        int u=R[i][0]+1, v=R[i][1]+1; ll d=L[i];
        g[u].push_back(make_pair(v, d));
        g[v].push_back(make_pair(u, d));
    }

	for(int i=0; i<mx; ++i)dj[i][0]=dj[i][1]=inf;
	for(int i=0; i<K; ++i)
   		dj[P[i]+1][0]=dj[P[i]+1][1]=0;

    for(int i=1; i<=N; ++i)
        ms.insert(make_pair(dj[i][1], i));

    djik();
    return dj[1][1];
}
