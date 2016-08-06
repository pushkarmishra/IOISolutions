#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define sf second.first
#define ss second.second
using namespace std;
const int mx=20010;
const int s=1001;

int n;
struct{int x, y;} p[mx];
static int px[2*s], cx[2*s], py[2*s], cy[2*s];

int main()
{
	cin >> n;
	rep(i, 1, n)
	{
		cin >> p[i].x >> p[i].y;
		p[i].x+=s; p[i].y+=s;
	}
	p[0].x=s, p[0].y=s;

	rep(i, 0, 2*s-1)
		cx[i]=cy[i]=abs(i-s);

	rep(i, 1, n)
	{
		memcpy(px, cx, sizeof cx);
		memcpy(py, cy, sizeof cy);

		rep(j, 0, 2*s-1)
		{
			cx[j]=min(px[j]+abs(p[i].y-p[i-1].y),
				  py[p[i].y]+abs(j-p[i-1].x));
			cy[j]=min(py[j]+abs(p[i].x-p[i-1].x),
				  px[p[i].x]+abs(j-p[i-1].y));
		}
	}

	int ans=INT_MAX;
	rep(i, 0, 2*s-1)
		ans=min(ans, min(cx[i], cy[i]));
	cout << ans << endl;
	return 0;
}
