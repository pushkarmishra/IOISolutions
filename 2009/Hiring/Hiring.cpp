#include <bits/stdc++.h>
using namespace std;
const int mx=5e5+10;

static int n, bi=0, bnw=0;
struct worker{double s, q, u; int i;} p[mx];
double w, tq=0, bcst=0;

int comp(worker const& l, worker const& r)
{
	return l.u<r.u;
}

int main()
{
	scanf("%d %lf", &n, &w);
	for(int i=1; i<=n; ++i)
	{
		scanf("%lf %lf", &p[i].s, &p[i].q);
		p[i].u=p[i].s/p[i].q; p[i].i=i;
	}
	sort(p+1, p+n+1, comp);

	priority_queue<double> pq;
	for(int i=1; i<=n; ++i)
	{
		tq+=p[i].q;
		pq.push(p[i].q);

		while(tq*p[i].u > w)
		{
			tq-=pq.top();
			pq.pop();
		}

		int nw=pq.size();
		double tcst=tq*p[i].u;

		if(nw>bnw || (nw==bnw && tcst<bcst))
			bnw=nw, bi=i, bcst=tcst;
	}

	tq=0;
	priority_queue< pair<double, int> > get;
	for(int i=1; i<=bi; ++i)
	{
		tq+=p[i].q;
		get.push(make_pair(p[i].q, p[i].i));
	}

	while(tq*p[bi].u>w)
	{
		tq-=get.top().first;
		get.pop();
	}

	cout << get.size() << '\n';
	while(!get.empty())
	{
		cout << get.top().second << '\n';
		get.pop();
	}

	return 0;
}
