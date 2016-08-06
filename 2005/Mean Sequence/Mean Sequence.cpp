#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, in, b=1e9, a=-1e9;
	cin >> n; 
	for(int i=1; i<=n; ++i)
	{
		cin >> in;
		b=min(b, in);
		int ta=2*in - b;
		b=2*in - a; a=ta;
	}
	cout << ((b-a+1>0)? b-a+1: 0) << endl;
	return 0;
}