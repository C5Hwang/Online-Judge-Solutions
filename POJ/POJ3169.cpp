#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1000 + 10 , MAX_M = 20000 + 10 , INF = 0x3f3f3f3f ;

struct Edge {
	int x , y , v ;
}e[MAX_M + MAX_N] ;

int n , cur , e1 , e2 , dis[MAX_N] ;

void ins(int a , int b , int c) {
	e[cur].x = a ; e[cur].y = b ; e[cur++].v = c ;
}

int main() {
	scanf("%d %d %d" , &n , &e1 , &e2) ;
	for (int i = 0 ; i < e1 ; ++i) {
		int x , y , c ;
		scanf("%d %d %d" , &x , &y , &c) ;
		ins(x , y , c) ;
	}
	for (int i = 0 ; i < e2 ; ++i) {
		int x , y , c ;
		scanf("%d %d %d" , &x , &y , &c) ;
		ins(y , x , -c) ;
	}
	for (int i = n ; i > 1 ; --i) ins(i , i - 1 , 0) ;

	///
	
	for (int i = 1 ; i <= n ; ++i) dis[i] = INF ;
	dis[1] = 0 ;

	bool ok = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		ok = 0 ;

		for (int j = 0 ; j < cur ; ++j) {
			int a = e[j].x , b = e[j].y , c = e[j].v ;
			if (dis[a] + c < dis[b]) dis[b] = dis[a] + c , ok = 1 ;
		}

		if (!ok) break ;
	}

	if (ok) printf("-1\n") ;
	else if (dis[n] == INF) printf("-2\n") ;
	else printf("%d\n" , dis[n]) ;
}
