#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define xx first
#define yy second
using namespace std;

static pair<int, int> st[510];
static pair<int, int> srst[510][510];;
int n, ci;

int d(int a, int b)
{
	return abs(st[a].xx-st[b].xx)+abs(st[a].yy-st[b].yy);
}
int cmp(pair<int, int> l, pair<int, int> r)
{
	return l.xx>r.xx;
}

int diffh()
{
	int mret=INT_MAX;
	rep(i, 1, n)
	{
		rep(j, 1, i-1)
		{
			int diam=srst[i][1].xx+srst[i][2].xx;
			int d2=0, dh=d(i, j), sz=0;
			rep(k, 1, n-1)
			{
				int t=srst[i][k].yy;
				int t1=srst[i][k+1].yy;
				t1=(t1==j)?srst[i][k+2].yy:t1;
				if(t==j)continue;

				sz=max(sz, d2+d(j, t)); d2=max(d2, d(j, t));
				diam=min(diam, max(dh+d(t1, i)+d2, sz));
			}
			mret=min(diam, mret);
		}
	}
	return mret;
}

int main()
{
	cin >> n;
	rep(i, 1, n)cin >> st[i].xx >> st[i].yy;

	rep(i, 1, n) rep(j, 1, n) srst[i][j]=make_pair(d(i, j), j);
	rep(i, 1, n) ci=i, sort(srst[i]+1, srst[i]+n+1, cmp);

	cout << diffh() << '\n';
	return 0;
}
