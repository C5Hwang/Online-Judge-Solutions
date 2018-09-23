#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 40 + 5 ;
const db INF = 1e100 , eps = 1e-9 ;

int n , m , t , id[MAX_N] ;
db A[MAX_N][MAX_N] , xi[MAX_N] ;

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
	std::swap(id[l + n] , id[e]) ;

	db tmp = -A[l][e] ; A[l][e] = -1 ;
	for (int i = 0 ; i <= n ; ++i) A[l][i] /= tmp ;

	for (int i = 0 ; i <= m ; ++i) {
		if (!dcmp(A[i][e]) || i == l) continue ;

		db k = A[i][e] ; A[i][e] = 0 ;
		for (int j = 0 ; j <= n ; ++j) A[i][j] += k * A[l][j] ;
	}
}

bool init() {
	for (int i = 1 ; i <= n ; ++i) id[i] = i ;

	for (;;) {
		int x = 0 , y = 0 ;

		for (int i = 1 ; i <= m ; ++i) if (dcmp(A[i][0]) < 0 && (!x || (rand() & 1))) x = i ;
		if (!x) return 1 ;

		for (int i = 1 ; i <= n ; ++i) if (dcmp(A[x][i]) > 0 && (!y || (rand() & 1))) y = i ;
		if (!y) return 0 ;

		pivot(x , y) ;
	}
}

bool simplex() {
	for (;;) {
		int x = 0 , y = 0 ;

		for (int i = 1 ; i <= n ; ++i) if (dcmp(A[0][i]) > 0) {y = i ; break ;}
		if (!y) return 1 ;

		db mind = INF ;
		for (int i = 1 ; i <= m ; ++i) {
			if (dcmp(A[i][y]) >= 0) continue ;

			db tmp = -A[i][0] / A[i][y] ;
			if (dcmp(tmp - mind) < 0) x = i , mind = tmp ;
		}
		if (!x) return 0 ;

		pivot(x , y) ;
	}
}

int main() {
	srand(19260817) ;

	n = read() ; m = read() ; t = read() ;
	for (int i = 1 ; i <= n ; ++i) A[0][i] = read() ;
	for (int i = 1 ; i <= m ; ++i) {
		for (int j = 1 ; j <= n ; ++j) A[i][j] = -read() ;
		A[i][0] = read() ;
	}

	///

	if (!init()) printf("Infeasible\n") ;
	else if (!simplex()) printf("Unbounded\n") ;
	else {
		printf("%0.9lf\n" , A[0][0]) ;
		if (t) {
			for (int i = n + 1 ; i <= n + m ; ++i) if (id[i]) xi[id[i]] = A[i - n][0] ;
			for (int i = 1 ; i <= n ; ++i) printf("%0.9lf " , xi[i]) ;
			printf("\n") ;
		}
	}

	return 0 ;
}