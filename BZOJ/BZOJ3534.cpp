#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ldb long double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ldb eps = 1e-8 ;
const int MAX_N = 50 + 5 ;

int n ;
ldb sum , a[MAX_N][MAX_N] ;

ldb gauss() {
	ldb sum = 1 ;
	for (int i = 1 ; i < n ; ++i) {
		int r = i ;
		for (int j = i + 1 ; j < n ; ++j) if (fabs(a[r][i]) - fabs(a[j][i]) < eps) r = j ;
		if (i != r) for (int j = 1 ; j < n ; ++j) std::swap(a[i][j] , a[r][j]) ;

		for (int j = i + 1 ; j < n ; ++j) {
			ldb xs = a[j][i] / a[i][i] ;
			for (int k = i ; k < n ; ++k) a[j][k] -= xs * a[i][k] ;
		}
		sum *= a[i][i] ;
	}

	return fabs(sum) ;
}

int main() {
	scanf("%d" , &n) ;

	sum = 1 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			scanf("%Lf" , &a[i][j]) ;
			if (fabs(a[i][j] - 1) < eps) a[i][j] = 1 - eps ;

			if (i < j) sum *= (1 - a[i][j]) ;
		}
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			if (i != j) {
				a[i][j] = a[i][j] / (1 - a[i][j]) ;
				a[i][i] += a[i][j] ; a[i][j] = -a[i][j] ;
			}

	///

	sum *= gauss() ;
	printf("%0.9Lf\n" , sum) ;

	return 0 ;
}