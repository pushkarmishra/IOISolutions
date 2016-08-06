#include<bits/stdc++.h>
using namespace std;

int ans=0, n, a, b, N, M;
static int lps[51];
map<int, vector< vector<char> > > m;
static char txt[2000010], pat[51];

void computeLPSArray()
{
	int len = 0; int i;
	lps[0] = 0; i=1;

    while(i < M)
    {
		if(pat[i] == pat[len])
		{
			len++;
			lps[i++] = len;
		}
		else
		{
			if(len) len=lps[len-1];
			else lps[i++] = 0;
		}
	}
}

void KMPSearch()
{
    int j=0, i=0;
    computeLPSArray();

    while(i < N)
    {
		if(pat[j] == txt[i])
		{
			j++; i++;
		}

		if (j == M)
		{
			ans++;
			j = lps[j-1];
		}

		else if(pat[j] != txt[i])
		{
			if(j!=0)j=lps[j-1];
			else i=i+1;
		}
    }
}

int main()
{
	cin >> a >> b >> n;
	cin >> txt;
	N=strlen(txt);

	for(int i=a; i<=b; ++i)
	{
		M=i;
		for(int j=0; j<(1<<i); ++j)
		{
			ans=0;
			int l=j;
			vector<char> str;
			for(int k=0; k<i; ++k)
			{
				int tmp=l%2;
				pat[k]=(char)(tmp+48);
				str.push_back((char)(tmp+48));
				l/=2;
			}
			KMPSearch();
			m[ans].push_back(str);
		}
	}

	map<int, vector< vector<char> > >::iterator it=m.end(); it--;
	for(int i=0; i<n; it--, i++)
	{
		int tmp=it->first;
		cout << tmp << ' ';
		for(int j=0; j<m[tmp].size(); ++j)
		{
			for(int k=0; k<m[tmp][j].size(); ++k)
				cout << m[tmp][j][k];
			cout << ' ';
		}
		cout << endl;
		if(it==m.begin())break;
	}
	return 0;
}
