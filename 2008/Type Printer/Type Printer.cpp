#include <bits/stdc++.h>
using namespace std;

int n;
string s[25010];
vector<int> p;
vector<char> put;

int cmp(string l, string r)
{
	return (l.compare(r)<=0)? 1:0;
}
int ns(string a, string b)
{
	int j=0;
	for(; j<min(a.size(), b.size()); ++j)
		if(a[j]!=b[j])break;
	return j;
}

int main()
{
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> s[i];
	sort(s+1, s+n+1);

	int ilw=0, l=0;
	for(int i=1; i<=n; ++i)
		if(l<s[i].size())l=s[i].size(), ilw=i;

	int be=ilw-1, af=ilw+1;
	p.push_back(ilw);
	while(be || af<n+1)
	{
		if(!be || (af<=n && ns(s[af], s[ilw])>=ns(s[be], s[ilw])))
		{	p.push_back(af); af++; }
		else if(be)
		{	p.push_back(be); be--; }
	}
	reverse(p.begin(), p.end());

	int ans=s[p[0]].size()+1;
	for(int j=0; j<s[p[0]].size(); ++j)
		put.push_back(s[p[0]][j]);
	put.push_back('P');

	for(int i=1; i<p.size(); ++i)
	{
		int t=ns(s[p[i]], s[p[i-1]]);
		ans+= (s[p[i-1]].size()-t)+(s[p[i]].size()-t)+1;

		for(int j=t; j<s[p[i-1]].size(); ++j)
			put.push_back('-');
		
		for(int j=t; j<s[p[i]].size(); ++j)
			put.push_back(s[p[i]][j]);
		put.push_back('P');
	}

	cout << ans << '\n';
	for(int i=0; i<put.size(); ++i)
		cout << put[i] << '\n';
	return 0;
}
