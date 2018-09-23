#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 , INF = 0x7FFFFFFF ;

struct Treap {
	int num , s , r ;
	Treap *ch[2] ;

	int cmp(int x) {
		return x <= num ? 0 : 1 ;
	}
}tre[MAX_N] ;

Treap *root ;
int n , cur ;

void update(Treap *rt) {
	int sum = 1 ;
	for (int i = 0 ; i < 2 ; ++i)
		sum += rt->ch[i] ? rt->ch[i]->s : 0 ;

	rt->s = sum ;
}

void rotate(Treap *&rt , int d) {
	Treap *son = rt->ch[d^1] ;

	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
	update(rt->ch[d]) ; update(rt) ;
}

void ins(Treap *&rt , int a) {
	if (!rt) {
		rt = &tre[cur++] ;
		rt->num = a ; rt->s = 1 ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return ;
	}

	int d = rt->cmp(a) ;

	ins(rt->ch[d] , a) ; update(rt) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

void del(Treap *&rt , int a) {
	if (rt->num == a) {
		if (!rt->ch[0]) rt = rt->ch[1] ;
		else if (!rt->ch[1]) rt = rt->ch[0] ;
		else {
			int d = rt->ch[0]->r < rt->ch[1]->r ? 1 : 0 ;

			rotate(rt , d) ;
			del(rt->ch[d] , a) ;
		}

		if (rt) update(rt) ;

		return ;
	}

	int d = rt->cmp(a) ;
	del(rt->ch[d] , a) ; update(rt) ;
}

int getrank(Treap *rt , int a) {
	if (!rt) return 0 ;

	int r = rt->ch[0] ? rt->ch[0]->s + 1 : 1 ,
	    d = rt->cmp(a) ;

	return getrank(rt->ch[d] , a) + r * d ;
}

int getnum(Treap *rt , int a) {
	int s = rt->ch[0] ? rt->ch[0]->s + 1 : 1 ;

	if (a == s) return rt->num ;
	else if (a > s) return getnum(rt->ch[1] , a - s) ;
	else return getnum(rt->ch[0] , a) ;
}

int getfront(Treap *rt , int a) {
	if (!rt) return -INF ;

	if (rt->num < a) return std::max(rt->num , getfront(rt->ch[1] , a)) ;
	else return getfront(rt->ch[0] , a) ;
}

int getbehind(Treap *rt , int a) {
	if (!rt) return INF ;

	if (rt->num > a) return std::min(rt->num , getbehind(rt->ch[0] , a)) ;
	else return getbehind(rt->ch[1] , a) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int q , num , res ;
		scanf("%d %d" , &q , &num) ;

		if (q == 1) ins(root , num) ;
		else if (q == 2) del(root , num) ;
		else if (q == 3) res = getrank(root , num) + 1 ;
		else if (q == 4) res = getnum(root , num) ;
		else if (q == 5) res = getfront(root , num) ;
		else if (q == 6) res = getbehind(root , num) ;

		if (q > 2) printf("%d\n" , res) ;
	}

	return 0 ;
}
