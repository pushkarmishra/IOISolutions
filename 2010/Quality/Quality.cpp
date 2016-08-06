#include <bits/stdc++.h>
#include "grader.h"
using namespace std;
const int mx=3010;

static int in[mx][mx], cum[mx][mx]={0};
int r, c, h, w;

void create_arr(int m)
{
	for(int i=1; i<=r; i++)
		for(int j=1; j<=c; ++j)
			cum[i][j]=cum[i][j-1]+cum[i-1][j]-cum[i-1][j-1]
					  +((in[i][j]>m)? 1: -1);
}
int get(int r1, int c1, int r2, int c2)
{
	return cum[r2][c2]-cum[r1-1][c2]-cum[r2][c1-1]+cum[r1-1][c1-1];
}

int process(int m)
{
	create_arr(m);
	int mn=INT_MAX;
	for(int i=1; i<=r; ++i)
		for(int j=1; j<=c; ++j)
			if(i-h+1>0 && j-w+1>0)
				mn=min(mn, get(i-h+1, j-w+1, i, j));
	
	return (mn>0)? 0:1;
}

int rectangle(int R, int C, int H, int W, int Q[3001][3001])
{
	r=R, c=C, h=H, w=W;
	for(int i=1; i<=r; ++i)
		for(int j=1; j<=c; ++j)
			in[i][j] = Q[i-1][j-1];

	int s=1, e=r*c;
	while(s<=e)
	{
		int m=(s+e)>>1;
		int tmp=process(m);
		if(!tmp)s=m+1;
		else e=m-1;
	}
	
	return s;
}