#include <bits/stdc++.h>
#include "holiday.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define rf freopen("in.in", "r", stdin)
#define ll long long
using namespace std;

priority_queue< int, vector<int>, greater<int> > pq;

ll process(int s, int d, int t, int a[])
{
	pq = priority_queue< int, vector<int>, greater<int> >();
	int i=s;
	ll mret=0, ret=0;

	while((s<=d && i<=d) || (s>d && i>=d))
	{
		t--; ret+=a[i];
		pq.push(a[i]);

		if(t>=0)
			mret=max(mret, ret);
		while(t<2 && !pq.empty())
		{
			t+=1; ret-=pq.top();
			pq.pop();
		}
		t--;
		i=(s<=d)? i+1:i-1;
	}
	return mret;
}

ll findMaxAttraction(int n, int s, int d, int a[])
{
	ll mret=0;
	rep(i, 0, n-1)
	{
		mret=max(mret, process(i, 0, d-abs(i-s), a));
		mret=max(mret, process(i, n-1, d-abs(i-s), a));
	}
	return mret;
}

/*int main()
{
	//rf;
	int n, s, d, a[100010];

	cin >> n >> s >> d;
	rep(i, 0, n-1)
		cin >> a[i];

	cout << findMaxAttraction(n, s, d, a) << '\n';
	return 0;
}*/