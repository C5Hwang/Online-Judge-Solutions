#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 10 + 5 ;

int n ;
db ver[MAX_N][MAX_N] , mat[MAX_N][MAX_N] ;

db sq(db x) {return x * x ;}

void gauss() {
	for (int i = 1 ; i <= n ; ++i) {
		int r = i ;
		for (int j = i + 1 ; j <= n ; ++j) if (fabs(mat[j][i]) > fabs(mat[r][i])) r = j ;
		if (r != i) for (int j = 1 ; j <= n + 1 ; ++j) std::swap(mat[i][j] , mat[r][j]) ;

		for (int j = i + 1 ; j <= n ; ++j) {
			db tmp = mat[j][i] / mat[i][i] ;
			for (int k = i ; k <= n + 1 ; ++k) mat[j][k] -= mat[i][k] * tmp ;
		}
	}

	for (int i = n ; i ; --i) {
		for (int j = n ; j > i ; --j) mat[i][n + 1] -= mat[j][n + 1] * mat[i][j] ;
		mat[i][n + 1] /= mat[i][i] ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) scanf("%lf" , &ver[i][j]) ;

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			mat[i][j] = 2 * (ver[i][j] - ver[0][j]) ;
			mat[i][n + 1] += sq(ver[i][j]) - sq(ver[0][j]) ;
		}

	gauss() ;

	for (int i = 1 ; i <= n ; ++i) {
		printf("%0.3lf" , mat[i][n + 1]) ;
		if (i != n) printf(" ") ;
	}

	return 0 ;
}