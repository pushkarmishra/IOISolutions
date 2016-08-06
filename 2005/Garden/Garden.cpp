#include <bits/stdc++.h>
using namespace std;
#define f(a) fill(&a[0], &a[299], (int)1e9)

int l, w, n, k;
static int gr[300][300]={0};
static int bl[300], br[300], bu[300], bd[300];

void transform()
{
	for(int i=1; i<=l; ++i)
		for(int j=1; j<=w; ++j)
			gr[i][j] += gr[i-1][j]+gr[i][j-1]-gr[i-1][j-1];
}
int get(int a1, int b1, int a2, int b2)
{
	if(a1>a2 || b1>b2)return 0;
	return gr[a2][b2]-gr[a1-1][b2]-gr[a2][b1-1]+gr[a1-1][b1-1];
}

int vr()
{
	for(int i=1; i<=w; ++i)
	{
		bl[i]=bl[i-1];
		for(int j=1; j<=i; ++j)
		{
			int a1=1, a2=1, tmp=1e9;
			while(1)
			{
				if(a2>l)break;
				int t=get(a1, j, a2, i);
				if(t==k)
					tmp=min(tmp, 2*((a2-a1+1)+(i-j+1)));
				a1+=(t>=k); a2+= (t<k);
			}
			bl[i]=min(bl[i], tmp);
		}
	}

	for(int i=w; i>=2; --i)
	{
		br[i-1]=br[i];
		for(int j=i; j<=w; ++j)
		{
			int a1=1, a2=1, tmp=1e9;
			while(1)
			{
				if(a2>l)break;
				int t=get(a1, i, a2, j);
				if(t==k)
					tmp=min(tmp, 2*((a2-a1+1)+(j-i+1)));
				a1+=(t>=k); a2+=(t<k);
			}
			br[i-1]=min(br[i-1], tmp);
		}
	}

	int ans=1e9;
	for(int i=1; i<=w; ++i)ans=min(ans, br[i]+bl[i]);
	return ans;
}

int hr()
{
	for(int i=1; i<=l; ++i)
	{
		bu[i]=bu[i-1];
		for(int j=1; j<=i; ++j)
		{
			int b1=1, b2=1, tmp=1e9;
			while(1)
			{
				if(b2>w)break;
				int t=get(j, b1, i, b2);
				if(t==k)
					tmp=min(tmp, 2*((b2-b1+1)+(i-j+1)));
				b1+=(t>=k); b2+=(t<k);
			}
			bu[i]=min(bu[i], tmp);
		}
	}

	for(int i=l; i>=2; --i)
	{
		bd[i-1]=bd[i];
		for(int j=i; j<=l; ++j)
		{
			int b1=1, b2=1, tmp=1e9;
			while(1)
			{
				if(b2>w)break;
				int t=get(i, b1, j, b2);
				if(t==k)
					tmp=min(tmp, 2*((b2-b1+1)+(j-i+1)));
				b1+=(t>=k); b2+=(t<k);
			}
			bd[i-1]=min(bd[i-1], tmp);
		}
	}

	int ans=1e9;
	for(int i=1; i<=l; ++i)ans=min(ans, bu[i]+bd[i]);
	return ans;
}

int main()
{
	cin >> w >> l >> n >> k;
	f(bl); f(br); f(bu); f(bd);
	for(int i=1, x, y; i<=n; ++i)
	{
		cin >> y >> x;
		gr[x][y]++;
	}
	transform();
	int ans=min(hr(), vr());
	(ans<1e9)? cout << ans <<'\n':cout <<"NO\n";
	return 0;
}
