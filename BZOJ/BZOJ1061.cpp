#include <stdio.h>
#include <stdlib.h>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db INF = 1e100 , eps = 1e-9 ;
const int MAX_N = 1e3 + 10 , MAX_M = 1e4 + 10 ;

int n , m ;
db A[MAX_M][MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ; 
}

int dcmp(db x) {
	if (x > eps) return 1 ;
	else if (x < -eps) return -1 ;
	else return 0 ;
}

void pivot(int l , int e) {
	db tmp = -A[l][e] ; A[l][e] = -1 ;
	for (int i = 0 ; i <= n ; ++i) A[l][i] /= tmp ;

	for (int i = 0 ; i <= m ; ++i) {
		if (!dcmp(A[i][e]) || i == l) continue ;

		db k = A[i][e] ; A[i][e] = 0 ;
		for (int j = 0 ; j <= n ; ++j) A[i][j] += k * A[l][j] ;
	}
}

void simplex() {
	for (;;) {
		int x = 0 , y = 0 ;

		for (int i = 1 ; i <= n ; ++i) if (dcmp(A[0][i]) > 0) {y = i ; break ;}
		if (!y) return ;

		db dmin = INF ;
		for (int i = 1 ; i <= m ; ++i) {
			if (dcmp(A[i][y]) >= 0) continue ;

			db tmp = -A[i][0] / A[i][y] ;
			if (dcmp(tmp - dmin) < 0) dmin = tmp , x = i ;
		}

		pivot(x , y) ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) A[0][i] = read() ;
	for (int i = 1 ; i <= m ; ++i) {
		int x , y , c ; x = read() ; y = read() ; c = read() ;

		for (int j = x ; j <= y ; ++j) A[i][j] = -1 ;
		A[i][0] = c ;
	}

	///

	simplex() ;
	printf("%d\n" , (int)(A[0][0] + 0.5)) ;

	return 0 ;
}