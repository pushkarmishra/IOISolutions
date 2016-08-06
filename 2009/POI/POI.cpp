#include <bits/stdc++.h>
using namespace std;
const int mx=2010;

int n, p, t;
static int q[mx][mx];
int pts[mx];
struct str {int p, i, n;} ans[mx];

int comp(const str& l, const str& r)
{
	return (l.p==r.p)? ((l.n==r.n)? l.i<r.i: l.n>r.n): l.p>r.p;
}

int main()
{
	cin >> n >> t >> p;
	fill(&pts[0], &pts[mx-1], n);

	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=t; ++j)
		{
			cin >> q[i][j];
			pts[j]-=q[i][j];
		}
	}

	for(int i=1; i<=n; ++i)
	{
		int num=0, pt=0;
		for(int j=1; j<=t; ++j)
		{
			if(q[i][j])
				pt+=pts[j], num+=1;
		}
		ans[i].p=pt, ans[i].i=i, ans[i].n=num;
	}
	sort(ans+1, ans+n+1, comp);

	for(int i=1; i<=n; ++i)
	{
	    if(ans[i].i==p)
		{
			cout << ans[i].p << ' ' << i << endl;
			break;
		}
	}
	return 0;
}
