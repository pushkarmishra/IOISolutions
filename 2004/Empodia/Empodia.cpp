#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;
const int mx=1e4+10;

static int cum[mx], em[mx], pos[mx], st[4*mx][2];
int n, in, qs, qe, ret[2];
pair<int, int> a[mx];

void build(int x, int y, int n)
{
	if(x==y)
		return void(st[n][0]=st[n][1]=pos[x]);
	int m=(x+y)>>1;
	build(x, m, 2*n); build(m+1, y, 2*n+1);

	st[n][0]=min(st[2*n][0], st[2*n+1][0]);
	st[n][1]=max(st[2*n][1], st[2*n+1][1]);
}
void qu(int x, int y, int n)
{
	if(y<qs || qe<x) return;
	if(qs<=x && y<=qe)
	{
		ret[0]=min(ret[0], st[n][0]);
		ret[1]=max(ret[1], st[n][1]);
		return;
	}
	int m=(x+y)>>1;
	qu(x, m, 2*n); qu(m+1, y, 2*n+1);
}

int main()
{
	cin >> n;
	assert(n<mx);
	rep(i, 1, n)
	{
		cin >> in; in++;
		pos[in]=i;
		a[i]=make_pair(in-pos[in], in);
	}

	sort(a+1, a+n+1);
	build(1, n, 1);

	rep(i, 1, n)
	{
		int j=i-1;
		while(a[j].first==a[i].first)
		{
			ret[0]=INT_MAX, ret[1]=INT_MIN;
			qs=a[j].second, qe=a[i].second;
			qu(1, n, 1);

			if(pos[qs]<=ret[0] && ret[1]<=pos[qe])
			{
				em[pos[qe]]=pos[qs];
				break;
			}
			j--;
		}
	}

	vector< pair<int, int> > ans; int st=0;
	rep(i, 3, n)
	{
		if(!em[i])continue;
		if(em[i]>=st)
		{
			ans.push_back(make_pair(em[i], i));
			st=em[i];
		}
	}

	cout << ans.size() << '\n';
	for(int i=0; i<ans.size(); ++i)
		cout << ans[i].first << ' ' << ans[i].second << endl;
	return 0;
}