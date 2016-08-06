#include<bits/stdc++.h>
using namespace std;

static int L[3][5010]; int n;
char s[5010];

void copy_prev()
{
	for(int i=0; i<5010; ++i)
		L[0][i]=L[1][i], L[1][i]=L[2][i], L[2][i]=0;
}

int lps()
{
	for (int i = 0; i < n; i++)
		L[0][i]=0, L[1][i]=1;
					 
	for (int cl=2; cl<=n; cl++)
	{
		for (int i=0; i<n-cl+1; i++)
		{
			int j = i+cl-1;
			if (s[i] == s[j])
				L[2][i] = L[0][i+1] + 2;
			else
				L[2][i] = max(L[1][i], L[1][i+1]);
		 }

		 copy_prev();
	}
	
	return L[1][0];
}

int main()
{
	cin >> n >> s;
	printf ("%d\n", n-lps());
	return 0;
}
