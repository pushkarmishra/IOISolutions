#include <bits/stdc++.h>
using namespace std;
#define up first
#define dw second
#define ll long long
const ll inf=8e18;
const int mx=5e5+10;

int n, qs, qe, chk; ll u, d, s;
struct pos{ll t, l, m;} p[mx];
static ll dp[mx], dpp[mx];
static pair<ll, ll> st[mx*5];

int cmp(pos const& l, pos const& r)
{
	return(l.t==r.t)? l.l<r.l: l.t<r.t;
}

int get(int so, int de)
{
	int tmp=(so>de)? (de-so)*u: (so-de)*d;
	return tmp;
}

void upd(int i, int x, int y, int n)
{
	if(y<qs || qe<x) return; 
	if(qs<=x && y<=qe)
	{
		st[n].up=dp[i]-(p[i].l*u);
		st[n].dw=dp[i]+(p[i].l*d);
		return;
	}
	int m=(x+y)>>1;
	upd(i, x, m, 2*n); upd(i, m+1, y, 2*n+1);

	st[n].up=max(st[2*n].up, st[2*n+1].up);
	st[n].dw=max(st[2*n].dw, st[2*n+1].dw);
}

ll que(int x, int y, int n)
{
	if(y<qs || qe<x)return -inf;
	if(qs<=x && y<=qe)
		return (chk)? st[n].up: st[n].dw;
	int m=(x+y)>>1;
	return max(que(x, m, 2*n), que(m+1, y, 2*n+1));
}

ll solve()
{
	for(int i=0; i<mx*5; ++i) st[i].up=st[i].dw=-inf;
	dp[0]=0; dp[n+1]=-inf;
	qs=qe=p[0].l; upd(0, 0, mx, 1);

	for(int i=1; i<=n;)
	{
		int ti=i;
		while(p[i].t==p[ti].t && ti<=n)ti++;
		
		for(int j=i; j<ti; ++j)
		{
			qs=p[j].l+1, qe=mx, chk=1;
			ll dws=que(0, mx, 1)+(p[j].l*u);

			qs=0, qe=p[j].l-1, chk=0;
			ll ups=que(0, mx, 1)-(p[j].l*d);

			dp[j]=max(ups, dws)+p[j].m;
			qs=qe=p[j].l;
			upd(j, 0, mx, 1);

		}

		for(int j=i; j<ti; ++j)
		{
			dpp[j]=dp[j]; dp[j]=-inf;
			qs=qe=p[j].l;
			upd(n+1, 0, mx, 1);
		}

		for(int j=ti-1; j>=i; --j)
		{
			qs=p[j].l+1, qe=mx, chk=1;
			ll dws=que(0, mx, 1)+(p[j].l*u);

			qs=0, qe=p[j].l-1, chk=0;
			ll ups=que(0, mx, 1)-(p[j].l*d);

			dp[j]=max(ups, dws)+p[j].m;
			qs=qe=p[j].l;
			upd(j, 0, mx, 1);
		}
		for(int j=ti-1; j>=i; --j)
		{
			dp[j]=max(dp[j], dpp[j]);
			qs=qe=p[j].l;
			upd(j, 0, mx, 1);
		}
		i=ti;
	}

	ll ans=-inf;
	for(int i=0; i<=n; ++i)
		ans=max(ans, dp[i]+get(p[i].l, p[0].l));

	return ans;
}

int main()
{
	scanf("%d %lld %lld %lld", &n, &u, &d, &s);
	p[0].t=-1, p[0].l=s, p[n+1].l=0;
	for(int i=1; i<=n; ++i)
		scanf("%lld %lld %lld", &p[i].t, &p[i].l, &p[i].m);
	sort(p, p+n+1, cmp);

	ll ans=solve();
	cout << ans << '\n';
	return 0;
}
