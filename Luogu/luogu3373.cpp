#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 1e5 + 10 , MAX_M = 1e5 + 10 ;

int mod ;

struct TREE {
	int num , ad , ti ;

	void times(ll k) {
		num = (num * k) % mod ;
		ad = (ad * k) % mod ; ti = (ti * k) % mod ;
	}
	void add(ll k , int x , int y) {
		int L = y - x + 1 ;
		num = (num + k * L) % mod ;
		ad = (ad + k) % mod ;
	}
}tree[MAX_N << 2] ;

int n , m , a[MAX_N] ;

void build(int t , int x , int y) {
	if (x == y) {
		TREE *p = &tree[t] ;
		p->num = a[x] ; p->ad = 0 ; p->ti = 1 ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build((t << 1) + 1 , mid + 1 , y) ;

	tree[t].ti = 1 ; tree[t].ad = 0 ;
	tree[t].num = (tree[t << 1].num + tree[(t << 1) + 1].num) % mod ;
}

void down(int t , int x , int y) {
	if (x == y) return ;
	TREE *p = &tree[t] ;

	int l = t << 1 , r = (t << 1) + 1 , mid = (x + y) >> 1 ;
	tree[l].times(p->ti) ; tree[r].times(p->ti) ;
	tree[l].add(p->ad , x , mid) ; tree[r].add(p->ad , mid + 1 , y) ;
	p->ti = 1 ; p->ad = 0 ;
}

void change(int t , int x , int y , int fx , int fy , int k , bool type) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		if (type) tree[t].add(k , x , y) ;
		else tree[t].times(k) ;

		return ;
	}
	down(t , x , y) ;

	int mid = (x + y) >> 1 ;
	change(t << 1 , x , mid , fx , fy , k , type) ;
	change((t << 1) + 1 , mid + 1 , y , fx , fy , k , type) ;

	tree[t].num = (tree[t << 1].num + tree[(t << 1) + 1].num) % mod ;
}

int query(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tree[t].num ;
	down(t , x , y) ;

	int mid = (x + y) >> 1 ,
		s1 = query(t << 1 , x , mid , fx , fy) ,
		s2 = query((t << 1) + 1 , mid + 1 , y , fx , fy) ;

	return (s1 + s2) % mod ;
}

int main() {
	scanf("%d %d %d" , &n , &m , &mod) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	build(1 , 1 , n) ;

	///

	for (int i = 0 ; i < m ; ++i) {
		int ty , x , y , k ;
		scanf("%d" , &ty) ;
		if (ty < 3) scanf("%d %d %d" , &x , &y , &k) ;
		else scanf("%d %d" , &x , &y) ;

		if (ty == 1) change(1 , 1 , n , x  , y , k , 0) ;
		else if (ty == 2) change(1 , 1 , n , x , y , k , 1) ;
		else printf("%d\n" , query(1 , 1 , n , x , y)) ;
	}

	return 0 ;
}
