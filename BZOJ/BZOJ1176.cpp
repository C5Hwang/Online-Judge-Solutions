#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 2e6 + 10 , MAX_Q = 2e5 + 10 ;

struct data {
	int type , x , y , val ;
}query[MAX_Q << 2] , temp[MAX_Q << 2] ;

int s , w , tot , cnt , ans[MAX_Q] , BIT[MAX_N] ;

///

int lowbit(int x) {return x & (-x) ;}

void add(int x , int a) {
	for (; x <= w ; x += lowbit(x)) BIT[x] += a ;
}

int sum(int x) {
	int s = 0 ;
	for (; x > 0 ; x -= lowbit(x)) s += BIT[x] ;
	return s ;
}

void init(int x) {
	for (; x <= w ; x += lowbit(x)) BIT[x] = 0 ;
}

///

void cdq(int x , int y) {
	if (x == y) return ;
	int mid = (x + y) >> 1 , p1 = x , p2 = mid + 1 , o = 0 ;
	cdq(x , mid) ; cdq(mid + 1 , y) ;

	while (p1 <= mid && p2 <= y) {
		if (query[p1].x <= query[p2].x) {
			data *p = &query[p1++] ;
			temp[o++] = *p ;
			if (p->type == 1) add(p->y , p->val) ;
		}
		else {
			data *p = &query[p2++] ;
			temp[o++] = *p ;
			if (p->type == 2) ans[p->val] += sum(p->y) ;
			else if (p->type == 3) ans[p->val] -= sum(p->y) ;
		}
	}

	for (; p1 <= mid ; ++p1) temp[o++] = query[p1] ;
	for (; p2 <= y ; ++p2) {
		data *p = &query[p2] ;
		temp[o++] = *p ;
		if (p->type == 2) ans[p->val] += sum(p->y) ;
		else if (p->type == 3) ans[p->val] -= sum(p->y) ;
	}

	for (int i = 0 ; i < o ; ++i) {
		init(temp[i].y) ;
		query[i + x] = temp[i] ;
	}
}

///

int main() {
	int ty ;
	scanf("%d %d %d" , &s , &w , &ty) ;
	while (ty != 3) {
		int x1 , y1 , x2 , y2 , a ;
		if (ty == 1) {
			scanf("%d %d %d" , &x1 , &y1 , &a) ;
			query[++tot] = (data){1 , x1 , y1 , a} ;
		}
		else {
			scanf("%d %d %d %d" , &x1 , &y1 , &x2 , &y2) ;
			query[++tot] = (data){2 , x2 , y2 , cnt} ;

			if (x1 - 1 > 0) query[++tot] = (data){3 , x1 - 1 , y2 , cnt} ;
			if (y1 - 1 > 0) query[++tot] = (data){3 , x2 , y1 - 1 , cnt} ;
			if (x1 - 1 > 0 && y1 - 1 > 0) query[++tot] = (data){2 , x1 - 1 , y1 - 1 , cnt} ;
			ans[cnt++] = (y2 - y1 + 1) * (x2 - x1 + 1) * s ;
		}

		scanf("%d" , &ty) ;
	}

	///
	
	cdq(1 , tot) ;
	for (int i = 0 ; i < cnt ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}
