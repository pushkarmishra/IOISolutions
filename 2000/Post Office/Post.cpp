#include <bits/stdc++.h>
using namespace std;

static int dp[400][35]={0};
int n, p, d[400], cd[400], par[400][35];

int main()
{
	cin >> n >> p;
	for(int i=1; i<=n; ++i)
	{
		cin >> d[i];
		cd[i]=cd[i-1]+d[i];
	}
	d[++n]=1e9; cd[n]= cd[n-1]+d[n];
	fill(&dp[0][0], &dp[399][34], (int)1e9);

	for(int i=1; i<=n; ++i)
	{
		dp[i][1]=(i*d[i])-cd[i];

		for(int j=2; j<=p+1; ++j)
		{
			if(j>i) break;
			int t=i-1;
			int mn=INT_MAX, mni=i;

			for(int k=i-1; k; --k)
			{
				while(d[t]-d[k]>d[i]-d[t])
					t--;

				int tmp=dp[k][j-1];
				tmp+= cd[t]-cd[k]-((t-k)*d[k]);
				tmp+= ((i-t)*d[i])-(cd[i]-cd[t]);

				if(tmp<mn)
					mn=tmp, mni=k;
			}

			dp[i][j]=mn, par[i][j]=mni;
		}
	}

	cout << dp[n][p+1] << '\n';

	vector<int> tmp;
	int u=par[n][p+1];
	while(p)
	{
		tmp.push_back(u);
		u=par[u][p]; p--;
	}
	reverse(tmp.begin(), tmp.end());

	for(int i=0; i<tmp.size(); ++i)
		cout << d[tmp[i]] << ' ';
	cout << endl;
	return 0;
}
