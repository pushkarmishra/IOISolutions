#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <stack>
#include <cassert>
#include <set>
#include <climits>
#include <string>
#include <cstring>
#include "Game.h"
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("in.in", "r", stdin)
using namespace std;
#define ll long long

ll v;
int q, ch, qx1, qy1, qx2, qy2, mx, my, chk;
struct node
{
	node *lo, *ro, *li, *ri;
	ll gcd;
	node(node* put)
	{
		gcd=0;
		lo=ro=ri=li=put;
	}
};
node *root, *dummy;

void upc(node* &cur, int x, int y, node* &l, node* &r)
{
	if(y<qy1 or qy2<x) return;
	if(cur == dummy) cur=new node(dummy);
	
	l=(l==NULL)? dummy:l; r=(r==NULL)? dummy:r;
	cur->lo=(l!=dummy)? l:dummy; cur->ro=(r!=dummy)? r:dummy;

	if(qy1<=x and y<=qy2)
	{
		cur->gcd=(chk)? v: __gcd(cur->lo->gcd, cur->ro->gcd);
		return;
	}

	int m=(x+y)>>1;
	upc(cur->li, x, m, l->li, r->li); upc(cur->ri, m+1, y, l->ri, r->ri);

	cur->gcd = __gcd(cur->li->gcd, cur->ri->gcd);
}
void upr(node* &cur, int x, int y)
{
	if(y<qx1 or qx2<x) return;
	if(cur == dummy) cur=new node(dummy);

	if(qx1<=x and y<=qx2)
	{
		chk=1; upc(cur, 1, my, cur->lo, cur->ro);
		return;
	}

	int m=(x+y)>>1;
	upr(cur->lo, x, m); upr(cur->ro, m+1, y);

	chk=0; upc(cur, 1, my, cur->lo, cur->ro);
}

ll quc(node* &cur, int x, int y)
{
	if(y<qy1 or qy2<x or cur==dummy) return 0;
	if(qy1<=x and y<=qy2)
		return cur->gcd;
	
	int m=(x+y)>>1;
	return __gcd(quc(cur->li, x, m), quc(cur->ri, m+1, y));
}
ll qur(node* &cur, int x, int y)
{
	if(y<qx1 || qx2<x || cur==dummy) return 0;
	if(qx1<=x && y<=qx2)
		return quc(cur, 1, my);
	
	int m=(x+y)>>1;
	return __gcd(qur(cur->lo, x, m), qur(cur->ro, m+1, y));
}

void init(int R, int C)
{
	mx=R, my=C;
	dummy = new node(NULL);
	root = new node(dummy);
}
void update(int P, int Q, long long K)
{
	qx1=P+1, qy1=Q+1, v=K;
	qx2=qx1, qy2=qy1;
	upr(root, 1, mx);
}
long long calculate(int P, int Q, int U, int V)
{
	qx1=P+1, qy1=Q+1, qx2=U+1, qy2=V+1;
	return qur(root, 1, mx);
}