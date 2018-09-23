#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e4 + 10 , MAX_M = 500 + 10 ;

int n , m , f[MAX_N][MAX_M] ;

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		int d ;
		scanf("%d" , &d) ;

		f[i][0] = f[i - 1][0] ;
		for (int j = 1 ; j <= std::min(i - 1 , m) ; ++j) f[i][0] = std::max(f[i][0] , f[i - j][j]) ;
		for (int j = 1 ; j <= m ; ++j) f[i][j] = f[i - 1][j - 1] + d ;
	}

	printf("%d\n" , f[n][0]) ;

	return 0 ;
}
