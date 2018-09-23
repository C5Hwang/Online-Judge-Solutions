#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2500 + 10 , INF = 0x3f3f3f3f ;

int n , m , a[MAX_N] , f[MAX_N] ;

int main() {
	scanf("%d %d" , &n , &m) ; a[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		f[i] = INF ; a[i] += a[i - 1] ;
	}
	f[0] = 0 ;

	for (int i = 1 ; i <= n ; ++i) {
		int res = INF ;
		for (int j = 1 ; j <= i ; ++j) res = std::min(res , f[i - j] + a[j]) ;

		f[i] = res + 2 * m ;
	}

	printf("%d\n" , f[n] - m) ;

	return 0 ;
}
