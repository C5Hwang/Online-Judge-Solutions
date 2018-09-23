#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 2e3 + 10 ;

int T , k , n , m , C[MAX_N][MAX_N] , sum[MAX_N][MAX_N] ;

int main() {
	scanf("%d %d" , &T , &k) ;
	n = 2e3 ;
	C[0][0] = 1 ; sum[0][0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		C[i][0] = 1 ; sum[i][0] = 0 ;
		for (int j = 1 ; j <= i ; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % k ;
			sum[i][j] = sum[i][j - 1] + (C[i][j] ? 0 : 1) ;
		}
		for (int j = i + 1 ; j <= n ; ++j) sum[i][j] = sum[i][j - 1] ;
	}

	///

	while (T--) {
		scanf("%d %d" , &n , &m) ;

		int ans = 0 ;
		for (int i = 1 ; i <= n ; ++i) ans += sum[i][m] ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}
