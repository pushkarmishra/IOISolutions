#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pi pair<int, int>
#define pii pair<int, pi>

static pii st[2100][2100], foo, up, ret;
int n, m, a, b, c, d, r1, r2, c1, c2, chk, ans=INT_MIN;
static int ar[1010][1010];
pair< pi, pi> coor;

void upr(int r, int x, int y, int p)
{
	if(y<c1 || c2<x) return;
	if(c1<=x && y<=c2)
	{
		st[r][p]=(chk)? up: min(st[2*r][p], st[2*r+1][p]);
		return;
	}
	int mid=(x+y)>>1;
	upr(r, x, mid, 2*p); upr(r, mid+1, y, 2*p+1);
	st[r][p]=min(st[r][2*p], st[r][2*p+1]);
}
void upc(int x, int y, int p)
{
	if(y<r1 || r2<x) return;
	if(r1<=x && y<=r2)
	{
		chk=1; upr(p, 1, m, 1);
		return;
	}
	int mid=(x+y)>>1;
	upc(x, mid, 2*p); upc(mid+1, y, 2*p+1);
	chk=0; upr(p, 1, m, 1);
}

pii qur(int r, int x, int y, int p)
{
	if(y<c1 || c2<x) return foo;
	if(c1<=x && y<=c2)
		return st[r][p];
	int mid=(x+y)>>1;
	return min(qur(r, x, mid, 2*p), qur(r, mid+1, y, 2*p+1));
}
pii quc(int x, int y, int p)
{
	if(y<r1 || r2<x) return foo;
	if(r1<=x && y<=r2)
		return qur(p, 1, m, 1);
	int mid=(x+y)>>1;
	return min(quc(x, mid, 2*p), quc(mid+1, y, 2*p+1));
}

void transfrm()
{
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			ar[i][j]+= ar[i-1][j]+ar[i][j-1]-ar[i-1][j-1];
}
int get(int r1, int c1, int r2, int c2)
{
	return ar[r2][c2]-ar[r2][c1]-ar[r1][c2]+ar[r1][c1];
}

int main()
{
	scanf( "%d %d %d %d %d %d", &m, &n, &b, &a, &d, &c);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			scanf("%d", &ar[i][j]);

	transfrm();
	foo=mp((int)2e9, mp(0, 0));

	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			if(i-c>=0 && j-d>=0)
			{
				int tmp=get(i-c, j-d, i, j);
				up=mp(tmp, mp(i-c+1, j-d+1));
				r1=r2=i-c+1, c1=c2=j-d+1;
				upc(1, n, 1);
			}
		}
	}

	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			if(i-a>=0 && j-b>=0)
			{
				int tmp=get(i-a, j-b, i, j);
				r1=i-a+2, r2=i-c, c1=j-b+2, c2=j-d;
				ret=quc(1, n, 1);
				if(tmp-ret.first>ans)
				{
					ans=tmp-ret.first;
					coor=mp(mp(i-a+1, j-b+1), ret.second);
				}
			}
		}
	}

	cout << coor.first.second << ' ' << coor.first.first << '\n';
	cout << coor.second.second << ' ' << coor.second.first << '\n';
	return 0;
}