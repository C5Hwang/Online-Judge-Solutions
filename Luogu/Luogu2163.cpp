#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e5 + 10 , MAX_NUM = 1e7 + 10 ;

struct data {
	int x , y ;
}pt[MAX_N] ;
struct Query {
	int x , y , idx , ty ;
}query[MAX_N << 2] ;

int n , m , inf , cnt , ans[MAX_N] , BIT[MAX_NUM] ;

///

bool cmp1(Query a , Query b) {
	return a.x < b.x ;
}

bool cmp2(data a , data b) {
	return a.x < b.x ;
}

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

///

int main() {
	inf = -1 ;
	int MINX = MAX_NUM , MINY = MAX_NUM ;
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d %d" , &pt[i].x , &pt[i].y) ;
		++pt[i].x ; ++pt[i].y ;

		MINX = std::min(MINX , pt[i].x) ;
		MINY = std::min(MINY , pt[i].y) ;
		inf = std::max(inf , pt[i].y) ;
	}
	for (int i = 0 ; i < m ; ++i) {
		int x1 , x2 , y1 , y2 ;
		scanf("%d %d %d %d" , &x1 , &y1 , &x2 , &y2) ;
		++x1 ; ++y1 ; ++x2 ; ++y2 ;
		inf = std::max(inf , y1) ; inf = std::max(inf , y2) ;

		query[cnt++] = (Query){x2 , y2 , i , 1} ;
		if (y1 - 1 >= MINY) query[cnt++] = (Query){x2 , y1 - 1 , i , -1} ;
		if (x1 - 1 >= MINX) query[cnt++] = (Query){x1 - 1 , y2 , i , -1} ;
		if (x1 - 1 >= MINX && y1 - 1 >= MINY) query[cnt++] = (Query){x1 - 1 , y1 - 1 , i , 1} ;	
	}

	///
	
	std::sort(query + 0 , query + cnt , cmp1) ;
	std::sort(pt + 0 , pt + n , cmp2) ;

	int p = 0 ;
	for (int i = 0 ; i < cnt ; ++i) {
		Query *nt = &query[i] ;
		for (; p < n && pt[p].x <= nt->x ; ++p) add(pt[p].y) ;

		ans[nt->idx] += nt->ty * sum(nt->y) ;
	}

	for (int i = 0 ; i < m ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}
