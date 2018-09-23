#include <stdio.h>
#include <stdlib.h>

#define db double
#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db INF = 1e100 , eps = 1e-9 ;
const int MAX_N = 1e3 + 10 , MAX_M = 1e4 + 10 ;

int n , m ;
db A[MAX_N][MAX_M] ;

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
	for (int i = 0 ; i <= m ; ++i) A[l][i] /= tmp ;

	for (int i = 0 ; i <= n ; ++i) {
		if (!dcmp(A[i][e]) || i == l) continue ;

		db k = A[i][e] ; A[i][e] = 0 ;
		for (int j = 0 ; j <= m ; ++j) A[i][j] += k * A[l][j] ;
	}
}

void simplex() {
	for (;;) {
		int x = 0 , y = 0 ;

		for (int i = 1 ; i <= m ; ++i) if (dcmp(A[0][i]) > 0) {y = i ; break ;}
		if (!y) return ;

		db dmin = INF ;
		for (int i = 1 ; i <= n ; ++i) {
			if (dcmp(A[i][y]) >= 0) continue ;

			db tmp = -A[i][0] / A[i][y] ;
			if (dcmp(tmp - dmin) < 0) dmin = tmp , x = i ;
		}

		pivot(x , y) ;
	}
}

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i) A[i][0] = read() ;
	for (int i = 1 ; i <= m ; ++i) {
		int x , y , d ; x = read() ; y = read() ; d = read() ;

		for (int j = x ; j <= y ; ++j) A[j][i] = -1 ;
		A[0][i] = d ;
	}

	///

	simplex() ;
	printf("%lld\n" , (ll)(A[0][0] + 0.5)) ;

	return 0 ;
}