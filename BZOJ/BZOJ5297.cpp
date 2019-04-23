#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 250 + 10 , mod = 1e4 + 7 ;

int n , m , a[MAX_N][MAX_N] ;

inline int gauss() {
	int s = 1 , f = 1 ;

	for (int i = 2 ; i <= n ; ++i) {
		for (int j = i + 1 ; j <= n ; ++j)
			for (; a[j][i] ;) {
				int t = a[i][i] / a[j][i] ;
				for (int k = i ; k <= n ; ++k)
					a[i][k] = (a[i][k] - t * a[j][k] % mod + mod) % mod ;
				for (int k = i ; k <= n ; ++k) std::swap(a[i][k] , a[j][k]) ;
				f = -f ;
			}

		(s *= a[i][i]) %= mod ;
	}

	if (f < 0) s = (mod - s) % mod ;
	return s ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &y , &x) ;

		(++a[y][y]) %= mod ; (a[x][y] += mod - 1) %= mod ;
	}

	///

	printf("%d\n" , gauss()) ;

	return 0 ;
}