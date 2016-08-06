#include <bits/stdc++.h>
#include "grader.h"
using namespace std;
#define s second
#define f first
const int mx=1e6+10;

int a, b, t;
static int wl[50010], sl[50010];
static pair<int, int> in[mx];

priority_queue<int, vector<int>, greater<int> > ps;
priority_queue<int> pw;

int process(int m)
{
	int idx=1;
	for(int i=1; i<=a; ++i)
	{
		while(in[idx].f<wl[i] && idx<=t)
			pw.push(in[idx++].s);

		int c=0;
		while(c<m && pw.size())
		{
			c++; pw.pop();
		}
	}

	while(pw.size())
	{
		ps.push(pw.top());
		pw.pop();
	}

	for(int i=idx; i<=t; ++i)
		ps.push(in[i].s);

	for(int i=1; i<=b; ++i)
	{
		int c=0;
		while(c<m && ps.size() && ps.top()<sl[i])
		{
			c++; ps.pop();
		}
	}

	int ret=ps.size()==0;
	while(ps.size())
		ps.pop();

	return ret;
}
int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[])
{
	a=A, b=B, t=T;

	for(int i=1; i<=a; ++i)
		wl[i] = X[i-1];
	for(int i=1; i<=b; ++i)
		sl[i] = Y[i-1];
	for(int i=1; i<=t; ++i)
		in[i].f=W[i-1], in[i].s=S[i-1];

	sort(wl+1, wl+a+1);
	sort(sl+1, sl+b+1);
	sort(in+1, in+t+1);

	int s=1, e=1e6, inf=1e6+1;
	while(s<=e)
	{
		int m=(s+e)>>1;
		int tmp=process(m);
		if(tmp)e=m-1;
		else s=m+1;
	}

	if(s==inf)cout << -1 << endl;
	return s;
}