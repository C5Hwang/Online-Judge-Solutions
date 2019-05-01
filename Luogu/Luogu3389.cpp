#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-6 ;
const int MAX_N = 100 + 10 ;

int n ;
db A[MAX_N][MAX_N] ;

bool gauss() {
	for (int i = 0 ; i < n ; ++i) {
		int r = i ;
		for (int j = i + 1 ; j < n ; ++j) if (fabs(A[r][i]) - fabs(A[j][i]) < eps) r = j ;
		if (r != i) for (int j = 0 ; j <= n ; ++j) std::swap(A[r][j] , A[i][j]) ;

		if (fabs(A[i][i]) < eps) return 0 ;

		for (int j = i + 1 ; j < n ; ++j) {
			db t = A[j][i] / A[i][i] ;
			for (int k = i ; k <= n ; ++k) A[j][k] -= t * A[i][k] ;
		}
	}

	for (int i = n - 1 ; i >= 0 ; --i) {
		for (int j = i + 1 ; j < n ; ++j) A[i][n] -= A[i][j] * A[j][n] ;
		A[i][n] /= A[i][i] ;
	}

	return 1 ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j <= n ; ++j) scanf("%lf" , &A[i][j]) ;

	///

	if (gauss()) for (int i = 0 ; i < n ; ++i) printf("%0.2lf\n" , A[i][n]) ;
	else printf("No Solution\n") ;

	return 0 ;
}