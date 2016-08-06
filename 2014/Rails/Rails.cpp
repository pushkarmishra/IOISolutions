#include <bits/stdc++.h>
#include "grader.h"
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define rf freopen("in.in", "r", stdin)
using namespace std;
#define ff first
#define ss second

int D[5010][5010];
pair<int, int> ew[5010];
vector<int> r, lv;

int dist(int u, int v)
{
	if (D[u][v] or D[v][u]) return max(D[u][v], D[v][u]);
	return D[u][v] = D[v][u] = getDistance(u, v);
}

void findLocation(int n, int first, int location[], int stype[])
{
	location[0]=first, stype[0]=1;
	
	rep(i, 1, n - 1)
		ew[i] = make_pair(dist(0, i), i);
	sort(ew + 1, ew + n);
	
	location[ew[1].ss] = first + ew[1].ff;
	stype[ew[1].ss] = 2;
	r.push_back(ew[1].ss); lv.push_back(0);
	
	int L = 0, R = ew[1].ss;
	rep(i, 2, n - 1)
	{
		int y = ew[i].ss;
		int Ry = dist(R, y);
		int Y0 = ew[i].ff;
		int D01 = ew[1].ff;
		int R1 = dist(R, 0) - D01;
		
		if(Ry > dist(R, 0) and Y0 + R1 + R1 == dist(0, R) + Ry)
		{
			bool found = false;
			rep(j, 0, lv.size()-1)
			{
				int l = lv[j];
				int ly = dist(L, y) - (location[l] - location[L]);
				int l1 = location[ew[1].ss]-location[l];

				if(Y0 == D01 + (l1 + ly))
				{
					found = true;
					location[y] = location[l] + ly;
					stype[y] = 2;
				}
				if (found) break;
			}
			if (not found)
			{
				stype[y] = 1;
				location[y] = location[R] - Ry;
				lv.push_back(y);
				L = y;
			}
		}
		else
		{
			bool found = false;
			rep(j, 0, r.size()-1)
			{
				int r0 = location[r[j]]-first;
				int Rr = location[R]-location[r[j]];

				if(Y0 == r0 + (Ry - Rr))
				{
					found = true;
					location[y] = location[R] - Ry;
					stype[y] = 1;
				}
				if (found) break;
			}
			if (not found)
			{
				stype[y] = 2;
				location[y] = first + Y0;
				r.push_back(y);
				R = y;
			}
		}
	}
}