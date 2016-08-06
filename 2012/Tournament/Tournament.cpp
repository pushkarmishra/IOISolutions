#include <bits/stdc++.h>
using namespace std;
const int mx=100010;

int n, c, r, node;
static int bit[mx], gr[mx], s[mx], e[mx];
pair<int, int> mr[mx], bst[3*mx];
set<int> al;
set<int>::iterator it;

void up(int i, int v)
{
	for(; i<mx; i+=i&-i)bit[i]+=v;
}
int get(int i)
{
	int ret=0;
	for(; i; i-=i&-i)ret+=bit[i];
	return ret;
}
int binsearch(int v)
{
	int s=1, e=n;
	while(s<=e)
	{
		int mid=(s+e)>>1;
		if(get(mid)<=v)s=mid+1;
		else e=mid-1;
	}
	return e;
}

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E)
{
	n=N, c=C, r=R;
	for(int i=1; i<=n; ++i)
	{
		if(i<n)gr[i]=K[i-1];
		gr[i]=gr[i-1]+(gr[i]>r);
		mr[i]=make_pair(i, i);
		bst[i]=make_pair(0, i);
		up(i, 1);
		al.insert(i);
	}
	for(int i=1; i<=c; ++i)
	{
		s[i]=S[i-1], e[i]=E[i-1];
		s[i]++; e[i]++;
	}

	for(int i=1; i<=c; ++i)
	{
		node=n+i;
		int x=binsearch(s[i]-1)+1, y=binsearch(e[i]);
		int pos=gr[y-1]-gr[x-1];

		if(pos)
			bst[node]=make_pair(0, node);
		else
		{
			bst[node]=make_pair(-1, node);
			for(int j=x; j<=y;)
			{
				int t=mr[j].second;
				if(bst[node].first<bst[t].first)
					bst[node]=bst[t];
				j=mr[j].first+1;
			}
			bst[node].first+=1;
		}

		mr[x]=make_pair(y, node);
		it=al.find(x);
		for(; *it <=y && it!=al.end();)
		{
			set<int>::iterator del=it; ++it;
			up(*del, -1); al.erase(del);
		}
		al.insert(x); up(x, 1);
	}

	pair<int, int> ans=make_pair(0, n+1);
	for(int i=1; i<=n+c; ++i)
	{
		if(ans.first<bst[i].first)ans=bst[i];
		else if(ans.first==bst[i].first && ans.second>bst[i].second)
			ans=bst[i];
	}
	return ans.second-1;
}