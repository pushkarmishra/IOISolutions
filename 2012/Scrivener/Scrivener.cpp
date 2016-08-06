#include <bits/stdc++.h>
#include "scrivener.h"
using namespace std;
const int mx=1e6+10;

vector<int> anc[mx];
vector< pair<int, char> > g[mx];
static int ptr[mx], len[mx], idx=0;
char rec[mx];

void Init()
{
	;
}

void TypeLetter(char L)
{
	int q=ptr[idx], tmp=-1;
	for(int i=0; i<g[q].size(); ++i)
	{
		int v=g[q][i].first;
		char c=g[q][i].second;
		
		if(c==L)
			tmp=v;
	}

	if(tmp!=-1)
	{
		ptr[idx+1]=tmp;
	}
	else
	{
		ptr[idx+1]=idx+1;
		rec[idx+1]=L;
		len[idx+1]=len[q]+1;

		g[q].push_back(make_pair(idx+1, L));
		anc[idx+1].push_back(q);

		int j=0, pos=q;
		while(anc[pos].size()>j)
		{
			anc[idx+1].push_back(anc[pos][j]);
			pos=anc[pos][j]; j++;
		}
	}
	idx++;
}
void UndoCommands(int U)
{
	ptr[idx+1]=ptr[idx-U]; ++idx;
}
char GetLetter(int P)
{
	int pos=ptr[idx], u=len[pos]-P-1;
	while(u)
	{
		int tmp=log2(u);
		pos=anc[pos][tmp];
		u-=pow(2, tmp);
	}
	if(u==0 && pos)return rec[pos];
}