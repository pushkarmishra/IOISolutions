#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define ll long long
using namespace std;

int in[202], n, m; char op;
map<ll, vector<int> > mp;
ll dp[102][102][2];

int main()
{
	cin >> n; m=2*n;
	rep(i, 0, m-1)
	{
		if(i%2)cin >> in[i];
		else {cin >> op; in[i]=op;}
	}

	rep(i, 1, n)
	{
		memset(dp, 0, sizeof dp);
		int st=(2*i-1);
		int en=(st-2+m)%m;

		for(int j=st;; j=(j+2)%m)
		{
			dp[j][j][0]=dp[j][j][1]=in[j];
			if(j==en) break;
		}

		rep(j, 1, n-1)
		{
			rep(k, 1, n-j)
			{
				int cs=(st+(k-1)*2)%m;
				int ce=(cs + 2*j)%m;
				ll maxv=LLONG_MIN, minv=LLONG_MAX;

				int l=cs;
				while(l!=ce)
				{
					ll a=dp[cs][l][1], b=dp[(l+2)%m][ce][1],
					   c=dp[cs][l][0], d=dp[(l+2)%m][ce][0];
					ll v=(in[(l+1)%m]==116)? a+b: a*b;
					ll v1=(in[(l+1)%m]==116)? c+d: c*d;

					maxv=max(maxv, max(v, v1));
					minv=min(minv, min(v, v1));

					l=(l+2)%m;
				}
				dp[cs][ce][1]=maxv;
				dp[cs][ce][0]=minv;
			}
		}
		mp[dp[st][en][1]].push_back(i);
	}

	map<ll, vector<int> >::iterator it=mp.end(); it--;
	cout << it->first << '\n';
	rep(i, 0, it->second.size()-1)
		cout << it->second[i] << ' ';
	cout << '\n';
	return 0;
}
