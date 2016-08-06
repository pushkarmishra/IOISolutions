#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;

static int dpp[150010], dpc[150010];
int q, m, k, f[2010], s[2010], nf=0, ans;

int main()
{
	cin >> q >> m >> k;
	rep(i, 1, m){cin >> f[i]; nf+=f[i];}
	rep(i, 1, k)cin >> s[i];

	sort(s+1, s+k+1);
	sort(f+1, f+m+1);

	if(nf<q)
	{
		int i=k;
		while(nf<q) nf+=s[i--];
		ans=q-k+i;
	}
	else if(q==nf)ans=nf;
	else
	{
		dpp[0]=1;
		rep(i, 1, m)
		{
			rep(j, 0, q)
			{
				dpc[j]=dpp[j];
				if(j>=f[i])dpc[j]=max(dpc[j], dpp[j-f[i]]);
			}
			memcpy(dpp, dpc, sizeof dpc);
			memset(dpc, 0, sizeof dpc);
		}
		ans=(dpp[q])? q: q-1;
	}

	cout << ans << endl;
	return 0;
}