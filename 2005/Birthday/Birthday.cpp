#include <bits/stdc++.h>
using namespace std;
const int mx=1e6+10;

int best=0;
int n, p[mx], pr[mx];

int main()
{
	cin >> n;
	for(int i=0; i<n; ++i)
	{
		cin >> p[i]; p[i]--;
		pr[n-1-i]=p[i];
		p[i]=i-p[i]; pr[n-1-i]=n-1-i-pr[n-1-i];
	}
	for(int i=0; i<n; ++i)
	{
		if(p[i]<=-(n/2)) p[i]+=n;
		else if(p[i]>n/2) p[i]-=n;

		if(pr[i]<=-(n/2)) pr[i]+=n;
		else if(pr[i]>n/2) pr[i]-=n;
	}
	sort(p, p+n); sort(pr, pr+n);

	for(int i=0; i<n-1; ++i)
	{
		best=max(best, p[i+1]-p[i]);
		best=max(best, pr[i+1]-pr[i]);
	}
	best=max(best, max(pr[0]+n-pr[n-1], p[0]+n-p[n-1]))-1;
	
	cout << (n-best)/2 << endl;
	return 0;
}