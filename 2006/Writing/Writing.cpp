#include <bits/stdc++.h>
using namespace std;

int ns, nw, cnt[256], ct[256], ans=0;
string s, w;

int main()
{
	cin >> nw >> ns;
	cin >> w >> s;
	for(int i=0; i<nw; ++i)
		cnt[w[i]]++;

	int a=0, b=-1;
	for(int i=0; i<ns; ++i)
	{
		ct[s[i]]++; b++;
		while(ct[s[i]]>cnt[s[i]])
			ct[s[a++]]--;
		if(b-a+1==nw)ans++;
	}

	cout << ans << '\n';
	return 0;
}