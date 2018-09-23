#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 5e5 + 10 , MAX_M = 2e5 + 10 ;

struct data {
	int type , x , y , val ;
}query[MAX_M << 2] , temp[MAX_M << 2] ;

int n , m , qt , ans[MAX_M] , BIT[MAX_N] ;

///

int lowbit(int x) {return x & (-x) ;}

void add(int x , int a) {
	for (; x <= n ; x += lowbit(x)) BIT[x] += a ;
}

int sum(int x) {
	int s = 0 ;
	for (; x > 0 ; x -= lowbit(x)) s += BIT[x] ;
	return s ;
}

void init(int x) {
	for (; x <= n ; x += lowbit(x)) BIT[x] = 0 ;
}

///

void cdq(int x , int y) {
	if (x == y) return ;
	int mid = (x + y) >> 1 ;
	cdq(x , mid) ; cdq(mid + 1 , y) ;

	int p1 = x , p2 = mid + 1 , t = 0 ;
	while (p1 <= mid && p2 <= y) {
		if (query[p1].x <= query[p2].x) {
			data *p = &query[p1++] ;
			if (p->type == 1) add(p->y , p->val) ;
			temp[t++] = *p ;
		}
		else {
			data *p = &query[p2++] ;
			if (p->type == 2) ans[p->val] += sum(p->y) ;
			else if (p->type == 3) ans[p->val] -= sum(p->y) ;
			temp[t++] = *p ;
		}
	}

	for (; p1 <= mid ; ++p1) temp[t++] = query[p1] ;
	for (; p2 <= y ; ++p2) {
		data *p = &query[p2] ;
		if (p->type == 2) ans[p->val] += sum(p->y) ;
		else if (p->type == 3) ans[p->val] -= sum(p->y) ;
		temp[t++] = *p ;
	}

	for (int i = 0 ; i < t ; ++i) {
		init(temp[i].y) ;
		query[i + x] = temp[i] ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (; ;) {
		int ty , x1 , y1 , x2 , y2 , a ;
		scanf("%d" , &ty) ;
		if (ty == 3) break ;

		if (ty == 1) {
			scanf("%d %d %d" , &x1 , &y1 , &a) ;
			query[++m] = (data){1 , x1 , y1 , a} ;
		}
		else {
			scanf("%d %d %d %d" , &x1 , &y1 , &x2 , &y2) ;
			query[++m] = (data){2 , x2 , y2 , qt} ;
			if (y1 - 1 > 0) query[++m] = (data){3 , x2 , y1 - 1 , qt} ;
			if (x1 - 1 > 0) query[++m] = (data){3 , x1 - 1 , y2 , qt} ;
			if (x1 - 1 > 0 && y1 - 1 > 0) query[++m] = (data){2 , x1 - 1 , y1 - 1 , qt} ;

			++qt ;
		}
	}

	///
	
	cdq(1 , m) ;
	for (int i = 0 ; i < qt ; ++i)
		printf("%d\n" , ans[i]) ;

	return 0 ;
}
