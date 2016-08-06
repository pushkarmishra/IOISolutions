#include <bits/stdc++.h>
#define rep(i, s, n) for(int i=s; i<=n; ++i)
#define rf freopen("in.in", "r", stdin)
#define ll long long
using namespace std;
ll ns=-2e18, zero=0;

struct node
{
	node*l, *r; ll sm, sd, mh;
	node(){l=r=NULL; sd=mh=0, sm=0;}
};
int n, qs, qe; ll val;
char ch;

void make_node(node* n, ll v, int x, int y)
{
	n->sm=v;
	n->sd = (y-x+1); n->sd*=v;
	n->mh=max(zero, n->sd);
}
void up(int x, int y, node* n)
{
	if(y<qs || qe<x) return;
	if(qs<=x && y<=qe)
	{
		make_node(n, val, x, y);
		return;
	}

	int m=(x+y)>>1;
	if(n->l==NULL) n->l=new node;
	if(n->r==NULL) n->r=new node;

	if(n->sm > ns)
	{
		if(n->l!=NULL) make_node(n->l, n->sm, x, m);
		if(n->r!=NULL) make_node(n->r, n->sm, m+1, y);
		n->sm=ns;
	}

	up(x, m, n->l); up(m+1, y, n->r);
	n->sd = (n->l!=NULL? n->l->sd:zero) + (n->r!=NULL? n->r->sd:zero);
	n->mh = max((n->l!=NULL? n->l->mh : zero), (n->r!=NULL? n->r->mh+n->l->sd : zero));
}

void qu(int x, int y, node* n)
{
	if(n->mh <= val) return void(val=y);
	if(n->mh > val && n->sm > ns)
		return void (val = x-1 + val/(n->sm));
	
	int m=(x+y)>>1;
	if(n->l->mh <= val) {val-=n->l->sd; qu(m+1, y, n->r);}
	else qu(x, m, n->l);
}

int main()
{
	//rf;
	cin >> n;
	cin >> ch;
	node *root=new node;
	
	while(ch!='E')
	{
		if(ch=='I')
		{
			scanf("%d %d %lld", &qs, &qe, &val);
			up(1, n, root);
		}
		else
		{
			scanf("%lld", &val);
			qu(1, n, root);
			printf("%lld\n", val);
		}

		cin >> ch;
	}
	return 0;
}