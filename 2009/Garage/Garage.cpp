#include <bits/stdc++.h>
using namespace std;
const int mx=1e5+10;

priority_queue<int, vector<int>, greater<int> > pq;
queue<int> q;
int g, n, to=0, rev=0;
static int p[mx], w[mx], oc[mx];

int main()
{
	cin >> g >> n;
	for(int i=1; i<=g; ++i){ cin >> p[i]; pq.push(i); }
	for(int i=1; i<=n; ++i) cin >> w[i];

	for(int i=1, t; i<=2*n; ++i)
	{
		cin >> t;
		if(t>0)
		{
			q.push(t);
			while(to<g && q.size())
			{
				int u=pq.top(), v=q.front();
				pq.pop(); q.pop();
				rev+= (p[u]*w[v]);
				oc[v]=u; to++;
			}
		}
		else
		{
			t*=-1; pq.push(oc[t]); to--;
			while(to<g && q.size())
			{
				int u=pq.top(), v=q.front();
				pq.pop(); q.pop();
				rev+= (p[u]*w[v]);
				oc[v]=u; to++;
			}
		}
	}

	cout << rev << '\n';
	return 0;
}
