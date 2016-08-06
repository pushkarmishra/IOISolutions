#include <bits/stdc++.h>
//#include "gondola.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define ll long long
#define pi pair<int, int>
#define mp make_pair
using namespace std;

int valid(int n, int inputSeq[])
{
	int st=0, v=0;
	rep(i, 0, n-1)
	{
		if(inputSeq[i]<=n)
			st=i, v=inputSeq[i];
	}

	if(v==0) return 1;
	rep(i, 0, n-1)
	{
		if(inputSeq[i]>n) continue;

		int p=(i-st+n)%n;
		int num=(p+v)%n; if(num==0) num=n;
		if(num!=inputSeq[i]) return 0;
	}
	return 1;
}

int replacement(int n, int gondolaSeq[], int replacementSeq[])
{
	priority_queue<pi, vector<pi>, greater<pi> > pq;

	int st=0, v=1;
	rep(i, 0, n-1)
		if(gondolaSeq[i]>n)
			pq.push(mp(gondolaSeq[i], i));
		else st=i, v=gondolaSeq[i];

	int l=0, idx=n+1;
	while(!pq.empty())
	{
		int p=(pq.top().second-st+n)%n;
		int num=(p+v)%n; if(num==0) num=n;
		replacementSeq[l++]=num;

		while(idx<pq.top().first)
			replacementSeq[l++]=idx++;

		idx=pq.top().first+1;
		pq.pop();
	}

	return l;
}

ll mod=1e9+9;
ll ex(ll b, ll e)
{
	if(e==0) return 1;
	if(e%2==0)
	{
		ll tmp=ex(b, e/2);
		return (tmp*tmp)%mod;
	}
	else
	{
		ll tmp=ex(b, e-1);
		return (tmp*b)%mod;
	}
}
ll getans(int n, int inputSeq[])
{
	priority_queue<int, vector<int>, greater<int> > pq;
	int chk=0;

	rep(i, 0, n-1)
	{
		if(inputSeq[i]<=n) chk=1;
		if(inputSeq[i]>n) pq.push(inputSeq[i]);
	}

	ll ret=valid(n, inputSeq);
	int idx=n+1;
	while(!pq.empty())
	{
		ll e=pq.top()-idx, b=pq.size();
		ll get=ex(b, e);
		ret = (ret*get)%mod;
		idx=pq.top()+1;
		pq.pop();
	}

	if(!chk) ret = (ret*n)%mod;
	return ret;
}
int countReplacement(int n, int inputSeq[])
{
	return getans(n, inputSeq);
}