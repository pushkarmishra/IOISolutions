#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
using namespace std;
const int mx=1e4+10;

int sig[][2]={{0, 0}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
int n;
int in[2*mx], reg[mx], x[mx], y[mx];

int main()
{
	cin >> n;
	rep(i, 1, 2*n) cin >> in[i];
	rep(i, 1, n) cin >> reg[i];
	
	sort(in+1, in+2*n+1);
	rep(i, 1, n)
		x[i]=in[i], y[i]=in[i+n];
	
	int xs=n, ys=n;
	rep(i, 2, n)
	{
		int prev=reg[i-1], cur=reg[i];
		if(sig[prev][0]!=sig[cur][0]) xs--;
		if(sig[prev][1]!=sig[cur][1]) ys--;
	}
	
	int x1=xs, x2=xs, y1=ys, y2=ys;
	char a=(sig[reg[1]][0]<0)? '-':'+', b=(sig[reg[1]][1]<0)? '-':'+';
	
	cout << a << x[x2] << ' ' << b << y[y2] << '\n';
	rep(i, 2, n)
	{
		int prev=reg[i-1], cur=reg[i];
		
		if(sig[cur][0]!=sig[prev][0])
		{
			++x2;
			char s=((x2-xs)%2)? ((a=='+')? '-':'+'):a;
			cout << s << x[x2] << ' ';
		}
		else
		{
			--x1;
			char s=((xs-x1)%2)? ((a=='+')? '-':'+'):a;
			cout << s << x[x1] << ' ';
		}
		
		if(sig[cur][1]!=sig[prev][1])
		{
			++y2;
			char s=((y2-ys)%2)? ((b=='+')? '-':'+'):b;
			cout << s << y[y2] << '\n';
		}
		else
		{
			--y1;
			char s=((ys-y1)%2)? ((b=='+')? '-':'+'): b;
			cout << s << y[y1] << '\n';
		}
	}
	return 0;
}
