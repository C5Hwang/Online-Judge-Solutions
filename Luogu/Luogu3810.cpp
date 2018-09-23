#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 , MAX_K = 2e5 + 10 ;

struct data {
	int a , b , c , idx , val ;
}query[MAX_N] , temp[MAX_N] ;

int n , k , tot , pl[MAX_N] , ans[MAX_N] , cnt[MAX_N] , BIT[MAX_K] ;

///

bool cmp(data x , data y) {
	return x.a < y.a || x.a == y.a && x.b < y.b || x.a == y.a && x.b == y.b && x.c < y.c ;
}

bool equal(data *x , data *y) {
	return x->a == y->a && x->b == y->b && x->c == y->c ;
}

///

int lowbit(int x) {return x & (-x) ;}

void add(int x , int a) {
	for (; x <= k ; x += lowbit(x)) BIT[x] += a ;
}

int sum(int x) {
	int s = 0 ;
	for (; x > 0 ; x -= lowbit(x)) s += BIT[x] ;
	return s ;
}

void init(int x) {
	for (; x <= k ; x += lowbit(x)) BIT[x] = 0 ;
}

///

void cdq(int x , int y) {
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	cdq(x , mid) ; cdq(mid + 1 , y) ;

	int p1 = x , p2 = mid + 1 , t = 0 ;
	while (p1 <= mid && p2 <= y) {
		if (query[p1].b <= query[p2].b) {
			data *p = &query[p1++] ;
			add(p->c , p->val) ;
			temp[t++] = *p ;
		}
		else {
			data *p = &query[p2++] ;
			ans[p->idx] += sum(p->c) ;
			temp[t++] = *p ;
		}
	}

	for (; p1 <= mid ; ++p1) temp[t++] = query[p1] ;
	for (; p2 <= y ; ++p2) {
		data *p = &query[p2] ;
		ans[p->idx] += sum(p->c) ;
		temp[t++] = *p ;
	}

	for (int i = 0 ; i < t ; ++i) {
		init(temp[i].c) ;
		query[i + x] = temp[i] ;
	}
}

///

int main() {
	scanf("%d %d" , &n , &k) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d %d %d" , &query[i].a , &query[i].b , &query[i].c) , query[i].idx = i ;
	
	///
	
	std::sort(query + 1 , query + 1 + n , cmp) ;

	int c = 1 ; tot = 1 ;
	data *last = &query[1] ;
	pl[last->idx] = 1 ; last->idx = 1 ;

	for (int i = 2 ; i <= n + 1 ; ++i) {
		data *p = &query[i] ;
		if (equal(p , last)) pl[p->idx] = tot , ++c ;
		else {
			last->val = c ;
			ans[last->idx] += c - 1 ;

			query[++tot] = query[i] ;
			last = &query[tot] ;
			pl[last->idx] = tot ; last->idx = tot ; c = 1 ;
		}
	}
	--tot ;

	///
	
	cdq(1 , tot) ;
	for (int i = 1 ; i <= n ; ++i) ++cnt[ans[pl[i]]] ;
	for (int i = 0 ; i < n ; ++i) printf("%d\n" , cnt[i]) ;

	return 0 ;
}
