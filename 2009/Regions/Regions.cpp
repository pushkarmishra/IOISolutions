#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <stack>
#include <cassert>
#include <set>
#include <climits>
#include <string>
#include <cstring>
#include <unordered_map>
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("regions.030.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
using namespace std;
const int mx=2e5+10;

map<int, int> precomp[mx/8];
vector<int> g[mx];

static int *reg[mx/8];
static int idx[mx/8], cntr[mx/8];
static int stim[mx], etim[mx], r[mx], st[mx];
int n, q, rc, tim=0, sqr;

void dfs(int u)
{
	stim[u]=++tim;
	reg[r[u]][idx[r[u]]++]=u;
	
	for(int i=0; i<g[u].size(); ++i)
	{
		int v=g[u][i];
		dfs(v);
	}
	etim[u]=tim;
}

int process(int r1, int r2)
{
	int top=-1;
	int i=0, j=0, cnt=0;
	if(!idx[r1] || !idx[r2]) return 0;
	
	while(j<idx[r2])
	{
		int s1, e1,
		    s2=stim[reg[r2][j]], e2=etim[reg[r2][j]];

		while(top>-1 && etim[st[top]] < s2)
			top--;
		while(i<idx[r1] && stim[reg[r1][i]] < s2)
		{
			s1=stim[reg[r1][i]], e1=etim[reg[r1][i]];
			if(e1>=e2) st[++top]=reg[r1][i];
			i++;
		}
		cnt+=top+1; j++;
	}
	return cnt;
}

int main()
{
	rf;// wf;
	
	scanf("%d %d %d", &n, &rc, &q);
	scanf("%d", &r[1]); cntr[r[1]]++;
	sqr=sqrt(n);

	rep(i, 2, n)
	{
		int boss; scanf("%d %d", &boss, &r[i]);
		g[boss].push_back(i); cntr[r[i]]++;
	}
	rep(i, 0, mx/8 - 1)
		reg[i]=new int[cntr[i]];
	dfs(1);

	rep(i, 1, rc)
	{
		if(idx[i]>=sqr)
		{
			rep(j, 1, rc)
				if(idx[j] < sqr)
				{
					precomp[i][j]=process(i, j);
					precomp[j][i]=process(j, i);
				}
				else precomp[i][j]=process(i, j);
		}
	}

	while(q--)
	{
		int r1, r2;
		scanf("%d %d", &r1, &r2);
		
		if(precomp[r1].find(r2)!=precomp[r1].end())
			printf("%d\n", precomp[r1][r2]);
		else printf("%d\n", process(r1, r2));

		cout.flush();
	}
	return 0;
}