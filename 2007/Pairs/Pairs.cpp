#include <bits/stdc++.h>
using namespace std;
const int mx=1e5+10;

int n, b, m, d; long long ans=0;
struct pt{int x, y, z;} p[mx];
static int bit1[2*mx], bit2[mx/1000][mx/1000][mx/1000];

int cmp(pt const& l, pt const& r)
{
	if(b==1) return l.x<r.x;
	if(b==2) return (l.x==r.x)? l.y<r.y: l.x<r.x;
	if(b==3) return (l.x==r.x)? ((l.y==r.y)? l.z<r.z: l.y<r.y):l.x<r.x;
}

void up1(int i, int v)
{
	for(; i<2*mx; i+=i&-i)bit1[i]+=v;
}
int qu1(int i)
{
	int ret=0;
	for(; i; i-=i&-i)ret+=bit1[i];
	return ret;
}

int main()
{
	cin >> b >> n >> d >> m;
	
	if(b==1)
	{
		for(int i=1; i<=n; ++i)
			cin >> p[i].x;
		sort(p+1, p+n+1, cmp);

		int j=1;
		for(int i=1; i<=n; ++i)
		{
			while(p[j].x<p[i].x-d) j++;
			ans+= i-j;
		}

		cout << ans << '\n';
	}

	else if(b==2)
	{
		for(int i=1; i<=n; ++i)
			cin >> p[i].x >> p[i].y;

		pair<int, int> tmp[mx];
		for(int i=1; i<=n; ++i)
			tmp[i].first=p[i].x-p[i].y,
			tmp[i].second=p[i].x+p[i].y;
		sort(tmp+1, tmp+n+1);

		int j=1;
		for(int i=1; i<=n; ++i)
		{
			while(tmp[j].first < tmp[i].first-d)
				up1(tmp[j++].second, -1);

			ans += qu1(tmp[i].second)-qu1(max(tmp[i].second-d-1, 0));
			ans += qu1(min(tmp[i].second+d, 2*mx-1))-qu1(tmp[i].second);
			up1(tmp[i].second, 1);
		}

		cout << ans << '\n';
	}
	return 0;
}
