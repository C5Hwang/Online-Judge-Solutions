#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 ;
const long long INF = 0x7FFFFFFF ;

struct Point {
	int bh ;
	long long x , y ;
}t[MAX_N] ;
struct Treap {
	long long num ;
	int bh , r ;
	Treap *ch[2] ;

	int cmp(int p , long long x) {
		if (num != x) return num < x ;
		else return bh < p ;
	}
}tre[MAX_N] ;

///

int n , c , cur ;
Treap *root , *tep ;
int fa[MAX_N] , sum[MAX_N] ;

///

void rotate(Treap *&rt , int d) {
	Treap *son = rt->ch[d^1] ;
	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
}

void ins(Treap *&rt , long long x , int p) {
	if (!rt) {
		rt = &tre[cur++] ;
		rt->num = x ; rt->bh = p ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return ;
	}

	int d = rt->cmp(p , x) ;
	ins(rt->ch[d] , x , p) ;

	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

void del(Treap *&rt , int p , long long x) {
	if (rt->bh == p) {
		if (!rt->ch[0]) rt = rt->ch[1] ;
		else if (!rt->ch[1]) rt = rt->ch[0] ;
		else {
			int d = rt->ch[0]->r < rt->ch[1]->r ? 1 : 0 ;
			rotate(rt , d) ; del(rt->ch[d] , p , x) ;
		}

		return ;
	}

	int d = rt->cmp(p , x) ;
	del(rt->ch[d] , p , x) ;
}

void FindMIN(Treap *rt , long long x) {
	if (!rt) return ;
	int d = rt->num <= x ? 1 : 0 ;

	if (rt->num <= x) tep = rt ;
	FindMIN(rt->ch[d] , x) ;
}

void FindMAX(Treap *rt , long long x) {
	if (!rt) return ;
	int d = rt->num > x ? 0 : 1 ;

	if (rt->num > x) tep = rt ;
	FindMAX(rt->ch[d] , x) ;
}

///

bool cmp(Point a , Point b) {return a.x < b.x ;}

int FindSet(int x) {return fa[x] == -1 ? x : (fa[x] = FindSet(fa[x])) ;}

void merge(int x , int y) {
	if (sum[x] > sum[y]) std::swap(x , y) ;

	int fx = FindSet(x) , fy = FindSet(y) ;

	if (fx == fy) return ;
	sum[fx] += sum[fy] ; fa[fy] = fx ;
}

///

int main() {
	memset(fa , -1 , sizeof(fa)) ;

	scanf("%d %d" , &n , &c) ;
	for (int i = 0 ; i < n ; ++i) {
		long long a , b ; scanf("%lld %lld" , &a , &b) ;
		t[i].x = a - b ; t[i].y = a + b ; t[i].bh = i ; sum[i] = 1 ;
	}

	///
	
	std::sort(t + 0 , t + n , cmp) ;
	int L = 0 ;
	ins(root , -INF , -1) ; ins(root , INF , -1) ;
	ins(root , t[0].y , t[0].bh) ;

	for (int i = 1 ; i < n ; ++i) {
		while (t[i].x - t[L].x > c) del(root , t[L].bh , t[L].y) , ++L ;

		Treap *MIN = NULL , *MAX = NULL ;
		FindMIN(root , t[i].y) ; MIN = tep ;
	   	FindMAX(root , t[i].y) ; MAX = tep ;
		if (abs(MIN->num - t[i].y) <= c) merge(MIN->bh , t[i].bh) ;
		if (abs(MAX->num - t[i].y) <= c) merge(MAX->bh , t[i].bh) ;

		ins(root , t[i].y , t[i].bh) ;
	}

	///
	
	int res = 0 , ms = 1 ;
	for (int i = 0 ; i < n ; ++i)
		if (fa[i] == -1) ++res , ms = std::max(ms , sum[i]) ;

	printf("%d %d\n" , res , ms) ;

	return 0 ;
}
