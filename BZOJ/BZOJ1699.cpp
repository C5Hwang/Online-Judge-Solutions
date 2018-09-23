#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e4 + 10 , lgN = 25 ;

int n , q , a[MAX_N] , f[MAX_N][lgN] , g[MAX_N][lgN] ;

int main() {
	scanf("%d %d" , &n , &q) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &a[i]) ;
		f[i][0] = g[i][0] = a[i] ;
	}

	///

	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 0 ; i < n ; ++i) {
			int k = i + (1 << (j - 1)) ;
			
			if (k < n) {
				f[i][j] = std::max(f[i][j - 1] , f[k][j - 1]) ;
				g[i][j] = std::min(g[i][j - 1] , g[k][j - 1]) ;
			}
			else f[i][j] = f[i][j - 1] , g[i][j] = g[i][j - 1] ;
		}

	///
	
	for (int i = 0 ; i < q ; ++i) {
		int x , y , len ;
		scanf("%d %d" , &x , &y) ; --x ; --y ;
		len = y - x + 1 ;

		int k = 0 , MIN , MAX ;
		while ((1 << (k + 1)) <= len) ++k ;	
		MIN = std::min(g[x][k] , g[y - (1 << k) + 1][k]) ;
		MAX = std::max(f[x][k] , f[y - (1 << k) + 1][k]) ;

		printf("%d\n" , MAX - MIN) ;
	}

	return 0 ;
}
