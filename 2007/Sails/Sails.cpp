#include <bits/stdc++.h>
using namespace std;
const int mx=1e5+10;

struct mast{int h, k;} a[mx];
int n, h, k, las=-1, mxh=1;
static int b[mx], d[mx];

int cmp(const mast& l, const mast& r)
{
	return (l.h==r.h)? l.k<r.k: l.h<r.h;
}

void up(int i, int v)
{
	for(; i<mx; i+=i&-i)b[i]+=v;
}
int q(int i)
{
	int ret=0;
	for(; i; i-=i&-i) ret+=b[i];
	return ret;
}

pair<int, int> bs(int i)
{
	int v=q(i);
	pair<int, int> ret=make_pair(i, i);
	
	int s=1, e=i;
	while(s<=e)
	{
		int m=(s+e)>>1;
		if(q(m)==v)e=m-1;
		else s=m+1;
	}
	ret.first=s;

	s=i, e=mxh-1;
	while(s<=e)
	{
		int m=(s+e)>>1;
		if(q(m)==v) s=m+1;
		else e=m-1;
	}
	ret.second=s;

	return ret;
}

long long process()
{
	for(int i=1; i<=n; ++i)
	{
		while(mxh<=a[i].h)
		{
			d[mxh]=0-las; las=0;
			if(d[mxh]!=0) up(mxh, 1);
			mxh++;
		}

		int idx=mxh-a[i].k;
		if(d[idx]!=0)
		{
			d[idx]++, las++;
			if(d[idx]==0) up(idx, -1);
			continue;
		}

		pair<int, int> get=bs(idx);
		int num=get.second-idx;

		d[get.first]++;
		if(d[get.first]==0) up(get.first, -1);

		if(get.first+num<mxh) d[get.first+num]--;
		if(d[get.first+num]!=0) up(get.first+num, 1);

		if(get.second<mxh) d[get.second]++;
		if(d[get.second]==0 && get.second<mxh)
			up(get.second, -1);

		if(get.second<mxh) las++;
	}

	long long ret=0, cur=-1;
	for(int i=1; i<mxh; ++i)
	{
		cur=d[i]+cur;
		ret+= (cur*(cur-1))/2;
	}
	
	return ret;
}

int main()
{
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> a[i].h >> a[i].k;
	sort(a+1, a+n+1, cmp);

	cout << process() << '\n';
	return 0;
}
