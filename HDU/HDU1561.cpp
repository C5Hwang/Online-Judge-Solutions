#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num ; Link *next ;
}list[MAX_N] ;

bool in[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , v[MAX_N] , f[MAX_N][MAX_N] ;

void find(int x) {
	for (int j = 1 ; j <= m ; ++j) f[x][j] = -INF ;
	f[x][0] = 0 ; f[x][1] = v[x] ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ; find(nx) ;

		for (int j = m ; j > 0 ; --j) {
			int d = x ? 0 : 1 ;
			for (int k = 0 ; k < j + d ; ++k)
				f[x][j] = std::max(f[x][j] , f[x][j - k] + f[nx][k]) ;
		}
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(f , 0 , sizeof(f)) ;
	memset(in , 0 , sizeof(in)) ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	while (n > 0 || m > 0) {
		init() ;

		for (int i = 1 ; i <= n ; ++i) {
			int x ; scanf("%d %d" , &x , &v[i]) ;

			if (x == i) x = 0 ;
			if (x > 0) in[i] = 1 , ins(x , i) ;
		}

		///
		
		for (int i = 1 ; i <= n ; ++i)
			if (!in[i]) ins(0 , i) ;
		find(0) ;
		
		printf("%d\n" , f[0][m]) ;

		scanf("%d %d" , &n , &m) ;
	}

	return 0 ;
}
