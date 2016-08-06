#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN=1e6+10;
ll l[MAXN], r[MAXN];
int RR;

ll calc(int st, int en, int *X)
{
    st++, en++;
    int m=(st+en)>>1;
    ll fl= l[en]-l[m] - ((ll)X[m-1]-X[0])*(en-m);
    ll fr = r[st]-r[m] - ((ll)X[RR-1]-X[m-1])*(m-st);
    return fl+fr;
}

int besthub(int R, int L, int X[], ll B)
{
    RR=R;
    for(int c=1; c<=R; c++)
        l[c]=l[c-1] +(X[c-1]-X[0]);
    for(int c=R; c; c--)
        r[c]=r[c+1] + (X[R-1]-X[c-1]);

    int sol=0, now=0, st=0;
    for(int en=0; en < R; ++en)
    {
        while(calc(st, en, X)>B)
            st++;
        sol=max(sol, en-st+1);
    }
    return sol;
}

#define MAX_R  1000000

static int R, L;
static long long B;
static int X[MAX_R];
static int solution;

inline
void my_assert(int e) {if (!e) abort();}

static void read_input()
{
  int i;
  scanf("%d %d %lld",&R,&L,&B);
  for(i=0; i<R; i++)
    scanf("%d",&X[i]);
}

int main()
{
  int ans;
  read_input();
  ans = besthub(R,L,X,B);
  cout << ans << endl;

  return 0;
}
