#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e5 + 10 , MAX_NUM = 1e7 + 10 ;

struct data {
	int type , x , y , idx ;
}query[MAX_N << 3] , temp[MAX_N << 3] ;

int n , m , tot , inf , ans[MAX_N] , BIT[MAX_NUM] ;

///

int lowbit(int x) {return x & (-x) ;}

void add(int x) {
	for (; x <= inf ; x += lowbit(x)) ++BIT[x] ;
}

int sum(int x) {
	int s = 0 ;
	for (; x > 0 ; x -= lowbit(x)) s += BIT[x] ;
	return s ;
}

void init(int x) {
	for (; x <= inf ; x += lowbit(x)) BIT[x] = 0 ;
}

///

void cdq(int x , int y) {
	if (x == y) return ;

	int mid = (x + y) >> 1 , p1 = x , p2 = mid + 1 , t = 0 ;
	cdq(x , mid) ; cdq(mid + 1 , y) ;

	while (p1 <= mid && p2 <= y) {
		if (query[p1].x <= query[p2].x) {
			data *p = &query[p1++] ;
			if (p->type == 1) add(p->y) ;
			temp[t++] = *p ;
		}
		else {
			data *p = &query[p2++] ;
			if (p->type == 2) ans[p->idx] += sum(p->y) ;
			else if (p->type == 3) ans[p->idx] -= sum(p->y) ;
			temp[t++] = *p ;
		}
	}

	for (; p1 <= mid ; ++p1) temp[t++] = query[p1] ;
	for (; p2 <= y ; ++p2) {
		data *p = &query[p2] ;
		if (p->type == 2) ans[p->idx] += sum(p->y) ;
		else if (p->type == 3) ans[p->idx] -= sum(p->y) ;
		temp[t++] = *p ;
	}

	for (int i = 0 ; i < t ; ++i) {
		init(temp[i].y) ;
		query[i + x] = temp[i] ;
	}
}

///

int main() {
	int MINX , MINY ;
	MINX = MINY = MAX_NUM ; inf = -1 ;

	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		int nx , ny ;
		scanf("%d %d" , &nx , &ny) ;
		++nx ; ++ny ;

		MINX = std::min(MINX , nx) ;
		MINY = std::min(MINY , ny) ;
		inf = std::max(inf , ny) ;
		query[++tot] = (data){1 , nx , ny , 0} ;
	}
	for (int i = 0 ; i < m ; ++i) {
		int x1 , y1 , x2 , y2 ;
		scanf("%d %d %d %d" , &x1 , &y1 , &x2 , &y2) ;
		++x1 ; ++y1 ; ++x2 ; ++y2 ;

		inf = std::max(inf , y1) ; inf = std::max(inf , y2) ;
		query[++tot] = (data){2 , x2 , y2 , i} ;
		if (x1 - 1 >= MINX) query[++tot] = (data){3 , x1 - 1 , y2 , i} ;
		if (y1 - 1 >= MINY) query[++tot] = (data){3 , x2 , y1 - 1 , i} ;
		if (x1 - 1 >= MINX && y1 - 1 >= MINY) query[++tot] = (data){2 , x1 - 1 , y1 - 1 , i} ;
	}

	///

	cdq(1 , tot) ;
	for (int i = 0 ; i < m ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}
