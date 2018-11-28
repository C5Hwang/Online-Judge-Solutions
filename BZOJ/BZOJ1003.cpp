#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DBEUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_M = 20 + 10 , INF = 0x3f3f3f3f ;

struct Edge {
	int x , y , v ;
}eg[MAX_M * MAX_M] ;

int n , m , K , e , tot , ban[MAX_N] , dis[MAX_M] , f[MAX_N] ;

int work(int S) {
	for (int i = 1 ; i <= m ; ++i) dis[i] = INF ;
	dis[1] = 0 ;

	for (int i = 1 ; i < m ; ++i) {
		for (int j = 0 ; j < tot ; ++j) {
			Edge *p = &eg[j] ;
			if (((1 << p->x) & S) || ((1 << p->y) & S)) continue ;

			dis[p->y] = std::min(dis[p->x] + p->v , dis[p->y]) ;
		}
	}

	return dis[m] ;
}

int main() {
	scanf("%d %d %d %d" , &n , &m , &K , &e) ;
	for (int i = 0 ; i < e ; ++i) {
		int a , b , v ;
		scanf("%d %d %d" , &a , &b , &v) ;

		eg[tot++] = (Edge){a , b , v} ;
		eg[tot++] = (Edge){b , a , v} ;
	}

	scanf("%d" , &e) ;
	for (int i = 0 ; i < e ; ++i) {
		int a , x , y ;
		scanf("%d %d %d" , &a , &x , &y) ;

		for (int j = x ; j <= y ; ++j) ban[j] |= (1 << a) ;
	}

	///

	f[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		f[i] = INF ;

		int s = 0 ;
		for (int j = i ; j ; --j) {
			s |= ban[j] ;

			int d = work(s) , tmp ;
			if (d == INF) continue ;

			tmp = f[j - 1] + d * (i - j + 1) + (j != 1 ? K : 0) ;
			f[i] = std::min(f[i] , tmp) ;
		}
	}

	printf("%d\n" , f[n]) ;

	return 0 ;
}