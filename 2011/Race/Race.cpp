#include <bits/stdc++.h>
using namespace std;
const int mx=200010;

vector< pair<int, int> > g[mx], vec;
map<int, int> sk;
static int des[mx], rem[mx]={0}, n, k;

void find_path(int u, int path, int l, int p)
{
	if(path<=k)
		vec.push_back(make_pair(path, l));
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first, d=path+g[u][i].second;
		if(v!=p && !rem[v] && d<=k)
			find_path(v, d, l+1, u);
	}
}
int find_node(int u, int tot, int tar, int p)
{
	int chk=1, ret=-1;
	if(tot-des[u]>tar)chk=0;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first;
		if(v!=p && !rem[v])
		{
			ret=max(ret, find_node(v, tot, tar, u));
			if(des[v]>tar)chk=0;
		}
	}
	return (chk)? u:ret;
}
void count(int u, int p)
{
	des[u]=1;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first;
		if(v!=p && !rem[v])
		{
			count(v, u);
		    des[u]+=des[v];
		}
	}
}
int process(int u)
{
	sk.clear(); sk[k]=2e9; sk[0]=0;
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i].first, d=g[u][i].second;
		if(rem[v])continue;

		vec.clear(); count(v, u); find_path(v, d, 1, u);
		for(int j=0; j<vec.size(); ++j)
		{
			int t1=vec[j].first, t2=vec[j].second;
			if(sk.find(k-t1) != sk.end())
				sk[k]=min(sk[k-t1]+t2, sk[k]);
		}
		for(int j=0; j<vec.size(); ++j)
		{
			int t1=vec[j].first, t2=vec[j].second;
			if(sk.find(t1)==sk.end()) sk[t1]=t2;
			else sk[t1]=min(sk[t1], t2);
		}
	}
	return sk[k];
}

int solve(int u, int p)
{
	int node=find_node(u, des[u], des[u]/2, p);
	rem[node]=1;
	int ret=process(node);
	
	for(int i=0; i<g[node].size(); ++i)
	{
		int v=g[node][i].first;
		if(!rem[v]) ret=min(ret, solve(v, node));
	}
	return ret;
}

int best_path(int N, int K, int H[][2], int *L)
{
	n=N, k=K;
	for(int i=0; i<N-1; ++i)
	{
		pair<int, int> u=make_pair(H[i][0], L[i]),
					   v=make_pair(H[i][1], L[i]);
		g[u.first].push_back(v);
		g[v.first].push_back(u);
	}
	count(0, -1); int ans=solve(0, -1);
	return (ans>n)? -1:ans;		
}

int N, K, H[mx][2], L[mx];
int main()
{
	cin >> N >> K;
	for(int i=0; i<N-1; ++i)
		cin >> H[i][0] >> H[i][1] >> L[i];
	
	cout << best_path(N, K, H, L);
	return 0;
}
